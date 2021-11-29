/*
 * Copyright (c) 2003-2009 Objective Systems, Inc.
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

/* Run-time print utility functions */

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "rtxsrc/rtxCtype.h"
#include "rtxsrc/rtxErrCodes.h"
#include "rtxsrc/rtxPrint.h"
#include "rtxsrc/osMacros.h"


/**************************************************************/
/* Proprietary implementation to redirect print in a file     */
/* instead of standard output                                 */
/**************************************************************/

/* the printf is substituted with an arbiitrary function      */
/* providing that the new function has same type of           */
/* proprietaryPrint function pointer                          */

int (*proprietaryPrint)(char *fmat, va_list args) = NULL;


EXTRTMETHOD void rtxInstallPrint (int (*newFunct)(char *fmat, va_list args))
{
	proprietaryPrint = newFunct;
}

EXTRTMETHOD int rtxRedirectPrint (char *fmat,...)
{
	va_list args;
	va_start(args, fmat);


	if (proprietaryPrint == NULL)
		return vprintf(fmat, args);
	else
		return proprietaryPrint(fmat, args);
}



EXTRTMETHOD void rtxPrintBoolean (const char* name, OSBOOL value)
{
   printf ("%s = %s\n", name, value ? "true" : "false");
}

EXTRTMETHOD void rtxPrintInteger (const char* name, OSINT32 value)
{
   printf ("%s = %d\n", name, value);
}

EXTRTMETHOD void rtxPrintInt64 (const char* name, OSINT64 value)
{
   printf ("%s = "OSINT64FMT"\n", name, value);
}

EXTRTMETHOD void rtxPrintUnsigned (const char* name, OSUINT32 value)
{
   printf ("%s = %u\n", name, value);
}

EXTRTMETHOD void rtxPrintUInt64 (const char* name, OSUINT64 value)
{
   printf ("%s = "OSUINT64FMT"\n", name, value);
}

EXTRTMETHOD void rtxPrintCharStr (const char* name, const char* cstring)
{
   printf ("%s = '%s'\n", name, 
      (cstring == 0) ? "(null)" : cstring);
}

EXTRTMETHOD void rtxPrintUTF8CharStr (const char* name, const OSUTF8CHAR* cstring)
{
   printf ("%s = '%s'\n", name, 
      (cstring == 0) ? "(null)" : (const char*)cstring);
}

EXTRTMETHOD void rtxPrintUnicodeCharStr 
(const char* name, const OSUNICHAR* str, int nchars)
{
   int i;
   if (0 == str) return;
   if (nchars < 0) {
      nchars = 0;
      while (str[nchars] != 0) nchars++;
   }
   printf ("%s = '", name);
   for (i = 0; i < nchars; i++) {
      if (OS_ISPRINT (str[i]))
         putc (str[i], stdout);
      else
         printf ("0x%04x", str[i]);
   }
   printf ("'\n");
}

EXTRTMETHOD void rtxPrintHexStr (const char* name, OSUINT32 numocts, const OSOCTET* data)
{
   if (numocts <= 32) {
      OSUINT32 i;
      printf ("%s = 0x", name);
      for (i = 0; i < numocts; i++) {
         printf ("%02x", data[i]);
      }
      printf ("\n");
   }
   else {
      printf ("%s =\n", name);
      rtxHexDump (data, numocts);
   }
}

EXTRTMETHOD void rtxPrintNVP (const char* name, const OSUTF8NVP* pnvp)
{
   printf ("%s.name  = '%s'\n", name, 
      (pnvp->name == 0) ? "(null)" : (const char*)pnvp->name);
   printf ("%s.value = '%s'\n", name, 
      (pnvp->value == 0) ? "(null)" : (const char*)pnvp->value);
}

EXTRTMETHOD void rtxPrintHexBinary 
(const char* name, OSUINT32 numocts, const OSOCTET* data)
{
   printf ("%s.numocts = %u\n", name, numocts);
   printf ("%s.data = \n", name);
   rtxHexDump (data, numocts);
}

EXTRTMETHOD void rtxPrintReal (const char* name, OSREAL value)
{
   printf ("%s = %g\n", name, value);
}

EXTRTMETHOD void rtxPrintNull (const char* name)
{
   printf ("%s = <null>\n", name);
}

EXTRTMETHOD int rtxPrintFile (const char* filename)
{
   char lbuf[1024];
   FILE *fp = fopen (filename, "r");
   if (0 == fp) return (RTERR_FILNOTFOU);

   while (fgets (lbuf, sizeof(lbuf), fp)) {
      puts (lbuf);
   }

   fclose (fp);

   return 0;
}

#ifndef __SYMBIAN32__

/* Indentation for brace text printing */

static OSUINT32 g_indent = 0;

EXTRTMETHOD void rtxPrintIndent ()
{
   OSUINT32 i;
   for (i = 0; i < g_indent; i++) printf (" ");
}

EXTRTMETHOD void rtxPrintIncrIndent ()
{
   g_indent += OSRTINDENTSPACES;
}

EXTRTMETHOD void rtxPrintDecrIndent ()
{
   if (g_indent > 0) 
      g_indent -= OSRTINDENTSPACES;
}

EXTRTMETHOD void rtxPrintCloseBrace ()
{
   rtxPrintDecrIndent ();
   rtxPrintIndent ();
   printf ("}\n");
}

EXTRTMETHOD void rtxPrintOpenBrace (const char* name)
{
   rtxPrintIndent ();
   printf ("%s {\n", name);
   rtxPrintIncrIndent ();
}

#endif
