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
 *  Routine name: xd_octstr_s  (decode static octet string)
 *
 *  Description:  This routine decodes the octet string at the current
 *                message pointer location and returns its value.  The
 *                value is returned in the buffer pointed to by the given
 *                character buffer pointer.  This routine also advances
 *                the message pointer to the start of the next field.
 *
 *                The routine first checks to see if explicit tagging
 *                is specified.  If yes, it calls xd_match to match
 *                the universal tag for this message type.  If the 
 *                match is not successful, a negative value is returned
 *                to indicate the parse was not successful.
 *
 *                If the match is successful or implicit tagging is
 *                specified, the string is copied into the static buffer
 *                using xd_memcpy.  The numocts field is then set to the
 *                length parsed from the field.  The status result of
 *                the operation is returned.
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
 *  object      char*	Pointer to decoded octet string value.
 *  numocts	int	Number of octets in string.
 *
 **********************************************************************/

int xd_octstr_s (OSCTXT* pctxt, 
                 OSOCTET* object_p, OSUINT32* pnumocts, 
                 ASN1TagType tagging, int length) 
{ 
   int stat = 0;

   if (tagging == ASN1EXPL) {
      if (!XD_MATCH1 (pctxt, ASN_ID_OCTSTR)) {
         return berErrUnexpTag (pctxt, ASN_ID_OCTSTR);
      }
      stat = XD_LEN (pctxt, &length);
      if (stat != 0) LOG_RTERR (pctxt, stat);
   }
     
   /* Check length */
   if (length < 0)
      return LOG_RTERR (pctxt, ASN_E_INVLEN);
   else if ((OSUINT32)length > *pnumocts) 
      return LOG_RTERR (pctxt, RTERR_STROVFLW);

   if (pctxt->flags & ASN1CONSTAG) {
      ASN1CCB ccb;
      OSUINT32 idx = 0, len = (OSUINT32) length;

      ccb.len = length;
      ccb.ptr = OSRTBUFPTR(pctxt);

      while (!XD_CHKEND (pctxt, &ccb)) {
         len = length;
         stat = xd_octstr_s 
            (pctxt, object_p + idx, &len, ASN1EXPL, length);

         if (stat != 0) return LOG_RTERR (pctxt, stat);
         else idx += len;
      }

      /* If not indefinite length, make sure we consumed exactly as  */
      /* many bytes as specified in the constructed length field..   */

      if (length != ASN_K_INDEFLEN) {
         size_t usedBytes = OSRTBUFPTR(pctxt) - ccb.ptr;
         if (usedBytes != (size_t)length)
            return LOG_RTERR (pctxt, ASN_E_INVLEN);
      }

      *pnumocts = idx;
   }
   else if (length > 0) {
      stat = xd_memcpy (pctxt, object_p, length);
      *pnumocts = length;
   }
   else {
      *pnumocts = 0;
   }

   return (0);
} 

