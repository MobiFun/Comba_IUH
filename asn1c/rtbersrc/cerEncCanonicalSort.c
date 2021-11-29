/*
 * Copyright (c) 1997-2009 Objective Systems, Inc.
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

#include "rtbersrc/xse_common.hh"
#include "rtxsrc/rtxStreamMemory.h"

/***********************************************************************
 *
 *  CER ENCODE FUNCTIONS
 *
 **********************************************************************/

int cerEncCanonicalSort (OSCTXT* pctxt, OSCTXT* pMemCtxt, OSRTSList* pList)
{
   OSBOOL swap = TRUE, swapped = FALSE;
   OSRTSListNode *pNode1, *pNode2;
   Asn1BufLocDescr *pComponent1, *pComponent2;
   OSOCTET *pelem1, *pelem2, *pBuf;
   int cmplen, result, stat = 0;
   size_t totalSize;
   void* ptmp;

   /* Sort elements */

   pBuf = rtxStreamMemoryGetBuffer (pMemCtxt, &totalSize);

   /* Sort elements */

   while (swap) {
      swap = FALSE;
      pNode1 = 0;
      pNode2 = pList->head;

      while (pNode2) {
         if (pNode1) {
            pComponent1 = (Asn1BufLocDescr*) pNode1->data;
            pComponent2 = (Asn1BufLocDescr*) pNode2->data;

            cmplen = OSRTMIN (pComponent1->numocts, pComponent2->numocts);

            /* Calculate encode buffer location pointers */
            pelem1 = pBuf + pComponent1->offset;
            pelem2 = pBuf + pComponent2->offset;

            result = memcmp (pelem1, pelem2, cmplen);
            if (result == 0)
               result = (pComponent1->numocts - pComponent2->numocts);
            if (result > 0) {
               /* swap the data, not node */
               ptmp = pNode1->data;
               pNode1->data = pNode2->data;
               pNode2->data = ptmp;
               swap = swapped = TRUE;
            }
         }
         pNode1 = pNode2;
         pNode2 = pNode2->next;
      }
   }

   /* If at least one element was swapped.. */

   if (swapped) {

      /* Write sorted elements */

      pNode1 = pList->head;
      while (pNode1) {
         pComponent1 = (Asn1BufLocDescr*) pNode1->data;

         if (stat == 0) {
            stat = rtxStreamWrite (pctxt, 
               pBuf + pComponent1->offset, pComponent1->numocts);
         }

         rtxMemFreePtr (pctxt, pComponent1);
         pNode2 = pNode1;
         pNode1 = pNode2->next;
         rtxMemFreePtr (pctxt, pNode2);
      }
   }
   else {
      /* Write buffer "as is" */
      stat = rtxStreamWrite (pctxt, pBuf, totalSize);

      /* Clean up memory */
      pNode1 = pList->head;
      while (pNode1) {
         pComponent1 = (Asn1BufLocDescr*) pNode1->data;
         rtxMemFreePtr (pctxt, pComponent1);
         pNode2 = pNode1;
         pNode1 = pNode2->next;
         rtxMemFreePtr (pctxt, pNode2);
      }
   }

   LCHECKBER (pctxt);

   if (stat != 0) return LOG_RTERR (pctxt, stat);
   return 0;
}

void cerGetBufLocDescr (OSCTXT *pctxt, Asn1BufLocDescr* pDescr) 
{ 
   size_t totalSize;
   /* here we don't need flush stream, since the call to this function should be
      either with empty buffer or after "cerAddBufLocDescr" */
   rtxStreamMemoryGetBuffer (pctxt, &totalSize);
   pDescr->offset = (int)totalSize;
}

void cerAddBufLocDescr (OSCTXT *pctxt, OSRTSList* pElemList, 
                        Asn1BufLocDescr* pDescr) 
{ 
   Asn1BufLocDescr* pbuf;
   size_t totalSize;
   rtxStreamFlush (pctxt); /* flush the internal buffer to memory stream's buffer */
   rtxStreamMemoryGetBuffer (pctxt, &totalSize); /* we only need size */

   pbuf = (Asn1BufLocDescr*) rtxMemAlloc (pctxt, sizeof(Asn1BufLocDescr));
   if (pbuf == 0) return;
   memcpy (pbuf, pDescr, sizeof (*pbuf));
   pbuf->numocts = (OSUINT32)(totalSize - pbuf->offset);
   rtxSListAppend (pElemList, pbuf);
}

