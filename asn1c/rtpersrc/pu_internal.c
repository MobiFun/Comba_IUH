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
 *  Routine name: pu_BitAndOctetStringAligmentTest
 *
 *  Description:  This routine test various conditions to determine 
 *                if a bit or octet string should be aligned on a 
 *                byte boundary.  It is assumed that aligned encoding 
 *                is being used if this routine is invoked.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pSizeList   struct* Pointer to ASN.1 size constraint structure 
 *                      from context.
 *  itemCount   int     Numbers of items (bits or octets) encoded or 
 *                      parsed from message.
 *  bitStrFlag  bool    Flag indicating call is being made for a bit 
 *                      string (false for octet string).
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  status      int     Status of operation.  Returned as function result.
 *  pAlignFlag  bool*   Flag indicating byte alignment should be 
 *                      performed.
 *
 *
 **********************************************************************/

int pu_BitAndOctetStringAlignmentTest (Asn1SizeCnst* pSizeList, 
                                              OSUINT32 itemCount, 
                                              OSBOOL bitStrFlag,
                                              OSBOOL* pAlignFlag)
{
   OSUINT32 threshold = (bitStrFlag) ? 16 : 2;

   if (pSizeList == 0 || itemCount > threshold) 
      *pAlignFlag = TRUE;
   else if (pu_isFixedSize(pSizeList)) 
      *pAlignFlag = FALSE;
   else {

      /* Variable length case: check size.. no alignment required if    */
      /* lower == upper and not extended..                              */

      OSBOOL extended;
      Asn1SizeCnst* pSize = pu_checkSize (pSizeList, itemCount, &extended);

      if (pSize != 0)
         *pAlignFlag = (OSBOOL)
            ((pSize->upper != pSize->lower) || pSize->extended);
      else {
         /* Note: we never should get here because constraint           */
         /* violation should have been caught when length was encoded   */
         /* or decoded..                                                */
         return RTERR_CONSVIO;
      }
   }

   return (0);
}
