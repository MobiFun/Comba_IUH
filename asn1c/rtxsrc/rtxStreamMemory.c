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
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxMemory.h"
#include "rtxsrc/rtxStreamMemory.h"

typedef struct MemDesc {
   OSCTXT*  pctxt;
   OSOCTET* pMemBuf;
   size_t   curIndex;
   size_t   bufSize;
   OSBOOL   attached;
   size_t   savedIndex;
} MemDesc;

#define MEMBUF_GROWTH 512

static long memWrite (OSRTSTREAM* pStream, const OSOCTET* data, size_t numocts)
{
   MemDesc* mdesc = (MemDesc*)pStream->extra;
   size_t toWrite = numocts;

   if (pStream->id != OSRTSTRMID_MEMORY || !(pStream->flags & OSRTSTRMF_OUTPUT)) 
      return RTERR_INVPARAM;

   if (mdesc->attached) { /* fixed memory buffer is used */
      if (toWrite > mdesc->bufSize - mdesc->curIndex)
         return RTERR_BUFOVFLW;
   }
   else { /* dynamic buffer */
      if (mdesc->curIndex + numocts > mdesc->bufSize) {
         size_t newSize = (mdesc->curIndex + numocts + MEMBUF_GROWTH);
         OSOCTET* newBuf = rtxMemReallocArray (
            mdesc->pctxt, mdesc->pMemBuf, newSize, OSOCTET);
         if (newBuf == NULL) return RTERR_NOMEM;
         mdesc->pMemBuf = newBuf;
         mdesc->bufSize = newSize;
         rtxMemHeapMarkSaved 
            (&mdesc->pctxt->pMemHeap, mdesc->pMemBuf, TRUE);
      }
   }

   OSCRTLMEMCPY (mdesc->pMemBuf + mdesc->curIndex, data, toWrite);
   mdesc->curIndex += toWrite;
   return 0;
}

static long memRead (OSRTSTREAM* pStream, OSOCTET* pbuffer, size_t bufSize)
{
   MemDesc* mdesc = (MemDesc*)pStream->extra;
   size_t readBytes;

   if (pStream->id != OSRTSTRMID_MEMORY || !(pStream->flags & OSRTSTRMF_INPUT))
      return RTERR_INVPARAM;

   readBytes = (bufSize < (mdesc->bufSize - mdesc->curIndex)) ? 
      bufSize : (mdesc->bufSize - mdesc->curIndex);
   OSCRTLMEMCPY (pbuffer, mdesc->pMemBuf + mdesc->curIndex, readBytes);
   mdesc->curIndex += readBytes;
   return (long)readBytes;
}

static int memSkip (OSRTSTREAM* pStream, size_t skipBytes)
{
   MemDesc* mdesc = (MemDesc*)pStream->extra;

   if (pStream->id != OSRTSTRMID_MEMORY || !(pStream->flags & OSRTSTRMF_INPUT))
      return RTERR_INVPARAM;
   if (skipBytes > (mdesc->bufSize - mdesc->curIndex))
      return RTERR_BUFOVFLW;
   mdesc->curIndex += skipBytes;
   return 0;
}

static int memClose (OSRTSTREAM* pStream)
{
   MemDesc* mdesc = (MemDesc*)pStream->extra;

   if (pStream->id != OSRTSTRMID_MEMORY) 
      return RTERR_INVPARAM;
   if (!mdesc->attached) {
      rtxMemFreeArray (mdesc->pctxt, mdesc->pMemBuf);
   }
   rtxMemFreePtr (mdesc->pctxt, pStream->extra);
   return 0;
}

static int memMark (OSRTSTREAM* pStream, size_t readAheadLimit)
{
   MemDesc* mdesc = (MemDesc*)pStream->extra;

   if (pStream->id != OSRTSTRMID_MEMORY || !(pStream->flags & OSRTSTRMF_INPUT))
      return RTERR_INVPARAM;
   mdesc->savedIndex = mdesc->curIndex;
   pStream->readAheadLimit = readAheadLimit;
   pStream->markedBytesProcessed = pStream->bytesProcessed;
   return 0;
}

static int memReset (OSRTSTREAM* pStream)
{
   MemDesc* mdesc = (MemDesc*)pStream->extra;

   if (mdesc->savedIndex == OSRTSTRM_K_INVALIDMARK) 
      return RTERR_INVPARAM;

   mdesc->curIndex = mdesc->savedIndex;
   pStream->bytesProcessed = pStream->markedBytesProcessed;
   mdesc->savedIndex = 0;
   pStream->readAheadLimit = INT_MAX;
   pStream->flags |= OSRTSTRMF_POSMARKED;
   return 0;
}

EXTRTMETHOD int rtxStreamMemoryCreate (OSCTXT* pctxt, OSUINT16 flags)
{
   OSRTSTREAM *pStream;
   MemDesc* mdesc;

   if (0 == pctxt->pStream) {
      int stat = rtxStreamInit (pctxt);
      if (0 != stat) return LOG_RTERR (pctxt, stat);
   }
   pStream = pctxt->pStream;

   if (flags & OSRTSTRMF_OUTPUT) {
      pStream->write = memWrite;
      pStream->flush = 0;
   }
   else if (flags & OSRTSTRMF_INPUT) {
      pStream->read = memRead;
      pStream->blockingRead  = memRead;
      pStream->skip = memSkip;
      pStream->mark = memMark;
      pStream->reset = memReset;
      pctxt->buffer.size = 0;
   }
   else 
      return LOG_RTERRNEW (pctxt, RTERR_INVPARAM);

   mdesc = rtxMemAllocType (pctxt, MemDesc);
   if (mdesc == NULL)
      return LOG_RTERRNEW (pctxt, RTERR_NOMEM);
   rtxMemHeapMarkSaved (&pctxt->pMemHeap, mdesc, TRUE);
   mdesc->pctxt = pctxt;
   mdesc->pMemBuf = 0;
   mdesc->bufSize = 0;
   mdesc->curIndex = 0;
   mdesc->attached = FALSE;
   mdesc->savedIndex = 0;

   pStream->flags = (OSUINT16) (flags | OSRTSTRMF_POSMARKED);
   pStream->id    = OSRTSTRMID_MEMORY;
   pStream->extra = mdesc;
   pStream->close = memClose;
   return 0;
}

EXTRTMETHOD int rtxStreamMemoryAttach (OSCTXT* pctxt, OSOCTET* pMemBuf, 
                           size_t bufSize, OSUINT16 flags)
{
   OSRTSTREAM *pStream;
   MemDesc* mdesc;

   if (0 == pctxt->pStream) {
      int stat = rtxStreamInit (pctxt);
      if (0 != stat) return LOG_RTERR (pctxt, stat);
   }
   pStream = pctxt->pStream;

   if (pMemBuf == 0 || 
      (!(flags & OSRTSTRMF_OUTPUT) && !(flags & OSRTSTRMF_INPUT)))
      return LOG_RTERRNEW (pctxt, RTERR_INVPARAM);

   mdesc = rtxMemAllocType (pctxt, MemDesc);
   if (mdesc == NULL)
      return LOG_RTERRNEW (pctxt, RTERR_NOMEM);
   rtxMemHeapMarkSaved (&pctxt->pMemHeap, mdesc, TRUE);
   mdesc->pctxt = pctxt;
   mdesc->pMemBuf = pMemBuf;
   mdesc->bufSize = bufSize;
   mdesc->curIndex = 0;
   mdesc->attached = TRUE;
   mdesc->savedIndex = 0;

   if (flags & OSRTSTRMF_OUTPUT) {
      pStream->write = memWrite;
      pStream->flush = 0;
   }
   else if (flags & OSRTSTRMF_INPUT) {
      pStream->read  = memRead;
      pStream->blockingRead  = memRead;
      pStream->skip  = memSkip;
      pStream->mark = memMark;
      pStream->reset = memReset;
      pctxt->buffer.size = 0;
   }
   pStream->flags = (OSUINT16) (flags | OSRTSTRMF_POSMARKED);
   pStream->id    = OSRTSTRMID_MEMORY;
   pStream->extra = mdesc;
   pStream->close = memClose;
   return 0;
}


EXTRTMETHOD OSOCTET* rtxStreamMemoryGetBuffer (OSCTXT* pctxt, size_t* pSize) 
{
   OSRTSTREAM *pStream = pctxt->pStream;
   MemDesc* mdesc;

   if (pStream == 0 || pStream->extra == 0 || 
      (!(pStream->flags & OSRTSTRMF_OUTPUT) && 
       !(pStream->flags & OSRTSTRMF_INPUT)))
      return 0;

   mdesc = (MemDesc*)pStream->extra;
   if (pSize != 0) {
      if (pStream->flags & OSRTSTRMF_INPUT)
         *pSize = mdesc->bufSize;
      else
         *pSize = mdesc->curIndex;
   }
   return mdesc->pMemBuf;
}

EXTRTMETHOD int rtxStreamMemoryCreateReader 
   (OSCTXT* pctxt, OSOCTET* pMemBuf, size_t bufSize)
{
   if (pMemBuf == 0 || bufSize == 0) {
      return LOG_RTERRNEW (pctxt, RTERR_INVPARAM);
   }
   else {
      return rtxStreamMemoryAttach 
         (pctxt, pMemBuf, bufSize, OSRTSTRMF_INPUT);
   }
}

EXTRTMETHOD int rtxStreamMemoryCreateWriter 
   (OSCTXT* pctxt, OSOCTET* pMemBuf, size_t bufSize)
{
   if (pMemBuf == 0 || bufSize == 0) {
      return rtxStreamMemoryCreate (pctxt, OSRTSTRMF_OUTPUT);
   }
   else {
      return rtxStreamMemoryAttach 
         (pctxt, pMemBuf, bufSize, OSRTSTRMF_OUTPUT);
   }
}
