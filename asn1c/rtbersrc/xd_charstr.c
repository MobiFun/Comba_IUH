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
 *  Routine name: xd_charstr
 *
 *  Description:  The following function decodes a value of a 
 *                useful character string useful type.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt	struct	Pointer to ASN.1 context block structure
 *  tagging     enum    Specifies whether element is implicitly or
 *                      explicitly tagged.
 *  tag         ASN1TAG ASN.1 tag to match before decoding the type.
 *                      Valid for explicit case only.
 *  length      int     Length of data to retrieve.  Valid for implicit
 *                      case only.
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat	int	Status of operation.  Returned as function result.
 *  object      bool    Decoded string value.
 *
 **********************************************************************/

int xd_charstr (OSCTXT* pctxt, const char** object_p,
                ASN1TagType tagging, ASN1TAG tag, int length)
{
   int stat = 0;
   int size, ll = 0, isConstructedTag;

   if (tagging == ASN1EXPL) {
      if ((stat = xd_match1 (pctxt, ASN1TAG2BYTE(tag), &length)) < 0)
         /* RTERR_IDNOTFOU will be logged later, by the generated code, 
            or reset by rtxErrReset (for optional seq elements). */
         return (stat == RTERR_IDNOTFOU) ? stat : LOG_RTERR (pctxt, stat);
   }
   isConstructedTag = (int)((pctxt->flags & ASN1CONSTAG) != 0);

   /* For an indefinite length message, need to get the actual 	*/
   /* length by parsing tags until the end of the message is 	*/
   /* reached..							*/
   if (length == ASN_K_INDEFLEN) {  /* indefinite length message */
      if ((stat = xd_consStrIndefLenAndSize (pctxt, TM_UNIV|ASN_ID_OCTSTR, 
         &ll, &size)) != 0)
         return LOG_RTERR (pctxt, stat);
   }
   else ll = size = length;
   if (ll > 0) {
      char* tmpstr = (char*) rtxMemAlloc (pctxt, ll + 1);
      if (0 != tmpstr) {
         ll = size;
         stat = xd_octstr_s (pctxt, (OSOCTET*)tmpstr, 
                             (OSUINT32*) &ll, ASN1IMPL, size);
         if (stat != 0) {
            rtxMemFreePtr (pctxt, tmpstr);
            return LOG_RTERR (pctxt, stat);
         }
         tmpstr[ll] = '\0';
         *object_p = tmpstr;
      }
      else
         return LOG_RTERR (pctxt, RTERR_NOMEM);
   }
   else {
      char* tmpstr = (char*) rtxMemAlloc (pctxt, 1);
      if (tmpstr) {
         tmpstr[0] = '\0';
         *object_p = tmpstr;
      }
      else
         return LOG_RTERR (pctxt, RTERR_NOMEM);
   }
   if (isConstructedTag && length == ASN_K_INDEFLEN) {
      if (XD_MATCHEOC (pctxt)) XD_BUMPIDX (pctxt, 2);
      else return LOG_RTERR (pctxt, ASN_E_INVLEN);
   }

   LCHECKBER (pctxt);

   return 0;
}
