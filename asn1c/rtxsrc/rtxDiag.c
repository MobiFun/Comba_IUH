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

#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxUnicode.h"
#include "rtxsrc/rtxPrint.h"
#include "rtxsrc/rtxPrintStream.h"

#ifndef __SYMBIAN32__
static OSBOOL g_DiagEnabled = FALSE;
#endif

EXTRTMETHOD OSBOOL rtxDiagEnabled (OSCTXT* pctxt)
{
#ifndef __SYMBIAN32__
   if (g_DiagEnabled) return TRUE;
   else 
#endif
      if (0 != pctxt && pctxt->flags & OSDIAG) return TRUE;
      else return FALSE;
}

EXTRTMETHOD OSBOOL rtxSetDiag (OSCTXT* pctxt, OSBOOL value)
{
   OSBOOL prevState = rtxDiagEnabled (pctxt);
   if (value)
      pctxt->flags |= OSDIAG;
   else {
      /* Need to do it this way because some UNIX compilers will set    */
      /* bits in full 32-bit word..                                     */
      OSRTFLAGS lflags = (pctxt->flags & ~OSDIAG);
      pctxt->flags = lflags;
   }
   return prevState;
}

#ifndef __SYMBIAN32__
EXTRTMETHOD OSBOOL rtxSetGlobalDiag (OSBOOL value)
{
   OSBOOL prevState = g_DiagEnabled;
   g_DiagEnabled = value;
   return prevState;
}
#endif

static OSBOOL checkDiagLevel (OSCTXT* pctxt, const char* str)
{
   if (*str == '~') {
      OSRTDiagTraceLevel level = (OSRTDiagTraceLevel) pctxt->diagLevel;
      const char* testStr;
      switch (level) {
      case OSRTDiagError: testStr = "Ee"; break;
      case OSRTDiagWarning: testStr = "EeWw"; break;
      case OSRTDiagInfo:  testStr = "EeWwIi"; break;
      case OSRTDiagDebug: testStr = "EeWwIiDd"; break;
      default: testStr = 0;
      }
      if (0 != testStr) {
         return (OSBOOL) (0 != OSCRTLSTRCHR (testStr, *(str+1)));
      }
   }
   return TRUE;
}

EXTRTMETHOD void rtxDiagPrint (OSCTXT* pctxt, const char* fmtspec, ...)
{
   if (rtxDiagEnabled (pctxt) && checkDiagLevel (pctxt, fmtspec)) {
      va_list  arglist;
      va_start (arglist, fmtspec);
      vprintf  (fmtspec, arglist);
      va_end   (arglist);
   }
}

void rtxDiagPrintUCS (OSCTXT* pctxt, const OSUNICHAR* chars)
{
   if (rtxDiagEnabled (pctxt)) {
      rtxUCSStrPrint (chars);
      printf ("\n");
   }
}

EXTRTMETHOD void rtxDiagHexDump 
(OSCTXT* pctxt, const OSOCTET* data, OSUINT32 numocts)
{
   if (rtxDiagEnabled (pctxt)) {
      rtxHexDumpToFile (stdout, data, numocts);
   }
}

EXTRTMETHOD void rtxDiagStream (OSCTXT* pctxt, const char* fmtspec, ...) 
{
   if (rtxDiagEnabled (pctxt) && checkDiagLevel (pctxt, fmtspec)) {
      va_list  arglist;
      va_start (arglist, fmtspec);
      rtxDiagToStream  (pctxt, fmtspec, arglist);
      va_end (arglist);
   }
}

/* Sends dump to print stream */
EXTRTMETHOD void rtxDiagStreamHexDump 
(OSCTXT* pctxt, const OSOCTET* data, OSUINT32 numocts)
{
   if (rtxDiagEnabled (pctxt)) {
      rtxHexDumpToStream (pctxt, data, numocts);
   }
}

EXTRTMETHOD void rtxDiagPrintChars 
(OSCTXT* pctxt, const char* data, OSUINT32 nchars)
{
   OSUINT32 i;
   if (rtxDiagEnabled (pctxt)) {
      for (i = 0; i < nchars; i++) putchar (data[i]);
      printf ("\n");
   }
}

EXTRTMETHOD void rtxDiagStreamPrintChars 
(OSCTXT* pctxt, const char* data, OSUINT32 nchars)
{
   if (rtxDiagEnabled (pctxt)) {
      OSUINT32 i;
      for (i = 0; i < nchars; i++)
         rtxPrintToStream (pctxt, "%c", data[i]);
   }
}

EXTRTMETHOD void rtxDiagSetTraceLevel (OSCTXT* pctxt, OSRTDiagTraceLevel level)
{
   rtxSetDiag (pctxt, TRUE);
   pctxt->diagLevel = (OSOCTET) level;
}
