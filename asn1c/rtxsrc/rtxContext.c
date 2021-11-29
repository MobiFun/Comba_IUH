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

/* Run-time utility functions */

#include <stdarg.h>
#include <stdlib.h>
#include "rtxsrc/rtxCommon.hh"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxErrCodes.h"
#include "rtxsrc/rtxStream.h"

#ifdef RTEVAL
#define _CRTLIB
#include "rtxevalsrc/rtxEval.hh"
#else
#define OSRT_CHECK_EVAL_DATE_STAT0(pctxt,stat)
#define OSRT_CHECK_EVAL_DATE_STAT1(pctxt,stat)
#define OSRT_CHECK_EVAL_DATE0(pctxt)
#define OSRT_CHECK_EVAL_DATE1(pctxt)
#endif /* RTEVAL */

/* Run-time context */

EXTRTMETHOD int rtxInitContextBuffer 
(OSCTXT* pctxt, OSOCTET* bufaddr, size_t bufsiz)
{
   if (pctxt->initCode != OSCTXTINIT) {
      return LOG_RTERRNEW (pctxt, RTERR_NOTINIT);
   }
   if (bufaddr == 0) {
      /* dynamic buffer */
      if (bufsiz == 0) bufsiz = OSRTENCBUFSIZ;

      pctxt->buffer.data = rtxMemAllocArray (pctxt, bufsiz, OSOCTET);
      if (!pctxt->buffer.data) return LOG_RTERRNEW (pctxt, RTERR_NOMEM);

      pctxt->buffer.size = bufsiz;
      pctxt->buffer.dynamic = TRUE;
   }
   else {
      /* static buffer */
      pctxt->buffer.data = (OSOCTET*) bufaddr;
      pctxt->buffer.size = bufsiz;
      pctxt->buffer.dynamic = FALSE;
   }

   OSRT_CHECK_EVAL_DATE1 (pctxt);
   LCHECKX (pctxt);

   pctxt->buffer.byteIndex = 0;
   pctxt->buffer.bitOffset = 8;

   return 0;
}

EXTRTMETHOD int rtxInitContext (OSCTXT* pctxt) 
{
   rtxErrInit ();  /* initialize error processing */
   rtxPreInitContext (pctxt);
   
   rtxMemHeapCreate (&pctxt->pMemHeap);
   return 0;
}

EXTRTMETHOD int rtxInitThreadContext (OSCTXT* pctxt, const OSCTXT* pSrcCtxt) 
{
   rtxInitContext (pctxt);
   pctxt->pGlobalData = pSrcCtxt->pGlobalData;
   return 0;
}

EXTRTMETHOD int rtxPreInitContext (OSCTXT* pctxt) 
{
   /* void* pudata = pctxt->pUserData; */
   OSCRTLMEMSET (pctxt, 0, sizeof(OSCTXT));
   /* pctxt->pUserData = pudata; */
   
   OSRT_CHECK_EVAL_DATE0 (pctxt);

   pctxt->initCode = OSCTXTINIT;
   return 0;
}

EXTRTMETHOD int rtxCheckContext (OSCTXT* pctxt)
{
   if (pctxt->initCode != OSCTXTINIT) {
      return RTERR_NOTINIT;
   }
   OSRT_CHECK_EVAL_DATE1 (pctxt);
   LCHECKX (pctxt);
   return 0;
}

static void rtxFreeAppInfo (OSCTXT* pctxt, void* pAppInfo)
{
   if (0 != pAppInfo) {
      /* The first element of pAppInfo always MUST BE a pointer to 
         free function. */
      OSFreeCtxtAppInfoPtr freeFunc = *(OSFreeCtxtAppInfoPtr*)pAppInfo;
      if (0 != freeFunc) {
         freeFunc (pctxt);
      }
      rtxMemFreePtr (pctxt, pAppInfo);
   }
}

EXTRTMETHOD void rtxFreeContext (OSCTXT* pctxt)
{
   OSBOOL saveBuf = (OSBOOL)((pctxt->flags & OSSAVEBUF) != 0);

   if (pctxt->buffer.dynamic && pctxt->buffer.data) {
      if (saveBuf) {
         rtxMemHeapMarkSaved (&pctxt->pMemHeap, pctxt->buffer.data, TRUE);
      }
      else {
         rtxMemFreePtr (pctxt, pctxt->buffer.data);
      }
   }

#ifndef _NO_STREAM
   rtxStreamRelease (pctxt);
#endif
#ifndef _COMPACT
   rtxErrReset (pctxt);
#endif
   rtxFreeAppInfo (pctxt, pctxt->pXMLInfo);
   rtxFreeAppInfo (pctxt, pctxt->pASN1Info);
   rtxFreeAppInfo (pctxt, pctxt->pEXIInfo);

   if (0 != pctxt->gblFreeFunc) {
      pctxt->gblFreeFunc (pctxt);
   }

   rtxMemHeapRelease (&pctxt->pMemHeap);

   pctxt->initCode = 0;
}

EXTRTMETHOD void rtxCopyContext (OSCTXT* pdest, OSCTXT* psrc)
{
   OSCRTLMEMCPY (&pdest->buffer, &psrc->buffer, sizeof(OSRTBuffer));
   pdest->flags = psrc->flags;
   pdest->key = psrc->key;
   pdest->keylen = psrc->keylen;
}

EXTRTMETHOD int rtxCtxtPushElemName 
(OSCTXT* pctxt, const OSUTF8CHAR* elemName)
{
   /* Add name to element name stack in context */
   return rtxDListAppend (pctxt, &pctxt->elemNameStack, (void*)elemName) ?
      0 : RTERR_NOMEM;
}

EXTRTMETHOD const OSUTF8CHAR* rtxCtxtPopElemName (OSCTXT* pctxt)
{
   const OSUTF8CHAR* elemName = 0;
   if (pctxt->elemNameStack.count > 0) {
      elemName = (const OSUTF8CHAR*) pctxt->elemNameStack.tail->data;
      rtxDListFreeNode 
         (pctxt, &pctxt->elemNameStack, pctxt->elemNameStack.tail);
   }
   return elemName;
}

EXTRTMETHOD int rtxCtxtSetBufPtr 
(OSCTXT* pctxt, OSOCTET* bufaddr, size_t bufsiz)
{
   int stat = rtxInitContextBuffer (pctxt, bufaddr, bufsiz);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   rtxCtxtSetFlag (pctxt, OSDISSTRM); /* disable stream operations */
   pctxt->state = 0;

   OSRT_CHECK_EVAL_DATE0 (pctxt);
   LCHECKX (pctxt);

   return 0;
}

EXTRTMETHOD void rtxCtxtSetFlag (OSCTXT* pctxt, OSUINT32 mask)
{
   pctxt->flags |= mask;
}

EXTRTMETHOD void rtxCtxtClearFlag (OSCTXT* pctxt, OSUINT32 mask)
{
   pctxt->flags &= ~mask;
}

/* Private function to assign memory heap in destination context (pctxt) 
   to be that of the source context (pSrcCtxt). */
void rtxCtxtSetMemHeap (OSCTXT* pctxt, OSCTXT* pSrcCtxt)
{
   if (pctxt == 0 || pSrcCtxt == 0 || 
       pSrcCtxt->pMemHeap == pctxt->pMemHeap) return;
   rtxMemHeapRelease (&pctxt->pMemHeap);
   pctxt->pMemHeap = pSrcCtxt->pMemHeap;
   rtxMemHeapAddRef (&pctxt->pMemHeap);
}

#if 0
static void rtxResetAppInfo (OSCTXT* pctxt, void* pAppInfo)
{
   if (0 != pAppInfo) {
      /* The second element of pAppInfo always MUST BE a pointer to 
         a context reset function. */
      OSResetCtxtAppInfoPtr resetFunc = 
         *((OSResetCtxtAppInfoPtr*)pAppInfo + 1);

      if (0 != resetFunc) {
         resetFunc (pctxt);
      }
   }
}

EXTRTMETHOD void rtxResetContext (OSCTXT* pctxt)
{
   rtxResetAppInfo (pctxt, pctxt->pXMLInfo);
   rtxResetAppInfo (pctxt, pctxt->pASN1Info);
   rtxResetAppInfo (pctxt, pctxt->pEXIInfo);
   rtxMemHeapReset (&pctxt->pMemHeap);
}
#endif

#ifdef RTEVAL
#include "rtxevalsrc/rtxEval.c"
#endif
