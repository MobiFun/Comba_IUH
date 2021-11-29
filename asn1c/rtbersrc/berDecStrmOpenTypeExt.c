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

#include "rtbersrc/xsd_common.hh"

int berDecStrmOpenTypeExt (OSCTXT *pctxt, ASN1CCB* ccb_p, ASN1TAG tag, 
                           OSRTDList *pElemList)
{
   int length, stat;

   if (tag == ASN_K_NOTAG) {

      /* Loop through remaining elements in SEQUENCE */

      while (!BS_CHKEND (pctxt, ccb_p)) {
         stat = berDecStrmOpenTypeAppend (pctxt, pElemList); /*!AB 11/06/02 */
         if (stat != 0) return LOG_RTERR (pctxt, stat);
      }

      /* !AB, 07/09/2004 */
      if (ccb_p->stat != 0) 
         return LOG_RTERR (pctxt, ccb_p->stat);
   }
   else {

      /* Loop through elements until matching tag found or some other   */
      /* error occurs..                                                 */

      while ((stat = berDecStrmMatchTag (pctxt, tag, &length, FALSE)) == 
              RTERR_IDNOTFOU) 
      {
         rtxErrReset(pctxt);

         if (BS_CHKEND (pctxt, ccb_p)) { 
            return LOG_RTERR (pctxt, RTERR_ENDOFBUF);
         }
         else {
            stat = berDecStrmOpenTypeAppend (pctxt, pElemList); /*!AB 11/06/02 */
            if (stat != 0) return LOG_RTERR (pctxt, stat);
         }
      }
      rtxErrReset(pctxt);
   }

   return 0;
} 

