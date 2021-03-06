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
 *  Routine name: pu_setFldBitOffset
 *
 *  Description:  This routine sets the bit offset to the current
 *                PER field in the given field record.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct* PER context block structure
 *
 *  Outputs:
 *
 *  None
 *
 *
 **********************************************************************/

EXTPERMETHOD void pu_setFldBitOffset (OSCTXT* pctxt)
{
   PERField* pfld;
   OSRTSListNode* pNode = ACINFO(pctxt)->fieldList.tail;

   if ((pctxt->flags & ASN1TRACE) != 0) {
      if (pNode) {
         pfld = (PERField*) pNode->data;
         if (0 != pfld && 0 == pfld->numbits) {
            pfld->bitOffset = PU_GETCTXTBITOFFSET (pctxt);
            RTDIAGSTRM4 (pctxt,"field '%s' bit offset set to %d\n", 
                    pfld->name, pfld->bitOffset);
         }
      }
   }
}
