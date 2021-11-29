/*
 * Copyright (c) 2003-2009 Objective Systems, Inc.
 *
 * This software is furnished under a license and may be used and copied
 * only in accordance with the terms of such license and with the
 * inclusion of the above copyright notice. This software or any other
 * copies thereof may not be provided or otherwise made available to any
 * other person. No title to and ownership of the software is hereby
 * transferred.
 *
 * The information in this software is subject to change without notice
 * and should not be construed as a commitment by Objective Systems, Inc.
 *
 * PROPRIETARY NOTICE
 *
 * This software is an unpublished work subject to a confidentiality agreement
 * and is protected by copyright and trade secret law.  Unauthorized copying,
 * redistribution or other use of this work is prohibited.
 *
 * The above notice of copyright on this source code product does not indicate
 * any actual or intended publication of such source code.
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxMemory.h"
#include "rtxsrc/rtxStream.h"
#include "rtxsrc/rtxStreamZlib.h"
#include "zlib.h"

#ifdef _DEBUG
#undef OSRTSTRM_K_BUFSIZE
#define OSRTSTRM_K_BUFSIZE 43 /* small enough, to test how flushing works */
#endif

typedef struct ZlibDesc {
   OSCTXT* pctxt;
   OSRTSTREAM* pUnderStream; /* underlying stream object */
   size_t   savedIndex;
   
   OSOCTET* inBuf;
   size_t inBufSz;
   size_t inBufPos;
   size_t inBufEnd;

   OSOCTET* outBuf;
   size_t outBufSz;
   size_t outBufPos;
   size_t outBufEnd;
   
   int level;
   int windowBits;
   int memLevel;
   int strategy;

   z_stream strm;
   OSBOOL compressed;
   OSBOOL dynamic;
   
} ZlibDesc;

int checkBuffer (OSCTXT* pctxt, size_t nbytes)
{
   if ( ( pctxt->buffer.byteIndex + nbytes ) > pctxt->buffer.size ) {
      if (pctxt->buffer.dynamic) {

         /* If dynamic encoding enabled, expand the current buffer 	*/
         /* to allow encoding to continue.                              */

         pctxt->buffer.size += OSRTMAX (OSRTENCBUFSIZ, nbytes);

         pctxt->buffer.data = rtxMemReallocArray 
            (pctxt, pctxt->buffer.data, pctxt->buffer.size, OSOCTET);

         if (!pctxt->buffer.data) 
            return LOG_RTERRNEW (pctxt, RTERR_NOMEM);
      }
      else {
         return LOG_RTERRNEW (pctxt, RTERR_BUFOVFLW);
      }
   }

   return 0;
}

int checkOutputBuffer (ZlibDesc* mdesc, size_t nbytes)
{
   if (mdesc->outBufPos + nbytes > mdesc->outBufSz) {
      if (mdesc->dynamic) {
         mdesc->outBufSz += OSRTMAX (OSRTENCBUFSIZ, nbytes);

         mdesc->outBuf = rtxMemReallocArray 
            (mdesc->pctxt, mdesc->outBuf, mdesc->outBufSz, OSOCTET);

         if (mdesc->outBuf) 
            return LOG_RTERRNEW (mdesc->pctxt, RTERR_NOMEM);
      }
      else
         return LOG_RTERRNEW (mdesc->pctxt, RTERR_BUFOVFLW);
   }

   return 0;
}

static long zlibWrite 
(OSRTSTREAM* pStream, const OSOCTET* pdata, size_t numocts)
{
   int stat = 0;
   ZlibDesc* mdesc = (ZlibDesc*) pStream->extra;
   z_stream* pstrm = &mdesc->strm;
   OSCTXT* pctxt = mdesc->pctxt;
   OSRTSTREAM* pUnderStream = mdesc->pUnderStream;
   size_t tail;
   
   if (!(pStream->flags & OSRTSTRMF_OUTPUT)) 
      return RTERR_INVPARAM;

   if (numocts == 0) return 0;

   if (!mdesc->compressed) {
      /* direct write to the under stream. */
      if (pUnderStream)
         stat = pUnderStream->write (pUnderStream, pdata, numocts);
      else {
         stat = checkBuffer (pctxt, numocts);
         if (0 == stat) {
            OSCRTLMEMCPY (&pctxt->buffer.data[pctxt->buffer.byteIndex], 
                    pdata, numocts);

            pctxt->buffer.byteIndex += numocts;
         }
      }
      
      if (stat != 0) LOG_RTERR (pctxt, stat);
      else pStream->bytesProcessed += numocts;
      
      return stat;
   }

   do {
      OSOCTET partialByte = 0;
      
      if (mdesc->inBuf == pctxt->buffer.data)
         mdesc->inBufPos = pctxt->buffer.byteIndex;

      if (pdata == 0 || pdata == mdesc->inBuf) { 
         /* flush */
         pstrm->next_in = (Bytef*) mdesc->inBuf;
         pstrm->avail_in = (uInt) mdesc->inBufPos;
         numocts = 0;

         /* move bits from buffer position */
         if (mdesc->inBufPos < mdesc->inBufSz)
            partialByte = mdesc->inBuf[mdesc->inBufPos];
         
         mdesc->inBufPos = 0;
         if (mdesc->inBuf == pctxt->buffer.data)
            pctxt->buffer.byteIndex = 0;
      }
      else if (mdesc->inBufPos == 0 && numocts >= mdesc->inBufSz) {
         /* direct encode from pdata */
         pstrm->next_in = (Bytef*) pdata;
         pstrm->avail_in = (uInt) numocts;
         numocts = 0;
      }
      else {
         /* copy data to end of input buffer */
         tail = mdesc->inBufSz - mdesc->inBufPos;
         if (tail > numocts) tail = numocts;

         OSCRTLMEMCPY (mdesc->inBuf + mdesc->inBufPos, pdata, tail); 
         pdata += tail;
         numocts -= tail;
         mdesc->inBufPos += tail;
         
         if (mdesc->inBuf == pctxt->buffer.data)
            pctxt->buffer.byteIndex = mdesc->inBufPos;

         if (mdesc->inBufPos < mdesc->inBufSz)
            break; /* buffer is not full */

         pstrm->next_in = (Bytef*) mdesc->inBuf;
         pstrm->avail_in = (uInt) mdesc->inBufSz;
         
         mdesc->inBufPos = 0;

         if (mdesc->inBuf == pctxt->buffer.data)
            pctxt->buffer.byteIndex = 0;
      }
         
      pStream->bytesProcessed += pstrm->avail_in;

      while (pstrm->avail_in > 0 || pdata == 0) {
         OSBOOL streamEnd = FALSE;
         
         if (!pUnderStream) { /* encode to context buffer */
            /* ??? YG: smaller block may be preallocated */
            stat = checkOutputBuffer (mdesc, pstrm->avail_in);
            if (stat != 0) return LOG_RTERR (pctxt, stat);

            pstrm->next_out = (Bytef*) mdesc->outBuf + mdesc->outBufPos;
            pstrm->avail_out = (uInt) (mdesc->outBufSz - mdesc->outBufPos);
         }
         
         stat = deflate (pstrm, (pdata) ? Z_NO_FLUSH : Z_FINISH);
      
         if (stat == Z_OK) stat = RT_OK;
         else if (stat == Z_STREAM_END) {
            streamEnd = TRUE;
            stat = RT_OK;
         }
         else stat = RTERR_FAILED;
         
         if (stat != 0) return LOG_RTERR (pctxt, stat);

         if (pUnderStream) {
            if (pstrm->avail_out == 0 || pdata == 0) {
               /* write out buffer to under stream */
               stat = pUnderStream->write (pUnderStream, mdesc->outBuf, 
                   mdesc->outBufSz - pstrm->avail_out);

               if (stat != 0) return LOG_RTERR (pctxt, stat);
               
               /* reset output buffer to begin */
               pstrm->next_out = (Bytef*) mdesc->outBuf;
               pstrm->avail_out = (uInt) mdesc->outBufSz;
            }
         }
         else {
            /* correct output buffer position */
            mdesc->outBufPos = mdesc->outBufSz - pstrm->avail_out;
         }
      
         if (streamEnd) /* deflate finished */
            return 0;
      }
      
      mdesc->inBuf[mdesc->inBufPos] = partialByte;
   }
   while (numocts > 0);

   return 0;
}

typedef enum { Unblocked, Blocked, Skip } ReadMode;

static long zlibReadData 
(OSRTSTREAM* pStream, OSOCTET* pdata, size_t size, ReadMode mode)
{
   ZlibDesc* mdesc = (ZlibDesc*) pStream->extra;
   z_stream* pstrm = &mdesc->strm;
   OSCTXT* pctxt = mdesc->pctxt;
   OSRTSTREAM* pUnderStream = mdesc->pUnderStream;
   int stat;
   size_t tail;
   long readySize = 0;

   if (!(pStream->flags & OSRTSTRMF_INPUT))
      return RTERR_INVPARAM;

   if (size == 0)
      return 0;

   if (!mdesc->compressed) {
      /* direct read from the under stream. */
      if (!pdata) return RTERR_NULLPTR;

      if (pUnderStream) {
         if (mode == Blocked) {
            if (pUnderStream->blockingRead)
               readySize = pUnderStream->blockingRead (pUnderStream, pdata, size);
            else {
               readySize = 0;

               do {
                  long tm = pUnderStream->read (pUnderStream, pdata, size);
                  if (tm >= 0) { /* ??? if tm == 0 */
                     readySize += tm;
                     pdata += tm;
                     size -= tm;
                  }
                  else {
                     readySize = tm;
                     break;
                  }   
               }
               while (size > 0); 
            }
         }
         else
            readySize = pUnderStream->read (pUnderStream, pdata, size);
      }
      else {
         tail = pctxt->buffer.size - pctxt->buffer.byteIndex;
         if (tail > size) tail = size;

         OSCRTLMEMCPY (pdata, &pctxt->buffer.data[pctxt->buffer.byteIndex], 
                       tail);
         
         readySize = (long) tail;
      }
      
      if (readySize > 0) pStream->bytesProcessed += readySize;

      return (readySize >= 0) ? readySize : LOG_RTERR (pctxt, (int) readySize);
   }

   if (mdesc->outBuf == pctxt->buffer.data)
      mdesc->outBufPos = pctxt->buffer.byteIndex;
   
   tail = mdesc->outBufEnd - mdesc->outBufPos;
   
   if (pdata == 0 && mode != Skip &&
       mdesc->savedIndex == OSRTSTRM_K_INVALIDMARK) 
   { 
      if (tail > 0)
         OSCRTLMEMMOVE (mdesc->outBuf, mdesc->outBuf + mdesc->outBufPos,
                        tail);

      mdesc->outBufPos = 0;
      mdesc->outBufEnd = tail;

      if (mdesc->outBuf == pctxt->buffer.data)
         pctxt->buffer.byteIndex = 0;
   }

   if (tail > 0) {
      /* copy data from output buffer */
      if (tail > size)
         tail = size;
      
      if (pdata) {
         OSCRTLMEMCPY (pdata, mdesc->outBuf + mdesc->outBufPos, tail);
         pdata += tail;
      }
      
      readySize = tail;
      size -= tail;

      if (pdata || mode == Skip) {
         mdesc->outBufPos += tail;
         pStream->bytesProcessed += tail;

         if (mdesc->savedIndex == OSRTSTRM_K_INVALIDMARK &&
             mdesc->outBufPos == mdesc->outBufEnd)
            mdesc->outBufPos = mdesc->outBufEnd = 0;

         if (mdesc->outBuf == pctxt->buffer.data)
            pctxt->buffer.byteIndex = mdesc->outBufPos;
      }
   }
   
   while (size > 0) {
      OSBOOL direct = FALSE;
      OSBOOL streamEnd = FALSE;
      
      /* decompress */
      if (pUnderStream) {
         if (mdesc->inBufEnd == mdesc->inBufPos) {
            /* input buffer is empty; read from under stream */
            long tm = pUnderStream->read 
               (pUnderStream, mdesc->inBuf, mdesc->inBufSz);
            
            if (tm < 0) return LOG_RTERR (pctxt, (int) tm);
            
            mdesc->inBufPos = 0;
            mdesc->inBufEnd = (size_t) tm;
         }
      }

      pstrm->next_in = (Bytef*) mdesc->inBuf + mdesc->inBufPos;
      pstrm->avail_in = (uInt) (mdesc->inBufEnd - mdesc->inBufPos);
      
      if (pdata && size > mdesc->outBufSz && 
          mdesc->savedIndex == OSRTSTRM_K_INVALIDMARK)
         direct = TRUE;
      
      if (direct) {
         /* direct decode to pdata */
         pstrm->next_out = (Bytef*) pdata;
         pstrm->avail_out = (uInt) size;
      }
      else {
         /* decode to output buffer */
         if (mdesc->outBufSz == mdesc->outBufEnd) {
            /* output buffer is full */
            size_t bufLen = mdesc->outBufSz * 2;
            
            if (bufLen > pStream->readAheadLimit)
               bufLen = pStream->readAheadLimit;
            
            if (bufLen > mdesc->outBufSz) {  
               /* expand output buffer */
               OSOCTET* ptm = rtxMemReallocArray 
                  (pctxt, mdesc->outBuf, mdesc->outBufSz * 2, OSOCTET);

               if (ptm == 0) return LOG_RTERR (pctxt, RTERR_NOMEM);
               
               if (mdesc->outBuf == pctxt->buffer.data) {
                  pctxt->buffer.data = ptm;
                  pctxt->buffer.size = bufLen;
               }
               
               mdesc->outBuf = ptm;
               mdesc->outBufSz = bufLen;
            }
            else {
               /* clear saved position */
               mdesc->savedIndex = OSRTSTRM_K_INVALIDMARK;
               mdesc->outBufPos = mdesc->outBufEnd = 0;

               if (mdesc->outBuf == pctxt->buffer.data)
                  pctxt->buffer.byteIndex = 0;
            }
         }

         pstrm->next_out = (Bytef*) mdesc->outBuf + mdesc->outBufEnd;
         pstrm->avail_out = (uInt) mdesc->outBufSz - mdesc->outBufEnd;
      }
      
      if (pstrm->avail_in == 0) {
         /* no data to decompress */
         if (mode == Blocked) {
            if (pUnderStream)
               continue; /* try to read more data */
            else
               return LOG_RTERR (pctxt,RTERR_ENDOFBUF); 
         }   
         else /* return actually readed size in non blocking mode */
            return readySize;
      }
      
      tail = pstrm->avail_out;
      
      stat = inflate (pstrm, Z_SYNC_FLUSH);
   
      if (stat == Z_OK) stat = RT_OK;
      else if (stat == Z_STREAM_END) {
         stat = RT_OK;
         streamEnd = TRUE;
      }   
      else stat = RTERR_FAILED;
      
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      tail -= pstrm->avail_out;
      
      if (direct) {
         /* decoded directly to pdata */
         pdata += tail;
         size -= tail;
         readySize += tail;
         pStream->bytesProcessed += tail;
      }
      else {
         /* decoded to output buffer */
         mdesc->outBufEnd += tail;
         if (mdesc->outBuf == pctxt->buffer.data)
            pctxt->buffer.size = mdesc->outBufEnd;

         if (tail > size) tail = size;

         if (pdata)
            OSCRTLMEMCPY (pdata, mdesc->outBuf + mdesc->outBufPos, tail);

         readySize += tail;

         if (pdata || mode == Skip) {
            mdesc->outBufPos += tail;
            pStream->bytesProcessed += tail;

            if (mdesc->savedIndex == OSRTSTRM_K_INVALIDMARK &&
                mdesc->outBufPos == mdesc->outBufEnd)
               mdesc->outBufPos = mdesc->outBufEnd = 0;

            if (mdesc->outBuf == pctxt->buffer.data)
               pctxt->buffer.byteIndex = mdesc->outBufPos;
         }
         
         size -= tail;
      }

      mdesc->inBufPos = mdesc->inBufEnd - pstrm->avail_in;
      
      if (streamEnd)
         break;
   }

   return (long) readySize;
}

static long zlibRead 
(OSRTSTREAM* pStream, OSOCTET* pdata, size_t size)
{
   return zlibReadData (pStream, pdata, size, Unblocked);
}

static long zlibBlockingRead 
(OSRTSTREAM* pStream, OSOCTET* pdata, size_t size)
{
   return zlibReadData (pStream, pdata, size, Blocked);
}

static int zlibClose (OSRTSTREAM* pStream)
{
   ZlibDesc* mdesc = (ZlibDesc*) pStream->extra;
   OSRTSTREAM* pUnderStream = mdesc->pUnderStream;
   OSCTXT* pctxt = mdesc->pctxt;
   int stat = 0;

   if (pStream->flags & OSRTSTRMF_OUTPUT) {
      if (mdesc->compressed) {
         stat = zlibWrite (pStream, 0, 1); /* flush */
      }
   }
   else if (!(pStream->flags & OSRTSTRMF_INPUT)) 
      stat = RTERR_NOTINIT;

   if (stat != 0) LOG_RTERR (pctxt, stat);

   if (mdesc->inBuf) rtxMemFreeType (pctxt, mdesc->inBuf);
   if (mdesc->outBuf) rtxMemFreeType (pctxt, mdesc->outBuf);
   rtxMemFreeType (pctxt, mdesc);

   /* if under stream absent then pStream will be freed in rtxStreamClose */
   if (pUnderStream) {
      rtxMemFreePtr (pctxt, pctxt->pStream);
      pctxt->pStream = pUnderStream;

      stat = pUnderStream->close (pUnderStream);
   }
   
   return (0 == stat) ? 0 : LOG_RTERR (pctxt, stat);
}

static int zlibFlush (OSRTSTREAM* pStream)
{
   ZlibDesc* mdesc = (ZlibDesc*) pStream->extra;
   OSRTSTREAM* pUnderStream = mdesc->pUnderStream;
   OSCTXT* pctxt = mdesc->pctxt;
   int stat = 0;

   if (!(pStream->flags & OSRTSTRMF_OUTPUT)) 
      return LOG_RTERRNEW (pctxt, RTERR_INVPARAM);

   if (mdesc->compressed) {
      stat = zlibWrite (pStream, mdesc->inBuf, 1); /* write input buffer */
      if (stat != 0) LOG_RTERR (pctxt, stat);
   }

   return (pUnderStream && pUnderStream->flush != 0) ? 
      pUnderStream->flush (pUnderStream) : 0;
}

static int zlibMark (OSRTSTREAM* pStream, size_t readAheadLimit)
{
   ZlibDesc* mdesc = (ZlibDesc*) pStream->extra;
   OSCTXT* pctxt = mdesc->pctxt;
   size_t sz;
   
   if (!(pStream->flags & OSRTSTRMF_INPUT)) 
      return LOG_RTERRNEW (pctxt, RTERR_INVPARAM);
   
   /* ??? mdesc->compressed */
   
   sz = mdesc->outBufEnd - mdesc->outBufPos;
   if (mdesc->outBufPos > 0 && sz > 0) {
      OSCRTLMEMMOVE (mdesc->outBuf, mdesc->outBuf + mdesc->outBufPos, sz);
      mdesc->outBufEnd = sz;
   }
   
   mdesc->savedIndex = mdesc->outBufPos = 0;
   if (readAheadLimit < mdesc->outBufSz) readAheadLimit = mdesc->outBufSz;
   pStream->readAheadLimit = readAheadLimit;
   pStream->markedBytesProcessed = pStream->bytesProcessed;
   return 0;
}

static int zlibReset (OSRTSTREAM* pStream)
{
   ZlibDesc* mdesc = (ZlibDesc*) pStream->extra;
   OSCTXT* pctxt = mdesc->pctxt;

   if (!(pStream->flags & OSRTSTRMF_INPUT)) 
      return LOG_RTERRNEW (pctxt, RTERR_INVPARAM);

   if (mdesc->savedIndex == OSRTSTRM_K_INVALIDMARK) 
      return LOG_RTERRNEW (pctxt, RTERR_INVPARAM);

   /* ??? mdesc->compressed */

   mdesc->outBufPos = mdesc->savedIndex;
   pStream->bytesProcessed = pStream->markedBytesProcessed;
   
   /* clear saved position */
   mdesc->savedIndex = OSRTSTRM_K_INVALIDMARK;
   pStream->readAheadLimit = 0;

   return 0;
}

static int zlibSkip (OSRTSTREAM* pStream, size_t skipBytes)
{
   ZlibDesc* mdesc = (ZlibDesc*) pStream->extra;
   OSRTSTREAM* pUnderStream = mdesc->pUnderStream;
   int stat;

   if (mdesc->compressed) {
      stat = (int) zlibReadData (pStream, 0, skipBytes, Skip);
      if (stat > 0) stat = 0;
   }
   else
      stat = pUnderStream->skip (pStream, skipBytes);

   return stat;
}

int rtxStreamZlibAttach (OSCTXT* pctxt, OSUINT16 flags) 
{
   OSRTSTREAM *pStream;
   OSRTSTREAM *pUnderStream;
   ZlibDesc* mdesc;
   int stat;

   pUnderStream = pctxt->pStream;

   pctxt->pStream = 0;
   /* re-init stream */
   stat = rtxStreamInit (pctxt);
   if (0 != stat) return LOG_RTERR (pctxt, stat);

   pStream = pctxt->pStream;

   if (pUnderStream)
      pStream->flags = (OSUINT16) (pUnderStream->flags | OSRTSTRMF_UNBUFFERED);
   else
      pStream->flags = (OSUINT16) (flags | OSRTSTRMF_UNBUFFERED);

   if (pStream->flags & OSRTSTRMF_OUTPUT) {
      pStream->write = zlibWrite;
      pStream->flush = zlibFlush;
   }
   else if (pStream->flags & OSRTSTRMF_INPUT) {
      pStream->read  = zlibRead;
      pStream->blockingRead  = zlibBlockingRead;
      pStream->skip  = zlibSkip;
      pStream->mark = zlibMark;
      pStream->reset = zlibReset;
   }
   pStream->close = zlibClose;

   mdesc = rtxMemAllocType (pctxt, ZlibDesc);
   if (mdesc == 0) {
      rtxMemFreePtr (pctxt, pStream);
      pctxt->pStream = pUnderStream;
      return LOG_RTERRNEW (pctxt, RTERR_NOMEM);
   }   

   mdesc->pctxt = pctxt;
   mdesc->pUnderStream = pUnderStream;
   mdesc->savedIndex = OSRTSTRM_K_INVALIDMARK;

   /* create buffers */
   mdesc->inBuf = 0;
   mdesc->outBuf = 0;

   if (pStream->flags & OSRTSTRMF_OUTPUT) {
      if (pUnderStream) {
         /* compress to stream */
         mdesc->outBuf = rtxMemAllocArray (pctxt, OSRTSTRM_K_BUFSIZE, 
                                           OSOCTET);
         if (!mdesc->outBuf) stat = RTERR_NOMEM;
         
         if (stat == 0 && pctxt->buffer.data == 0) {
            /* compress without direct buf */
            mdesc->inBuf = rtxMemAllocArray (pctxt, OSRTSTRM_K_BUFSIZE, 
                                             OSOCTET);
            if (!mdesc->inBuf) stat = RTERR_NOMEM;
         }
      }
      else if (pctxt->buffer.data != 0) {
         /* compress to context buffer */
         mdesc->inBuf = rtxMemAllocArray (pctxt, OSRTSTRM_K_BUFSIZE, 
                                          OSOCTET);
         if (!mdesc->inBuf) stat = RTERR_NOMEM;
      }
      else stat = RTERR_BUFOVFLW; /* no destination */
   }
   else if (pStream->flags & OSRTSTRMF_INPUT) {
      if (pUnderStream) {
         /* decompress to stream */
         mdesc->inBuf = rtxMemAllocArray (pctxt, OSRTSTRM_K_BUFSIZE, 
                                          OSOCTET);
         if (!mdesc->inBuf) stat = RTERR_NOMEM;
         
         if (stat == 0 && pctxt->buffer.data == 0) {
            /* decompress without ctxtBuf */
            mdesc->outBuf = rtxMemAllocArray (pctxt, OSRTSTRM_K_BUFSIZE, 
                                             OSOCTET);
            if (!mdesc->outBuf) stat = RTERR_NOMEM;
         }
      }
      else if (pctxt->buffer.data != 0) {
         /* decompress from context buffer */
         mdesc->outBuf = rtxMemAllocArray (pctxt, OSRTSTRM_K_BUFSIZE, 
                                           OSOCTET);
         if (!mdesc->outBuf) stat = RTERR_NOMEM;
      }
      else stat = RTERR_ENDOFBUF; /* no source */
   }
   else RTERR_FAILED;
   
   if (stat != 0)  {
      if (mdesc->inBuf) rtxMemFreePtr (pctxt, mdesc->inBuf);
      if (mdesc->outBuf) rtxMemFreePtr (pctxt, mdesc->inBuf);
      rtxMemFreePtr (pctxt, mdesc);
      rtxMemFreePtr (pctxt, pStream);
      pctxt->pStream = pUnderStream;
      return LOG_RTERRNEW (pctxt, stat);
   }

   mdesc->inBufSz = OSRTSTRM_K_BUFSIZE;
   mdesc->inBufPos = 0;
   mdesc->inBufEnd = 0;
   
   mdesc->outBufSz = OSRTSTRM_K_BUFSIZE;
   mdesc->outBufPos = 0;
   mdesc->outBufEnd = 0;

   pStream->id    = OSRTSTRMID_ZLIB;
   pStream->extra = mdesc;
   
   mdesc->compressed = FALSE;
   
   /* set compression default params */
   mdesc->level = Z_DEFAULT_COMPRESSION;
   mdesc->windowBits = MAX_WBITS;
   mdesc->memLevel = 9; /* 8 for 16-bit platform */
   mdesc->strategy = Z_DEFAULT_STRATEGY;
   
   return 0;
}

int rtxStreamZlibFree (OSCTXT* pctxt) 
{
   return zlibClose (pctxt->pStream);
}


int rtxStreamZlibSetDeflateParams 
(OSCTXT* pctxt, int level, int windowBits, int memLevel, int strategy)
{
   ZlibDesc* mdesc = (ZlibDesc*) pctxt->pStream->extra;
   mdesc->level = level;
   mdesc->windowBits = windowBits;
   mdesc->memLevel = memLevel;
   mdesc->strategy = strategy;
   return 0;
}

int rtxStreamZlibSetInflateParams 
(OSCTXT* pctxt, int windowBits)
{
   ZlibDesc* mdesc = (ZlibDesc*) pctxt->pStream->extra;
   mdesc->windowBits = windowBits;
   return 0;
}

static voidpf zalloc (voidpf opaque, uInt items, uInt size)
{
   return (voidpf) rtxMemAlloc ((OSCTXT*) opaque, items * size);
}

static void zfree (voidpf opaque, voidpf address)
{
   rtxMemFreePtr ((OSCTXT*) opaque, address);
}

int rtxStreamZlibStart (OSCTXT* pctxt)
{
   int stat = 0;
   ZlibDesc* mdesc = (ZlibDesc*) pctxt->pStream->extra;
   OSRTSTREAM* pUnderStream = mdesc->pUnderStream;
   z_stream* pstrm = &mdesc->strm;
   
   pstrm->zalloc = zalloc;
   pstrm->zfree = zfree;
   pstrm->opaque = pctxt;

   if (pctxt->pStream->flags & OSRTSTRMF_OUTPUT) {
      if (pUnderStream) {
         if (pctxt->buffer.data != 0) {
            /* buffer must aligned */
            if (pctxt->buffer.bitOffset != 8) { 
               pctxt->buffer.byteIndex++; 
               pctxt->buffer.bitOffset = 8; 
            }
            
            if (pctxt->buffer.byteIndex > 0) {
               /* flush content buffer */
               stat = zlibWrite (pctxt->pStream, pctxt->buffer.data, 
                                 pctxt->buffer.byteIndex);

               if (stat != 0) return LOG_RTERR (pctxt, stat);
            }
            
            pctxt->buffer.byteIndex = 0;
         }
            
         pstrm->next_out = (Bytef*) mdesc->outBuf;
         pstrm->avail_out = (uInt) mdesc->outBufSz;
      }
      else { /* zlib stream write to content buffer */
         /* buffer must aligned */
         if (pctxt->buffer.bitOffset != 8) { 
            pctxt->buffer.byteIndex++; 
            pctxt->buffer.bitOffset = 8; 
         }
         
         pstrm->next_out = 
            (Bytef*) pctxt->buffer.data + pctxt->buffer.byteIndex;
         pstrm->avail_out = 
            (uInt) (pctxt->buffer.size - pctxt->buffer.byteIndex);
      
         /* save context buffer in outBuf fields */
         mdesc->dynamic = pctxt->buffer.dynamic;
         mdesc->outBuf = pctxt->buffer.data;
         mdesc->outBufSz = pctxt->buffer.size;
         mdesc->outBufPos = pctxt->buffer.byteIndex;
         
         /* set input buffer as context buffer */
         pctxt->buffer.dynamic = FALSE;
         pctxt->buffer.data = mdesc->inBuf;
         pctxt->buffer.size = mdesc->inBufSz;
         pctxt->buffer.byteIndex = 0;
      }
      
      stat = deflateInit2 (pstrm, mdesc->level, Z_DEFLATED, mdesc->windowBits, 
                           mdesc->memLevel, mdesc->strategy);
   }
   else if (pctxt->pStream->flags & OSRTSTRMF_INPUT) {
      if (pUnderStream) {
         if (pctxt->buffer.data != 0) {
            /* decompress to context buffer */
         
            /* buffer must aligned */
            if (pctxt->buffer.bitOffset != 8) { 
               pctxt->buffer.byteIndex++; 
               pctxt->buffer.bitOffset = 8; 
            }
            
            mdesc->outBuf = pctxt->buffer.data;
            mdesc->outBufSz = pctxt->buffer.size;
            mdesc->outBufPos = pctxt->buffer.byteIndex;
            mdesc->outBufEnd = pctxt->buffer.size;
            
            /* ???? copy compressed part to input buffer */
            if (mdesc->outBufPos != mdesc->outBufSz) {
               size_t tail = mdesc->outBufSz - mdesc->outBufPos;
               OSCRTLMEMCPY (mdesc->inBuf, mdesc->outBuf + mdesc->outBufPos, 
                             tail);
               mdesc->inBufEnd = tail;
               mdesc->inBufPos = 0;
            }

            mdesc->outBufPos = pctxt->buffer.byteIndex = pctxt->buffer.size;
         }
      }
      else { /* zlib stream read from content buffer */
         /* buffer must aligned */
         if (pctxt->buffer.bitOffset != 8) { 
            pctxt->buffer.byteIndex++; 
            pctxt->buffer.bitOffset = 8; 
         }
         
         /* save context buffer in inBuf fields */
         mdesc->dynamic = pctxt->buffer.dynamic;
         mdesc->inBuf = pctxt->buffer.data;
         mdesc->inBufSz = pctxt->buffer.size;
         mdesc->inBufPos = pctxt->buffer.byteIndex;
         
         /* set output buffer as context buffer */
         pctxt->buffer.dynamic = TRUE;
         pctxt->buffer.data = mdesc->outBuf;
         pctxt->buffer.size = mdesc->outBufSz;
         pctxt->buffer.byteIndex = 0;
      }
      
      stat = inflateInit2 (pstrm, mdesc->windowBits);
   }
   else stat = RTERR_FAILED;
   
   if (stat == Z_OK) stat = RT_OK;
   else if (stat == Z_MEM_ERROR) stat = RTERR_NOMEM;
   else stat = RTERR_FAILED;
   
   mdesc->compressed = TRUE;
                       
   return (0 == stat) ? 0 : LOG_RTERR (pctxt, stat);
}

int rtxStreamZlibEnd (OSCTXT* pctxt)
{
   int stat = 0;
   ZlibDesc* mdesc = (ZlibDesc*) pctxt->pStream->extra;
   OSRTSTREAM* pUnderStream = mdesc->pUnderStream;
   z_stream* pstrm = &mdesc->strm;
   
   if (pctxt->pStream->flags & OSRTSTRMF_OUTPUT) {
      stat = zlibWrite (pctxt->pStream, 0, 1); /* flush */
      if (stat == 0) {
         stat = deflateEnd (pstrm);

         if (stat == Z_OK) stat = RT_OK;
         else stat = RTERR_FAILED;
      }
      
      if (pUnderStream) {
         if (mdesc->inBuf == pctxt->buffer.data)
            mdesc->inBuf = 0;
      }
      else {
         /* restore context buffer */
         pctxt->buffer.dynamic = mdesc->dynamic;
         pctxt->buffer.data = mdesc->outBuf;
         pctxt->buffer.size = mdesc->outBufSz;
         pctxt->buffer.byteIndex = mdesc->outBufPos;
         mdesc->outBuf = 0;
      }
   }   
   else if (pctxt->pStream->flags & OSRTSTRMF_INPUT) {
      stat = inflateEnd (pstrm);

      if (stat == Z_OK) stat = RT_OK;
      else stat = RTERR_FAILED;

      if (pUnderStream) {
         if (mdesc->outBuf == pctxt->buffer.data)
            mdesc->outBuf = 0;
      }
      else {
         /* restore context buffer */
         pctxt->buffer.dynamic = mdesc->dynamic;
         pctxt->buffer.data = mdesc->inBuf;
         pctxt->buffer.size = mdesc->inBufSz;
         pctxt->buffer.byteIndex = mdesc->inBufPos;
         mdesc->inBuf = 0;
      }
   }
   
   mdesc->compressed = FALSE;
                       
   return (0 == stat) ? 0 : LOG_RTERR (pctxt, stat);
}

int rtxStreamZlibReset (OSCTXT* pctxt)
{
   int stat = 0;
   ZlibDesc* mdesc = (ZlibDesc*) pctxt->pStream->extra;
   z_stream* pstrm = &mdesc->strm;
   
   if (pctxt->pStream->flags & OSRTSTRMF_OUTPUT) {
      stat = zlibWrite (pctxt->pStream, 0, 1); /* flush */
      if (stat == 0)
         stat = deflateReset (pstrm);
   }
   else if (pctxt->pStream->flags & OSRTSTRMF_INPUT)
      stat = inflateReset (pstrm);
   
   if (stat == Z_OK) stat = RT_OK;
   else stat = RTERR_FAILED;
   
   mdesc->compressed = TRUE;
                       
   return (0 == stat) ? 0 : LOG_RTERR (pctxt, stat);
}
