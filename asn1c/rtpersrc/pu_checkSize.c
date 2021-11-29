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
 *  Routine name: pu_checkSize 
 *
 *  Description:  This routine checks the given size against the size
 *                constraint list.  It will return the constraint the
 *                value falls within.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct* ASN.1 context block structure
 *  value       int     Size value
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  sizeCnst    struct* Pointer to matching constraint structure
 *  extendable  bool*   Indicates size is extendable
 *
 **********************************************************************/

EXTPERMETHOD OSBOOL pu_isExtendableSize (Asn1SizeCnst* pSizeList)
{
   Asn1SizeCnst* lpSize = pSizeList;
   while (lpSize) {
      if (lpSize->extended)
         return TRUE;
      else
         lpSize = lpSize->next;
   }
   return FALSE;
}

EXTPERMETHOD OSBOOL pu_isFixedSize (Asn1SizeCnst* pSizeList)
{
   Asn1SizeCnst* lpSize = pSizeList;
   if (lpSize && !lpSize->extended && !lpSize->next) {
      return (OSBOOL) (lpSize->lower == lpSize->upper);
   }
   return FALSE;
}

EXTPERMETHOD Asn1SizeCnst* pu_checkSize (Asn1SizeCnst* pSizeList, OSUINT32 value, 
                            OSBOOL* pExtendable)
{
   Asn1SizeCnst* lpSize = pSizeList;
   *pExtendable = pu_isExtendableSize (lpSize);

   while (lpSize) {
      if (value >= lpSize->lower && value <= lpSize->upper) {
         return (lpSize);
      }
      else lpSize = lpSize->next;
   }

   return 0;
}
