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

#include "rtpersrc/pu_common.hh"

/***********************************************************************
 *
 *  Routine name: pu_addSizeConstraint
 *
 *  Description:  This routine adds the given size constraint to
 *                the context structure.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct* ASN.1 context block structure
 *  psize       struct* Pointer to ASN.1 size constraint structure
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  status      int     Status of operation
 *
 **********************************************************************/

EXTPERMETHOD int pu_addSizeConstraint (OSCTXT* pctxt, Asn1SizeCnst* pSize)
{
   Asn1SizeCnst* lpSize;

   /* If constraint does not already exist, add it */

   if (!ACINFO(pctxt)->pSizeConstraint) {
      ACINFO(pctxt)->pSizeConstraint = pSize;
   }

   /* Otherwise, check to make sure given constraint is larger than     */
   /* the existing constraint..                                         */

   else {
      lpSize = pSize;
      while (lpSize) {
         if (ACINFO(pctxt)->pSizeConstraint->lower < lpSize->lower ||
             ACINFO(pctxt)->pSizeConstraint->upper > lpSize->upper) 
         {
            return LOG_RTERR (pctxt, RTERR_CONSVIO);
         }
         lpSize = lpSize->next;
      }
   }

   return 0;
}
