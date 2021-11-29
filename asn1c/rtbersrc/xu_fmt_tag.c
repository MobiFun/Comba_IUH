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

#include "rtbersrc/xu_common.hh"

/***********************************************************************
 *
 *  Routine name: xu_fmt_tag
 *
 *  Description:  This routine formats the elements in an ASN.1 tag for
 *  display.  Class, form, and ID code text fields are returned.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  tag		short	ASN.1 tag value
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  class       char*   Textual representation of class field
 *  form        char*   Textual representation of form field
 *  id_code     char*   Textual representation of ID code field
 *
 **********************************************************************/

void xu_fmt_tag (ASN1TAG *tag_p, char *class_p, char *form_p, char *idCode_p)
{
   static const char* id_names[] = {
      " EOC", "BOOL", " INT", "BITS", "OCTS", "NULL", " OID", "OBJD", 
      " EXT", "REAL", "ENUM", "EPDV", "UTF8", "ROID", "  14", "  15", 
      " SEQ", " SET", "NUMS", "PRTS", "T61S", "VIDS", "IA5S", "UTCT", 
      "GENT", "GRAS", "VISS", "GENS", "UNIS", "  29", "BMPS"
   };

   ASN1TAG  tclass = *tag_p & TM_PRIV;
   OSUINT32 idcode = *tag_p & TM_IDCODE;

   switch (tclass)
   {
      case TM_UNIV: strcpy (class_p, "UNIV"); break;
      case TM_APPL: strcpy (class_p, "APPL"); break;
      case TM_CTXT: strcpy (class_p, "CTXT"); break;
      case TM_PRIV: strcpy (class_p, "PRIV"); break;
      default:      strcpy (class_p, "****"); break;
   }

   *form_p = (*tag_p & TM_CONS) ? 'C' : 'P';

   if (tclass == TM_UNIV && idcode < sizeof (id_names)/sizeof (id_names[0]))
      strcpy  (idCode_p, id_names[idcode]);
   else
      sprintf (idCode_p, "%4d", idcode);
}

char* xu_fmt_tag2 (ASN1TAG *tag_p, char* bufp)
{
   char szClass[8], cForm, szIdCode[8];
   xu_fmt_tag (tag_p, szClass, &cForm, szIdCode);
   sprintf (bufp, "[%s %c %s]", szClass, cForm, szIdCode);
   return (bufp);
}
