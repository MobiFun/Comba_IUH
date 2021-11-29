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

#include "rtbersrc/xd_common.hh"

/***********************************************************************
 *
 *  Routine name: xd_OpenTypeExt
 *
 *  Description:  This routine decodes an ASN.1 open type 
 *                extension field.  This is an implicit field 
 *                that is added a to a type when an extension 
 *                marker (...) is present at the end of a message 
 *                or when a pair of markers are present in the 
 *                middle with no defined fields (..., ...).
 *
 *
 *  Inputs:
 *
 *  Name        Type                Description
 *  ----        ---------           -----------
 *  pctxt      OSCTXT*           Context block pointer
 *  ccb_p       ASN1CCB*            Context control block pointer
 *  tag         ASN1TAG             Next expected tag value 
 *                                  (or ASN_K_NOTAG if last field)
 *
 *  Outputs:
 *
 *  Name        Type                Description
 *  ----        ---------           -----------
 *  status      int	            Status of operation.  
 *                                  Returned as function result.
 *  pElemList   list*               Pointer to list to which decoded 
 *                                  open type elements will be added.
 *
 **********************************************************************/

int xd_OpenTypeExt (OSCTXT* pctxt, ASN1CCB* ccb_p, ASN1TAG tag, 
                    OSRTDList *pElemList)
{
   int length, stat;

   if (tag == ASN_K_NOTAG) {

      /* Loop through remaining elements in SEQUENCE */

      while (!XD_CHKEND (pctxt, ccb_p)) {
         stat = xd_OpenTypeAppend (pctxt, pElemList); /*!AB 11/06/02 */
         if (stat != 0) return LOG_RTERR (pctxt, stat);
      }
   }
   else {

      /* Loop through elements until matching tag found or some other   */
      /* error occurs..                                                 */

      while ((stat = xd_match (pctxt, tag, &length, 0)) == RTERR_IDNOTFOU) {
         rtxErrReset (pctxt);

         if (XD_CHKEND (pctxt, ccb_p)) { 
            return LOG_RTERR (pctxt, RTERR_ENDOFBUF);
         }
         else {
            stat = xd_OpenTypeAppend (pctxt, pElemList); /*!AB 11/06/02 */
            if (stat != 0) return LOG_RTERR (pctxt, stat);
         }
      }
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }

   return 0;
}
