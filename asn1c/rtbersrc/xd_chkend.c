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
 *  Routine name: xd_chkend
 *
 *  Description:  This routine checks for the end of the context defined
 *                by the length variables that were last pushed on the
 *                stack using xd_push.
 *
 *  Inputs:
 *
 *  None
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  eoc		bool	True if end-of-context encountered.  Returned as
 *                      function result.
 *
 **********************************************************************/

int xd_chkend (OSCTXT* pctxt, ASN1CCB* ccb_p)
{ 
   int		len;
   ASN1TAG	tag;
   register int	eoc, stat, usedBytes;

   if (ccb_p->len == ASN_K_INDEFLEN)
   {
      stat = xd_tag_len (pctxt, &tag, &len, 0);

      if (stat == RTERR_ENDOFBUF) {
         rtxErrReset (pctxt);
         eoc = TRUE;
      }
      else if (tag == 0 && len == 0)
      {
         /* Advance cursor past EOC only if enveloping context  */
         /* parsed the indefinite length marker..               */
         /*
         if (ccb_p->tagging == ASN1EXPL) {
            xd_tag_len (pctxt, &tag, &len, XM_ADVANCE);
         }
         */
         eoc = TRUE;
      }
      else 
         eoc = FALSE;
   }
   else
   {
      usedBytes = (int)(OSRTBUFPTR(pctxt) - ccb_p->ptr);
      eoc = ((usedBytes >= ccb_p->len) || 
         (pctxt->buffer.byteIndex >= pctxt->buffer.size)); /*!AB 09/19/02 */
   }

   return (eoc);
}

