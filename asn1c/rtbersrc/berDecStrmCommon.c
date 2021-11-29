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

#include "rtbersrc/xsd_common.hh"

/***********************************************************************
 *
 *  Routine name: berDecStrmTag
 *
 *  Description:  This routine decodes an ASN tag into a standard 16 bit
 *                structure.  This structure represents a tag as follows:
 *
 *                 Bit#: 11 1 1110000000000
 *                       54 3 2109876543210
 *                      |__|_|_____________|
 *                       ^  ^  ID code 
 *                       |  |
 *                       |  +- Form:
 *                       |     0 = Primitive,
 *                       |     1 = Constructor
 *                       |
 *                       +---- Class:
 *                             0 (00) = Universal
 *                             1 (01) = Application
 *                             2 (10) = Context-specific
 *                             3 (11) = Private
 *
 *                Note: This tag structure can be expanded to 32 bits 
 *                (29 for the ID code) by including the following #define 
 *                statement in asn1type.h:
 *
 *                #define ASN1C_EXPANDED_TAGS
 *
 ***********************************************************************/

int berDecStrmTag (OSCTXT* pctxt, ASN1TAG *tag_p)
{ 
   ASN1TAG      class_form, id_code;
   int          lcnt = 0;
   int          b, stat;
   OSOCTET      ub;
   
   stat = rtxStreamRead (pctxt, &ub, 1);
   if (stat < 0) return stat;

   b = ub; *tag_p = 0;

   class_form = (ASN1TAG)(b & TM_CLASS_FORM);
   class_form <<= ASN1TAG_LSHIFT;

   if ((id_code = (b & TM_B_IDCODE)) == 31) {
      id_code = 0;
      do {
         stat = rtxStreamRead (pctxt, &ub, 1);
         if (stat < 0) return stat;

         b = ub;
         id_code = (id_code * 128) + (b & 0x7F);
         if (id_code > TM_IDCODE || lcnt++ > 8) 
            return LOG_RTERR (pctxt, ASN_E_BADTAG);
      } while (b & 0x80);
   }

   *tag_p = class_form | id_code;

   /* Set constructed tag bit in context flags based on parsed value */
   SET_ASN1CONSTAG(pctxt, class_form);

   return (0);
}

/***********************************************************************
 *
 *  Routine name: berDecStrmLength
 *
 *  Description:  This routine decodes the length field component of an
 *                ASN.1 message.  It is called by the xd_tag_len routine
 *                which handles the decoding of both the ID and length
 *                fields.
 *
 **********************************************************************/

int berDecStrmLength (OSCTXT *pctxt, int *len_p)
{ 
   int i, j, stat;
   OSOCTET b, lbuf[8];

   stat = rtxStreamRead (pctxt, &b, 1);
   if (stat < 0) return LOG_RTERR (pctxt, stat); else stat = b;

   if (stat > 0x80) {
      *len_p = 0;
      i = stat & 0x7F;

      if (i > 4) 
         return LOG_RTERR (pctxt, ASN_E_INVLEN);

      stat = rtxStreamRead (pctxt, lbuf, i);
      if (stat < 0) return LOG_RTERR (pctxt, stat);

      for (j = 0, *len_p = 0; j < i; j++) {
         *len_p = (*len_p * 256) + lbuf[j];
      }
   }
   else if (stat == 0x80) *len_p = ASN_K_INDEFLEN;
   else *len_p = stat;

   /* Length is not indefinite length */
   if (*len_p != ASN_K_INDEFLEN) {
      if (*len_p < 0)
         return LOG_RTERR (pctxt, ASN_E_INVLEN);
   }

   return (0);
} 

int berDecStrmTagAndLen (OSCTXT *pctxt, ASN1TAG *tag_p, int *len_p) 
{ 
   int stat;
   OSUINT16 mask = ASN1INDEFLEN | ASN1LASTEOC;

   /* Check for attempt to read past EOB */

   if (0 != (pctxt->flags & ASN1INDEFLEN)) {
      if ((pctxt->flags & mask) == mask)
         return LOG_RTERR (pctxt, RTERR_ENDOFBUF);
   }

   if ((stat = berDecStrmTag (pctxt, tag_p)) == 0)
   {
      stat = berDecStrmLength (pctxt, len_p);

      /* Indefinite length message check.. if indefinite length parsed, */
      /* bump indefinite length section counter; if EOC ID parsed,      */
      /* decrement count.  If overall message is of indefinite length   */
      /* and count goes to zero, signal end of message.                 */

      if (stat == 0)
      {
         if (*len_p == ASN_K_INDEFLEN) {

            /* Verify form of tag is constructed.  If not, indefinite   */
            /* length is invalid (ED, 4/12/02)..                        */

            if (0 == (pctxt->flags & ASN1CONSTAG))
               return LOG_RTERR (pctxt, ASN_E_INVLEN);
         }
      }
      else 
         return LOG_RTERR (pctxt, stat);
   }
   else 
      return LOG_RTERR (pctxt, stat);

   return 0;
} 

int berDecStrmMatchTag (OSCTXT* pctxt, ASN1TAG tag, int *len_p, 
   OSBOOL advance)
{
   int stat;
   ASN1TAG parsed_tag;
   int parsed_len;

   stat = rtxStreamDirectBufCheck (pctxt);
   if (stat < 0) return LOG_RTERR (pctxt, stat);

   stat = rtxStreamMark (pctxt, 32);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   stat = berDecStrmTagAndLen (pctxt, &parsed_tag, &parsed_len);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   parsed_tag &= ~TM_CONS;
   if ((tag & ~TM_CONS) != parsed_tag) {
      rtxStreamReset (pctxt);
#ifndef _COMPACT
      berErrAddTagParm (pctxt, tag);         /* expected tag */
      berErrAddTagParm (pctxt, parsed_tag);  /* parsed tag */
#endif
      return RTERR_IDNOTFOU;
   }
   else {
      if (len_p != 0) *len_p = parsed_len;
      if (!advance) {
         stat = rtxStreamReset (pctxt);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
      }
   }

   return 0;
}

int berDecStrmMatchEOC (OSCTXT* pctxt)
{
   int stat;
   OSOCTET lbuf[2];

   stat = rtxStreamDirectBufCheck (pctxt);
   if (stat < 0) return LOG_RTERR (pctxt, stat);

   stat = rtxStreamMark (pctxt, 8);
   if (stat < 0) return LOG_RTERR (pctxt, stat);

   stat = rtxStreamRead (pctxt, lbuf, 2);
   if (stat < 0) return LOG_RTERR (pctxt, stat);

   if (!(lbuf[0] == 0 && lbuf[1] == 0)) {
      rtxStreamReset (pctxt);
      rtxErrAddStrParm (pctxt, "EOC");
      rtxErrAddStrParm (pctxt, "non-EOC");
      return LOG_RTERR (pctxt, RTERR_IDNOTFOU);
   }
   return 0;
}

OSBOOL berDecStrmTestEOC (OSCTXT* pctxt, ASN1CCB* ccb_p)
{
   int stat;
   OSOCTET lbuf[2];

   rtxStreamMark (pctxt, 8);

   stat = rtxStreamRead (pctxt, lbuf, 2);
   if (stat < 0) { ccb_p->stat = stat; return TRUE; }

   rtxStreamReset (pctxt);

   return (lbuf[0] == 0 && lbuf[1] == 0);
}

