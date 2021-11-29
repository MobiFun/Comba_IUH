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

#include <stdlib.h>
#include <string.h>
#include "rtxsrc/rtxCtype.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxMemory.h"
#include "rtxsrc/rtxMemBuf.h"

EXTRTMETHOD void rtxMemBufInit (OSCTXT* pCtxt, OSRTMEMBUF* pMemBuf, size_t segsize)
{
   pMemBuf->pctxt = pCtxt;
   pMemBuf->segsize = (0 == segsize) ? OSMBDFLTSEGSIZE : (OSUINT32)segsize;
   pMemBuf->startidx = 0;
   pMemBuf->usedcnt = 0;
   pMemBuf->bufsize = 0;
   pMemBuf->buffer = 0;
   pMemBuf->bitOffset = 0;
   pMemBuf->userState = 0;
   pMemBuf->isDynamic = TRUE;
   pMemBuf->isExpandable = TRUE;
}

EXTRTMETHOD void rtxMemBufInitBuffer (OSCTXT* pCtxt, OSRTMEMBUF* pMemBuf, 
                          OSOCTET* buf, size_t bufsize, size_t segsize)
{
   pMemBuf->pctxt = pCtxt;
   pMemBuf->segsize = (OSUINT32)segsize;
   pMemBuf->startidx = 0;
   pMemBuf->usedcnt = 0;
   pMemBuf->bufsize = (OSUINT32)bufsize;
   pMemBuf->buffer = buf;
   pMemBuf->bitOffset = 0;
   pMemBuf->userState = 0;
   pMemBuf->isDynamic = FALSE;
   pMemBuf->isExpandable = TRUE;
}

EXTRTMETHOD void rtxMemBufFree (OSRTMEMBUF* pMemBuf)
{
   if (pMemBuf->isDynamic) {
      rtxMemFreeArray (pMemBuf->pctxt, pMemBuf->buffer);
      pMemBuf->buffer = 0;
      pMemBuf->bufsize = 0;
   }

   rtxMemBufReset (pMemBuf);      
}

EXTRTMETHOD void rtxMemBufReset (OSRTMEMBUF* pMemBuf)
{
   pMemBuf->usedcnt = 0;
   pMemBuf->startidx = 0;
   pMemBuf->bitOffset = 0;
}

EXTRTMETHOD int rtxMemBufAppend (OSRTMEMBUF* pMemBuf, 
                     const OSOCTET* pdata, size_t nbytes)
{
   int stat = 0;

   if (0 == nbytes) return 0;

   /* Ensure capacity for data */
   stat = rtxMemBufPreAllocate (pMemBuf, nbytes);

   /* Copy data */
   if (stat == 0) {
      if (pdata) {
         OSCRTLMEMCPY (&pMemBuf->buffer[pMemBuf->usedcnt], pdata, nbytes);
         pMemBuf->usedcnt += (OSUINT32)nbytes;
      }
   }
   else return LOG_RTERR (pMemBuf->pctxt, stat);
   return 0;
}

EXTRTMETHOD int rtxMemBufPreAllocate (OSRTMEMBUF* pMemBuf, size_t nbytes)
{
   if (0 == nbytes) return 0;

   /* Ensure capacity for data */
   if ((pMemBuf->usedcnt + nbytes) > pMemBuf->bufsize) {
      OSUINT32 reqbytes = pMemBuf->usedcnt + (OSUINT32)nbytes;
      OSUINT32 nsegs = ((reqbytes - 1) / pMemBuf->segsize) + 1;

      if (pMemBuf->isDynamic && 0 != pMemBuf->buffer) {
         OSOCTET *newbuf = rtxMemReallocArray (pMemBuf->pctxt, 
                                                   pMemBuf->buffer, 
                                                   pMemBuf->segsize * nsegs,
                                                   OSOCTET);
         if (newbuf == 0)
            return LOG_RTERRNEW (pMemBuf->pctxt, RTERR_NOMEM);
         pMemBuf->buffer = newbuf;
      }
      else { /* Do initial mem alloc */
         OSOCTET *oldbuf = pMemBuf->buffer;
         pMemBuf->buffer = rtxMemAllocArray (pMemBuf->pctxt, 
                                                 pMemBuf->segsize * nsegs,
                                                 OSOCTET);
         if (pMemBuf->buffer == 0)
            return LOG_RTERRNEW (pMemBuf->pctxt, RTERR_NOMEM);

         if (oldbuf && pMemBuf->bufsize)
            OSCRTLMEMCPY (pMemBuf->buffer, oldbuf, pMemBuf->bufsize);
            
         rtxMemHeapMarkSaved 
            (&pMemBuf->pctxt->pMemHeap, pMemBuf->buffer, TRUE);
         pMemBuf->isDynamic = TRUE;
      }
      if (0 == pMemBuf->buffer) return LOG_RTERRNEW (pMemBuf->pctxt, RTERR_NOMEM);
      pMemBuf->bufsize = pMemBuf->segsize * nsegs;
   }
   return 0;
}

/**
  Removes leading and trailing white spaces. Buffer should contain 
  16-bit character string without trailing zero.
  Returns the length of resulting buffer.
*/
EXTRTMETHOD int rtxMemBufTrimW (OSRTMEMBUF* pMemBuf) 
{
   OSUNICHAR* pStr = (OSUNICHAR*) (pMemBuf->buffer + pMemBuf->startidx);
   
   /* skip leading white space */

   int i;
   for (i = (int)pMemBuf->startidx; i < (int)pMemBuf->usedcnt &&
      OS_ISSPACE ((char)*pStr); i++, pStr++) 
   {
      pMemBuf->startidx += sizeof (OSUNICHAR);
   }

   /* skip trailing white space */

   pStr = (OSUNICHAR*) (pMemBuf->buffer + pMemBuf->usedcnt - 1);
   for (i = (int)pMemBuf->usedcnt - 1; i > (int)pMemBuf->startidx &&
      OS_ISSPACE ((char)*pStr); i--, pStr--) 
   {
      pMemBuf->usedcnt -= sizeof (OSUNICHAR);
   }
   return pMemBuf->usedcnt - pMemBuf->startidx;
}

EXTRTMETHOD int rtxMemBufSet (OSRTMEMBUF* pMemBuf, OSOCTET value, size_t nbytes)
{
   int stat;   

   if (0 == nbytes) return 0;

   /* Ensure capacity for data */
   stat = rtxMemBufPreAllocate (pMemBuf, nbytes);
   if (stat != 0) return LOG_RTERR (pMemBuf->pctxt, stat);

   /* Set data */
   OSCRTLMEMSET (&pMemBuf->buffer[pMemBuf->usedcnt], value, nbytes);
   pMemBuf->usedcnt += (OSUINT32)nbytes;

   return 0;
}

EXTRTMETHOD OSOCTET* rtxMemBufGetData (OSRTMEMBUF* pMemBuf, int* length) 
{
   if (length != 0)
      *length = (int)(pMemBuf->usedcnt - pMemBuf->startidx);

   return pMemBuf->buffer + pMemBuf->startidx; 
}

EXTRTMETHOD int rtxMemBufGetDataLen (OSRTMEMBUF* pMemBuf) 
{
   return pMemBuf->usedcnt - pMemBuf->startidx;
}

EXTRTMETHOD int rtxMemBufCut (OSRTMEMBUF* pMemBuf, size_t fromOffset, size_t nbytes)
{
   if ((OSUINT32)(fromOffset + nbytes) > pMemBuf->usedcnt)
      return LOG_RTERRNEW (pMemBuf->pctxt, RTERR_INVPARAM);
   OSCRTLMEMCPY (pMemBuf->buffer + pMemBuf->startidx + fromOffset, 
           pMemBuf->buffer + pMemBuf->startidx + fromOffset + nbytes,
           pMemBuf->usedcnt - nbytes);
   pMemBuf->usedcnt -= (OSUINT32)nbytes;
   return 0;
}
 
EXTRTMETHOD OSBOOL rtxMemBufSetExpandable (OSRTMEMBUF* pMemBuf, OSBOOL isExpandable)
{
   OSBOOL wasExpandable = pMemBuf->isExpandable;
   pMemBuf->isExpandable = isExpandable;
   return wasExpandable;
}
