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
 *  Routine name: xd_octstr
 *
 *  Description:  This routine decodes the octet string at the current
 *                message pointer location and returns its value.  This
 *                routine is identical to the xd_octstr_s above
 *                except for the fact that dynamic memory is allocated
 *                for the decoded string.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  tagging     bool    Specifies whether element is implicitly or
 *                      explicitly tagged.
 *  length      int     Length of data to retrieve.  Valid for implicit
 *                      case only.
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat	int	Status of operation.  Returned as function result.
 *  object      char**	Pointer to decoded octet string value.
 *  numocts	int	Number of octets in string.
 *
 **********************************************************************/

int xd_octstr (OSCTXT* pctxt, 
               const OSOCTET** object_p2, OSUINT32* pnumocts, 
               ASN1TagType tagging, int length) 
{ 
   OSOCTET* poctstr = 0;
   int stat = 0;
   int isConstructedTag;

   if (tagging == ASN1EXPL) {
      if ((stat = xd_match1 (pctxt, ASN_ID_OCTSTR, &length)) < 0)
         /* RTERR_IDNOTFOU will be logged later, by the generated code, 
            or reset by rtxErrReset (for optional seq elements). */
         return (stat == RTERR_IDNOTFOU) ? stat : LOG_RTERR (pctxt, stat);
   }
   isConstructedTag = (int)((pctxt->flags & ASN1CONSTAG) != 0);

   if (stat == 0) {
      int size, ll = 0;

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
         /* If "fast copy" option is not set (ASN1FATSCOPY) or if constructed,
          * copy the octet string value into a dynamic memory buffer;
          * otherwise, store the pointer to the value in the decode 
          * buffer in the data pointer argument. */

         if ((pctxt->flags & ASN1FASTCOPY) == 0 || isConstructedTag) {
            poctstr = (OSOCTET*) rtxMemAlloc (pctxt, ll);
            if (0 != poctstr) {
               *pnumocts = size; /* !AB (06/24/2002) */
               stat = xd_octstr_s (pctxt, poctstr, pnumocts, 
                                     ASN1IMPL, size);
            }
            else
               return LOG_RTERR (pctxt, RTERR_NOMEM);
         }
         else {
            *pnumocts = size; 
            poctstr = ASN1BUFPTR (pctxt);
            XD_BUMPIDX (pctxt, size);
         }
      }
      else {
         *pnumocts = 0;
      }
   }

   if (stat != 0) 
      return LOG_RTERR_AND_FREE_MEM (pctxt, stat, poctstr);

   *object_p2 = poctstr;

   if (isConstructedTag && length == ASN_K_INDEFLEN) {
      if (XD_MATCHEOC (pctxt)) XD_BUMPIDX (pctxt, 2);
      else return LOG_RTERR (pctxt, ASN_E_INVLEN);
   }

   LCHECKBER (pctxt);

   return 0;
} 
