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

/* Calculates the actual length of the octet string, in the constructed 
 * case and if the indefinite length is used. Size - the actual number 
 * of octets used for the storing constructed octet string, length - the 
 * length necessary for the assembled string. 
 * This function is internal, used by OCTET, CHARACTER and BIT STRINGs. */

int xd_consStrIndefLenAndSize 
   (OSCTXT* pctxt, ASN1TAG expectedTag, int* length, int* size) 
{
   OSRTBufSave  savedBufferInfo;
   ASN1TAG tag;
   int     len, ll = 0, stat;
   
   xu_SaveBufferState (pctxt, &savedBufferInfo);

   while ((stat = xd_tag_len (pctxt, &tag, &len, XM_ADVANCE)) == 0) {

      /* check tag value (ED, 5/1/02), (AB, 10/3/02) */

      if ( !(tag == 0 || tag == expectedTag) )
         return LOG_RTERR (pctxt, ASN_E_BADTAG);

      if (len == ASN_K_INDEFLEN) {
         int sz, ll1;
         if ((stat = xd_consStrIndefLenAndSize 
            (pctxt, expectedTag, &ll1, &sz)) != 0)
         {
            return LOG_RTERR(pctxt, stat);
         }
         ll += ll1;
         pctxt->buffer.byteIndex += sz;
      }
      else if (tag == 0 && len == 0) 
         break;
      else if (len > 0) {
         pctxt->buffer.byteIndex += len;
         ll += len;
      }
   }

   if (stat != 0) LOG_RTERR(pctxt, stat);

   *size = (int)
      (pctxt->buffer.byteIndex - savedBufferInfo.byteIndex - 2);/* excl EOC */
   *length = ll;

   xu_RestoreBufferState (pctxt, &savedBufferInfo);

   return 0;
}
