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
#include <string.h>
#include "rtxsrc/rtxStreamBuffered.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxMemory.h"

typedef struct CacheDesc {
   OSCTXT* pctxt;
   OSRTSTREAM* pUnderStream; /* underlying stream object */
   OSOCTET* pMemBuf;
   size_t   curIndex;
   size_t   readSize;
   size_t   savedIndex;
   OSUINT32 mode;
} CacheDesc;

#define MEMBUF_GROWTH 512

static long cacheRead (OSRTSTREAM* pStream, OSOCTET* pbuffer, size_t bufSize)
{
   CacheDesc* mdesc = (CacheDesc*)pStream->extra;
   size_t readBytes;
   size_t newIndex, lowestIndex;
   
   if (pStream->id != OSRTSTRMID_BUFFERED || !(pStream->flags & OSRTSTRMF_INPUT))
      return RTERR_INVPARAM;

   newIndex    = mdesc->curIndex;
   lowestIndex = mdesc->curIndex;
   newIndex += bufSize;

   /* reset mark pos if it is out of range */
   if (mdesc->savedIndex != OSRTSTRM_K_INVALIDMARK && 
       newIndex - mdesc->savedIndex > pStream->readAheadLimit)
   {
      mdesc->savedIndex = OSRTSTRM_K_INVALIDMARK;
      pStream->readAheadLimit = 0;
   }
   else {
      if (mdesc->savedIndex < mdesc->curIndex)
         lowestIndex = mdesc->savedIndex;
   }

   /* do we need to read more data? */
   if (mdesc->curIndex >= mdesc->readSize) {
      /* yes, read more data */
      long len;
      
      if (newIndex >= pStream->bufsize) {
         if (newIndex - lowestIndex > pStream->bufsize) {
            OSOCTET* pNewMemBuf;
            pStream->bufsize = (newIndex - lowestIndex + MEMBUF_GROWTH - 1) /
                                MEMBUF_GROWTH * MEMBUF_GROWTH;
            pNewMemBuf = rtxMemReallocArray (
               mdesc->pctxt, mdesc->pMemBuf, pStream->bufsize, OSOCTET);
            if (pNewMemBuf == 0)
               return RTERR_NOMEM;
            rtxMemHeapMarkSaved 
               (&mdesc->pctxt->pMemHeap, pNewMemBuf, TRUE);
            mdesc->pMemBuf = pNewMemBuf;
         }

         if (mdesc->savedIndex != OSRTSTRM_K_INVALIDMARK) 
         {
            /* move marked data to the beginning of the buffer */
            mdesc->readSize = mdesc->readSize - mdesc->savedIndex;
            OSCRTLMEMCPY (mdesc->pMemBuf, mdesc->pMemBuf + mdesc->savedIndex, 
                    mdesc->readSize);
            pStream->bytesProcessed += mdesc->savedIndex;
            pStream->markedBytesProcessed = pStream->bytesProcessed;
            mdesc->curIndex -= mdesc->savedIndex;
            mdesc->savedIndex = 0;
         }
         else {
            /* reset buffer pos to the beginning */
            mdesc->readSize = mdesc->readSize - mdesc->curIndex;
            OSCRTLMEMCPY (mdesc->pMemBuf, mdesc->pMemBuf + mdesc->curIndex, 
                    mdesc->readSize);
            pStream->bytesProcessed += mdesc->curIndex;
            mdesc->curIndex = 0;
         }
      }

      len = mdesc->pUnderStream->read
               (mdesc->pUnderStream, 
                mdesc->pMemBuf + mdesc->readSize, 
                pStream->bufsize - mdesc->readSize);
      if (len < 0) 
         return RTERR_ENDOFBUF;
      mdesc->readSize += len;
   }
   
   readBytes = mdesc->readSize - mdesc->curIndex;
   if (readBytes > bufSize) readBytes = bufSize;
   OSCRTLMEMCPY (pbuffer, mdesc->pMemBuf + mdesc->curIndex, readBytes);
   mdesc->curIndex += readBytes;

   if (mdesc->mode & OSRTSTRMCM_RESTORE_UNDERLAYING_AFTER_RESET &&
       mdesc->curIndex >= mdesc->readSize && 
       mdesc->savedIndex == OSRTSTRM_K_INVALIDMARK) 
   {
      rtxStreamBufferedRelease (mdesc->pctxt);
   }

   return (long)readBytes;
}

static int cacheSkip (OSRTSTREAM* pStream, size_t skipBytes)
{
   CacheDesc* mdesc = (CacheDesc*)pStream->extra;
   int stat;

   if (pStream->id != OSRTSTRMID_BUFFERED || !(pStream->flags & OSRTSTRMF_INPUT))
      return RTERR_INVPARAM;
   /* TODO: skip should read data into the buffer, if position is marked */
   stat = mdesc->pUnderStream->skip (mdesc->pUnderStream, skipBytes);
   if (stat >= 0)
      mdesc->curIndex += skipBytes;
   return stat;
}

static int cacheClose (OSRTSTREAM* pStream)
{
   CacheDesc* mdesc = (CacheDesc*)pStream->extra;
   int stat;

   if (pStream->id != OSRTSTRMID_BUFFERED) 
      return RTERR_INVPARAM;
   
   stat = mdesc->pUnderStream->close (mdesc->pUnderStream);
   mdesc->pUnderStream->flags = 0;

   rtxStreamBufferedRelease (mdesc->pctxt);
   return stat;
}

static int cacheMark (OSRTSTREAM* pStream, size_t readAheadLimit)
{
   CacheDesc* mdesc = (CacheDesc*)pStream->extra;

   if (pStream->id != OSRTSTRMID_BUFFERED || !(pStream->flags & OSRTSTRMF_INPUT))
      return RTERR_INVPARAM;
   mdesc->savedIndex = mdesc->curIndex;
   pStream->readAheadLimit = readAheadLimit;
   pStream->markedBytesProcessed = pStream->bytesProcessed;
   return 0;
}

static int cacheReset (OSRTSTREAM* pStream)
{
   CacheDesc* mdesc = (CacheDesc*)pStream->extra;

   if (mdesc->savedIndex == OSRTSTRM_K_INVALIDMARK || 
       mdesc->curIndex - mdesc->savedIndex > 
       pStream->readAheadLimit) 
   {
      int stat;

      /* if there is no savemark for the buffer, try to call
         "reset" for underlying stream. */
      
      stat = mdesc->pUnderStream->reset (mdesc->pUnderStream);

      if (stat == 0 && 
          mdesc->mode & OSRTSTRMCM_RESTORE_UNDERLAYING_AFTER_RESET) 
      {
         rtxStreamBufferedRelease (mdesc->pctxt);
      }
      return stat;
   }
   mdesc->curIndex = mdesc->savedIndex;
   pStream->bytesProcessed = pStream->markedBytesProcessed;
   mdesc->savedIndex = OSRTSTRM_K_INVALIDMARK;
   pStream->readAheadLimit = 0;
   return 0;
}

EXTRTMETHOD int rtxStreamBufferedCreate (OSCTXT* pctxt, OSUINT32 mode)
{
   OSRTSTREAM *pStream;
   OSRTSTREAM *pUnderStream;
   CacheDesc* mdesc;
   int stat;

   if (0 == pctxt->pStream) {
      return LOG_RTERRNEW (pctxt, RTERR_INVPARAM);
   }
   pUnderStream = pctxt->pStream;

   pctxt->pStream = 0;
   /* re-init stream */
   stat = rtxStreamInit (pctxt);
   if (0 != stat) return LOG_RTERR (pctxt, stat);

   pStream = pctxt->pStream;

   /* input stream are supported only */
   if (!(pUnderStream->flags & OSRTSTRMF_INPUT))
      return LOG_RTERRNEW (pctxt, RTERR_INVPARAM);

   pStream->read = cacheRead;
   pStream->blockingRead = cacheRead;
   pStream->skip = cacheSkip;
   pStream->mark = cacheMark;
   pStream->reset = cacheReset;

   mdesc = rtxMemAllocType (pctxt, CacheDesc);
   if (mdesc == 0)
      return LOG_RTERRNEW (pctxt, RTERR_NOMEM);
   rtxMemHeapMarkSaved (&pctxt->pMemHeap, mdesc, TRUE);
   mdesc->pctxt = pctxt;
   mdesc->pUnderStream = pUnderStream;
   mdesc->pMemBuf = 0;
   mdesc->readSize = 0;
   mdesc->curIndex = 0;
   mdesc->savedIndex = OSRTSTRM_K_INVALIDMARK;
   mdesc->mode = mode;

   pStream->flags = OSRTSTRMF_INPUT; /* input stream are supported only */
   pStream->id    = OSRTSTRMID_BUFFERED;
   pStream->extra = mdesc;
   pStream->close = cacheClose;
   return 0;
}

EXTRTMETHOD int rtxStreamBufferedRelease (OSCTXT* pctxt) 
{
   OSRTSTREAM *pStream = pctxt->pStream;
   OSRTSTREAM *pUnderStream;
   CacheDesc* mdesc;

   if (0 == pctxt->pStream || pStream->id != OSRTSTRMID_BUFFERED) 
      return LOG_RTERRNEW (pctxt, RTERR_INVPARAM);

   /* return back the underlying stream to context and free all buffers, etc */
   /* do not close the stream! */
   mdesc = (CacheDesc*)pStream->extra;
   pUnderStream = mdesc->pUnderStream;

   rtxMemFreePtr (pctxt, mdesc->pMemBuf);
   rtxMemFreePtr (pctxt, pStream->extra);
   rtxMemFreePtr (pctxt, pStream);

   pctxt->pStream = pUnderStream;
   return 0;
}

EXTRTMETHOD int rtxStreamBufferedSetPreReadBuf 
   (OSCTXT* pctxt, const OSOCTET* pdata, size_t datalen)
{
   OSRTSTREAM *pStream = pctxt->pStream;
   CacheDesc* mdesc;
   OSOCTET* pNewMemBuf;

   if (0 == pctxt->pStream || pStream->id != OSRTSTRMID_BUFFERED) 
      return LOG_RTERRNEW (pctxt, RTERR_INVPARAM);

   mdesc = (CacheDesc*)pStream->extra;

   if (datalen > 0) {
      pNewMemBuf = rtxMemReallocArray (
         mdesc->pctxt, mdesc->pMemBuf, datalen, OSOCTET);
      if (pNewMemBuf == 0)
         return LOG_RTERRNEW (pctxt, RTERR_NOMEM);
      pStream->bufsize = datalen;
      rtxMemHeapMarkSaved (&mdesc->pctxt->pMemHeap, pNewMemBuf, TRUE);
      mdesc->pMemBuf = pNewMemBuf;
      
      OSCRTLMEMCPY (pNewMemBuf, pdata, datalen);
      mdesc->readSize = datalen;
   }
   else {
      rtxMemFreePtr (mdesc->pctxt, mdesc->pMemBuf);
      mdesc->pMemBuf = 0;
      mdesc->readSize = 0;
      pStream->bufsize = 0;
   }
   mdesc->curIndex = 0;
   mdesc->savedIndex = OSRTSTRM_K_INVALIDMARK;
   return 0;
}

EXTRTMETHOD int rtxStreamBufferedPrependReadBuf 
   (OSCTXT* pctxt, const OSOCTET* pdata, size_t datalen)
{
   OSRTSTREAM *pStream = pctxt->pStream;
   CacheDesc* mdesc;
   OSOCTET* pNewMemBuf;

   if (0 == pctxt->pStream || pStream->id != OSRTSTRMID_BUFFERED) 
      return LOG_RTERR (pctxt, RTERR_INVPARAM);

   mdesc = (CacheDesc*)pStream->extra;

   if (datalen > 0) {
      if (datalen <= mdesc->curIndex) {
         mdesc->curIndex -= datalen;
         OSCRTLMEMCPY (mdesc->pMemBuf + mdesc->curIndex, pdata, datalen);
      }
      else {
         pNewMemBuf = rtxMemReallocArray (
            mdesc->pctxt, mdesc->pMemBuf, datalen + mdesc->readSize - mdesc->curIndex, OSOCTET);
         if (pNewMemBuf == 0)
            return LOG_RTERR (pctxt, RTERR_NOMEM);
         mdesc->pMemBuf = pNewMemBuf;
         if (mdesc->savedIndex != OSRTSTRM_K_INVALIDMARK) 
            mdesc->savedIndex += datalen - mdesc->curIndex;
         OSCRTLMEMCPY (mdesc->pMemBuf + datalen, mdesc->pMemBuf, mdesc->readSize - mdesc->curIndex);
         OSCRTLMEMCPY (mdesc->pMemBuf, pdata, datalen);
         mdesc->curIndex = 0;
         rtxMemHeapMarkSaved (&mdesc->pctxt->pMemHeap, pNewMemBuf, TRUE);
         pStream->bufsize = datalen + mdesc->readSize - mdesc->curIndex;
         mdesc->readSize = pStream->bufsize;
      }
   }
   return 0;
}
