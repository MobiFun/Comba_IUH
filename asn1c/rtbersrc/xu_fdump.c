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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rtbersrc/asn1ber.h"
#include "rtsrc/rt_common.hh"

/***********************************************************************
 *
 *  Routine name: xu_dump
 *
 *  Description:  This routine dumps an ASN message to the standard output
 *  device in the following format:
 *
 *  CLAS  F  -ID-  LENGTH  HEX CONTENTS                         ASCII
 *  xxxx  x  xxxx  xxxxxx  xx xx xx xx xx xx xx xx xx xx xx xx  xxxxxxxxxxxx
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  msgptr      char*   Pointer to ASN encoded message
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat        int     Completion status of routine
 *
 **********************************************************************/

static int xu_fdump_cb (const char* text_p, void* cbArg_p);

int xu_dump (OSOCTET *msgptr, ASN1DumpCbFunc cb, void* cbArg_p)
{
   OSCTXT     lctxt;
   ASN1TAG    tag;
   int        count, len, stat, ilcnt;
   char       *bufp, class_text[5], form_text, id_text[5], lbuf[133];

   /* If no callback function given, use local file dump callback       */
   /* with stdout as the callback parameter..                           */

   if (!cb) {
      cb = xu_fdump_cb;
      cbArg_p = stdout;
   }

   /* Set decode buffer pointer and pass header text to callback */

   if ((stat = rtInitASN1Context (&lctxt)) != 0)
      return (stat);

   if ((stat = xd_setp (&lctxt, msgptr, 0, &tag, &len)) != 0)
      { rtxFreeContext (&lctxt); return (stat); }

   (*cb) ("CLAS  F  -ID-  LENGTH  HEX CONTENTS                         ASCII",
      cbArg_p);

   if (len == ASN_K_INDEFLEN) ilcnt = 0;
   else ilcnt = 1; /* any non-zero value is acceptable here */

   /* Loop through message; format each line and pass to callback */

   while ((stat = xd_tag_len (&lctxt, &tag, &len, XM_ADVANCE)) == 0)
   {
      xu_fmt_tag (&tag, class_text, &form_text, id_text);
      if (len == ASN_K_INDEFLEN) ilcnt++;
      if (tag == 0 && len == 0) ilcnt--;

      if ((tag & TM_CONS) || len == 0)
      {
         if (len == ASN_K_INDEFLEN)
            sprintf (lbuf,
               "%4s  %c  %4s   INDEF", class_text, form_text, id_text);
         else
            sprintf (lbuf, 
               "%4s  %c  %4s  %6d", class_text, form_text, id_text, len);

         (*cb) (lbuf, cbArg_p);
      }
      else
      {
         register int i;
         size_t offset = 0;

         bufp = xu_fmt_contents (&lctxt, len, &count);

         for (i = 0; i < count; i++)
         {
            if (i == 0)
               sprintf (lbuf, "%4s  %c  %4s  %6d  %s", 
                  class_text, form_text, id_text, len, &bufp[offset]);
            else
               sprintf (lbuf, "                       %s", &bufp[offset]);

            (*cb) (lbuf, cbArg_p);

            offset += strlen(&bufp[offset]) + 1;
         }

         rtxMemFreePtr (&lctxt, bufp);
      }
      if (ilcnt <= 0) break;
   }

   if (stat == RTERR_ENDOFBUF) stat = 0;

   rtxFreeContext (&lctxt);
   return (stat);
}

/***********************************************************************
 *
 *  Routine name: xu_fdump
 *
 *  Description:  Identical to xu_dump except allows redirection of output
 *  to a text file.
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  file_p      FILE*   Pointer to file to receive output
 *  msgptr      char*   Pointer to ASN encoded message
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat        int     Completion status of routine
 *
 **********************************************************************/

int xu_fdump (FILE *file_p, OSOCTET *msgptr)
{
   return (xu_dump (msgptr, xu_fdump_cb, file_p));
}

static int xu_fdump_cb (const char* text_p, void* cbArg_p)
{
   /* Callback arg is a file pointer */
   FILE* fp = (FILE*) cbArg_p;
   fprintf (fp, "%s\n", text_p);
   return (0);
}
