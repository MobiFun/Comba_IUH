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
 *  Routine name: xd_bitstr_s  (decode static bit string)
 *
 *  Description:  This routine decodes the bit string at the current
 *                message pointer location and returns its value.  The
 *                value is returned in the "ASNBITSTR" structure.  This
 *                structure contains a value for the number of bits and
 *                a pointer to the decoded bit string.  The routine    
 *                also advances the message pointer to the start of the
 *                the next field.
 *
 *                The routine first checks to see if explicit tagging
 *                is specified.  If yes, it calls xd_match to match
 *                the universal tag for this message type.  If the
 *                match is not successful, a negative value is returned
 *                to indicate the parse was not successful.
 *
 *                If the match is successful or implicit tagging is
 *                specified, the first byte of the data value is fetched.
 *                This byte contains a value indicating the number of bits
 *                in the last octet that are unused.  Dynamic memory is
 *                then allocated for the bit string and xd_memcpy      
 *                is called to copy the string from the message to the 
 *                allocated memory.  The number of bits is calculated by
 *                multiplying the number of octets times eight bits/octet
 *                and then subtracting the number of unused bits obtained
 *                above.  The number of bits and dynamic memory pointer  
 *                are passed back to the caller via the "ASNBITSTR" 
 *                structure.  The actual length of the string in bytes is
 *                returned as the function result.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt	struct	Pointer to ASN.1 context block structure
 *  tagging     enum    Specifies whether element is implicitly or
 *                      explicitly tagged.
 *  length      int     Length of data to retrieve.  Valid for implicit
 *                      case only.
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat	int	Status of operation.  Returned as function result.
 *  object      char*	Decoded bit string value.
 *  numbits	int	Number of bits in string.
 *
 **********************************************************************/
int xd_bitstr_s (OSCTXT* pctxt, 
                 OSOCTET* object_p, OSUINT32* numbits_p, 
                 ASN1TagType tagging, int length) 
{ 
   int bufsiz = (*numbits_p - 1) / 8 + 1;
   int stat = 0;
   OSOCTET b = 8;

   if (tagging == ASN1EXPL) {
      if (!XD_MATCH1 (pctxt, ASN_ID_BITSTR)) {
         return berErrUnexpTag (pctxt, ASN_ID_BITSTR);
      }
      stat = XD_LEN (pctxt, &length);
      if (stat != 0) LOG_RTERR (pctxt, stat);
   }

   if (pctxt->flags & ASN1CONSTAG) { /* constructed case */
      ASN1CCB ccb;
      int idx = 0, oidx = -1, len;

      ccb.len = length;
      ccb.ptr = OSRTBUFPTR(pctxt);

      while (!XD_CHKEND (pctxt, &ccb)) {
         if ((stat = xd_match1 (pctxt, ASN_ID_BITSTR, &len)) != 0)
            return LOG_RTERR (pctxt, stat);
         
         if ((int)(idx + len) == bufsiz + 1) { /* last segment detection */
            if ((stat = XD_MEMCPY1 (pctxt, &b)) != 0)  /* read unused bit count */
               return LOG_RTERR (pctxt, stat);
            len --;
            oidx = -1;
         }
         else oidx = idx;
         if (idx + len <= bufsiz) 
            stat = xd_memcpy (pctxt, object_p + idx, len);
         else stat = RTERR_STROVFLW;

         if (stat != 0) return LOG_RTERR (pctxt, stat);
         else idx += len;
      }
      if (oidx >= 0 && idx - oidx > 0) { /* if unused bit count wasn't fetched... */
         b = object_p [oidx];
         memcpy (object_p + oidx, object_p + oidx + 1, idx - oidx - 1);
         idx --;
      }
      if (b <= 7) { /* initial octet should be 0..7, !AB (11/06/02) */
         *numbits_p = (idx * 8) - b;

         /* If not indefinite length, make sure we consumed exactly as  */
         /* many bytes as specified in the constructed length field..   */

         if (length != ASN_K_INDEFLEN) {
            size_t usedBytes = OSRTBUFPTR(pctxt) - ccb.ptr;
            if (usedBytes != (size_t)length)
               return LOG_RTERR (pctxt, ASN_E_INVLEN);
         }
      }
      else
         return LOG_RTERR (pctxt, RTERR_BADVALUE);
   }
   else if (length > 0) { /* primitive case */
      if ((stat = XD_MEMCPY1 (pctxt, &b)) == 0) {
         length--;  /* adjust by 1; first byte is unused bit count */
         if (length == 0) {
            if (0 == b)
               *numbits_p = 0;
            else
               stat = ASN_E_INVLEN;
         }
         if (stat == 0) {
            if (b <= 7) { /* initial octet should be 0..7, !AB (11/05/02) */
               if (length <= bufsiz) {
                  stat = xd_memcpy (pctxt, object_p, length);
                  *numbits_p = (length * 8) - b;
               }
               else
                  stat = RTERR_STROVFLW;
            }
            else
               stat = RTERR_BADVALUE;
         }
      }
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }
   else if (length == 0)
      *numbits_p = 0;
   else
      return LOG_RTERR (pctxt, ASN_E_INVLEN);

   return 0;
} 
