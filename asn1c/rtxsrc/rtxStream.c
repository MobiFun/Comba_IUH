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
#include "rtxsrc/rtxStream.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxMemory.h"
#include "rtxsrc/rtxMemBuf.h"
#include "rtxsrc/rtxContext.hh"

#ifdef RTEVAL
#define _CRTLIB
#include "rtxevalsrc/rtxEval.hh"
#else
#define OSRT_CHECK_EVAL_DATE_STAT0(pctxt,stat)
#define OSRT_CHECK_EVAL_DATE_STAT1(pctxt,stat)
#define OSRT_CHECK_EVAL_DATE0(pctxt)
#define OSRT_CHECK_EVAL_DATE1(pctxt)
#endif /* RTEVAL */

EXTRTMETHOD int rtxStreamInit (OSCTXT* pctxt)
{
   pctxt->pStream = rtxMemAllocTypeZ (pctxt, OSRTSTREAM);
   if (pctxt->pStream == NULL) return LOG_RTERRNEW (pctxt, RTERR_NOMEM);

   rtxMemHeapMarkSaved (&pctxt->pMemHeap, pctxt->pStream, TRUE);

   rtxCtxtClearFlag (pctxt, OSDISSTRM);

   LCHECKX (pctxt);
   return 0;
}

EXTRTMETHOD int rtxStreamFlush (OSCTXT* pctxt)
{
   int stat = 0;
   OSRTSTREAM *pStream = pctxt->pStream;

   if (pStream == 0 || !(pStream->flags & OSRTSTRMF_OUTPUT)) 
      return LOG_RTERRNEW (pctxt, RTERR_INVPARAM);

   if (pStream->flush != 0) {
      stat = pStream->flush (pStream);
      if (stat < 0) return LOG_RTERRNEW (pctxt, stat);
   }
   LCHECKX (pctxt);
   return stat;
}

EXTRTMETHOD int rtxStreamClose (OSCTXT* pctxt)
{
   OSRTSTREAM *pStream = pctxt->pStream;
   int stat = 0, stat2 = 0;
   
   if (pStream == 0 || pStream->close == 0) 
      return LOG_RTERRNEW (pctxt, RTERR_NOTINIT);

   if (pStream->flags & OSRTSTRMF_OUTPUT) {
      stat = rtxStreamFlush (pctxt);
   }
   else if (!(pStream->flags & OSRTSTRMF_INPUT)) 
      return LOG_RTERRNEW (pctxt, RTERR_NOTINIT);

   stat2 = pStream->close (pStream);

   pStream->flags = 0;

   rtxMemFreePtr (pctxt, pctxt->pStream);
   pctxt->pStream = 0;

   if ( stat != 0 ) return LOG_RTERR (pctxt, stat);
	else if ( stat2 != 0 ) return LOG_RTERR (pctxt, stat2);
	else return 0;
}

EXTRTMETHOD long rtxStreamWrite 
(OSCTXT* pctxt, const OSOCTET* data, size_t numocts)
{
   OSRTSTREAM *pStream = pctxt->pStream;
   long len;

   if (pStream == 0 || pStream->write == 0 || 
       !(pStream->flags & OSRTSTRMF_OUTPUT)) 
      return LOG_RTERRNEW (pctxt, RTERR_NOTINIT);

   OSRT_CHECK_EVAL_DATE0 (pctxt);

   len = pStream->write (pStream, data, numocts);
   if (len >= 0)
      pStream->ioBytes += len;
   else
      return LOG_RTERRNEW (pctxt, (int)len);

   LCHECKX (pctxt);
   return len;
}

EXTRTMETHOD long rtxStreamRead 
(OSCTXT* pctxt, OSOCTET* pbuffer, size_t bufSize)
{
   OSRTSTREAM *pStream = pctxt->pStream;
   long len;

   if (pStream == 0 || pStream->read == 0 || 
       !(pStream->flags & OSRTSTRMF_INPUT)) 
      return LOG_RTERRNEW (pctxt, RTERR_NOTINIT);

   len = pStream->read (pStream, pbuffer, bufSize);
   if (len >= 0) {
      if (pStream->id != OSRTSTRMID_CTXTBUF)
         pStream->ioBytes += len;
   }
   else
      return LOG_RTERRNEW (pctxt, (int)len);

   OSRT_CHECK_EVAL_DATE1 (pctxt);
   LCHECKX (pctxt);

   return len;
}

EXTRTMETHOD long rtxStreamBlockingRead 
(OSCTXT* pctxt, OSOCTET* pbuffer, size_t readBytes)
{
   OSRTSTREAM *pStream = pctxt->pStream;
   long len;

   OSRT_CHECK_EVAL_DATE0 (pctxt);

   if (pStream == 0 || pStream->blockingRead == 0 || 
       !(pStream->flags & OSRTSTRMF_INPUT)) 
      return LOG_RTERRNEW (pctxt, RTERR_NOTINIT);

   len = pStream->blockingRead (pStream, pbuffer, readBytes);
   if (len >= 0) {
      pStream->ioBytes += len;

      /* If capture enabled, append data to capture buffer */
      if (0 != pStream->pCaptureBuf) {
         int stat;
         if (0 == pbuffer) {
            /* assume context buffer was used */
            pbuffer = OSRTBUFPTR (pctxt);
         }
         stat = rtxMemBufAppend (pStream->pCaptureBuf, pbuffer, len);
         if (0 != stat) LOG_RTERRNEW (pctxt, stat);
      }
   }
   else
      return LOG_RTERRNEW (pctxt, (int)len);

   return len;
}

EXTRTMETHOD int rtxStreamSkip (OSCTXT* pctxt, size_t bytes)
{
   OSRTSTREAM *pStream = pctxt->pStream;
   int stat;

   if (pStream == 0 || !(pStream->flags & OSRTSTRMF_INPUT)) 
      return LOG_RTERRNEW (pctxt, RTERR_INVPARAM);

   if (pStream->skip == 0) 
      return LOG_RTERRNEW (pctxt, RTERR_NOTINIT);

   stat = pStream->skip (pStream, bytes);
   if (stat >= 0)
      pStream->ioBytes += bytes;
   else
      return LOG_RTERRNEW (pctxt, stat);

   return stat;
}

EXTRTMETHOD int rtxStreamGetIOBytes (OSCTXT* pctxt, size_t* pPos)
{
   OSRTSTREAM *pStream = pctxt->pStream;

   if (pStream == 0) 
      return LOG_RTERRNEW (pctxt, RTERR_NOTINIT);

   if (pPos != 0)
      *pPos = pStream->ioBytes;

   return 0;
}

EXTRTMETHOD int rtxStreamMark (OSCTXT* pctxt, size_t readAheadLimit)
{
   OSRTSTREAM *pStream = pctxt->pStream;
   int stat;

   if (pStream == 0) 
      return LOG_RTERRNEW (pctxt, RTERR_INVPARAM);

   if (pStream->mark == 0 || pStream->reset == 0)
      return LOG_RTERRNEW (pctxt, RTERR_NOTSUPP);

   if (pStream->nextMarkOffset != 0) {
      /* move stream pos to end of PDU */
      stat = pStream->reset (pStream);
      if (pStream->skip != 0) 
         stat = pStream->skip (pStream, pStream->nextMarkOffset);
   }
   
   stat = pStream->mark (pStream, readAheadLimit);
   if (stat < 0) return LOG_RTERRNEW (pctxt, stat);
   pStream->flags |= OSRTSTRMF_POSMARKED;
   pStream->nextMarkOffset = 0;
   return 0;
}

EXTRTMETHOD int rtxStreamReset (OSCTXT* pctxt)
{
   OSRTSTREAM *pStream = pctxt->pStream;
   int stat;

   if (pStream == 0) 
      return LOG_RTERRNEW (pctxt, RTERR_INVPARAM);

   if (pStream->mark == 0 || pStream->reset == 0)
      return LOG_RTERRNEW (pctxt, RTERR_NOTSUPP);

   pStream->flags &= ~OSRTSTRMF_POSMARKED;
   
   stat = pStream->reset (pStream);
   if (stat < 0) return LOG_RTERRNEW (pctxt, stat);
   
   pStream->nextMarkOffset = 0;
   
   return 0;
}

EXTRTMETHOD OSBOOL rtxStreamMarkSupported (OSCTXT* pctxt)
{
   OSRTSTREAM *pStream = pctxt->pStream;

   if (pStream == 0 || pStream->mark == 0 || pStream->reset == 0)
      return FALSE;
   return TRUE;
}

EXTRTMETHOD OSBOOL rtxStreamIsOpened (OSCTXT* pctxt)
{
   OSRTSTREAM *pStream = pctxt->pStream;

   if (pStream != 0 && 
      ((pStream->flags & OSRTSTRMF_INPUT) || 
       (pStream->flags & OSRTSTRMF_OUTPUT)))
      return TRUE;
   return FALSE;
}

EXTRTMETHOD OSBOOL rtxStreamIsReadable (OSCTXT* pctxt)
{
   OSRTSTREAM *pStream = pctxt->pStream;
   return (OSBOOL)(pStream != 0 && (pStream->flags & OSRTSTRMF_INPUT));
}

EXTRTMETHOD OSBOOL rtxStreamIsWritable (OSCTXT* pctxt)
{
   OSRTSTREAM *pStream = pctxt->pStream;
   return (OSBOOL)(pStream != 0 && (pStream->flags & OSRTSTRMF_OUTPUT));
}

EXTRTMETHOD void rtxStreamSetCapture (OSCTXT* pctxt, OSRTMEMBUF* pmembuf)
{
   OSRTSTREAM *pStream = pctxt->pStream;
   if (0 != pStream) {
      pStream->pCaptureBuf = pmembuf;

      /* If context-buffer stream and context buffer contains data, 
         append data to capture buffer */
      if (pStream->id == OSRTSTRMID_CTXTBUF && pctxt->buffer.size > 0) {
         rtxMemBufAppend 
            (pStream->pCaptureBuf, pctxt->buffer.data, pctxt->buffer.size);
      }
   }
}

EXTRTMETHOD OSRTMEMBUF* rtxStreamGetCapture (OSCTXT* pctxt)
{
   OSRTSTREAM *pStream = pctxt->pStream;
   return (0 != pStream) ? pStream->pCaptureBuf : 0;
}

