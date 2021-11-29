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
 *  Routine name: xd_count
 *
 *  Description:  This routine counts the elements within a sequence of or
 *                set of constructor field.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  length	int	Length of sequence of or set of constructor field.
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat	int	Routine completion status.  Returned as function
 *                      result.
 *  count	int	Number of elements in field.
 *
 **********************************************************************/

int xd_count (OSCTXT *pctxt, int length, int *count_p)
{ 
   OSRTBuffer   saved_ctxt;
   ASN1CCB      ccb;
   int          stat;

   /* Save current decoding context */

   memcpy (&saved_ctxt, &pctxt->buffer, sizeof(OSRTBuffer));

   /* Count elements */

   *count_p = 0;

   ccb.len = length;
   ccb.ptr = OSRTBUFPTR(pctxt);

   while (!XD_CHKEND (pctxt, &ccb)) {
      if ((stat = xd_NextElement (pctxt)) == 0) {
         (*count_p)++;
      }
      else 
         return LOG_RTERR (pctxt, stat);
   }
      
   /* Restore original message pointer and length */

   memcpy (&pctxt->buffer, &saved_ctxt, sizeof(OSRTBuffer));

   return 0;
}
