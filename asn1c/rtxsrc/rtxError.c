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
/*
// CHANGE LOG
// Date         Init    Description
//
////////////////////////////////////////////////////////////////////////////
*/
/* Run-time error utility functions */
#include <stdarg.h>
#include <stdio.h>

#include "rtxsrc/osMacros.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxCommonDefs.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxMemory.h"
#include "rtxsrc/rtxUnicode.h"
#include "rtxsrc/rtxUTF8.h"


#define printf rtxRedirectPrint

EXTERNRT int rtxRedirectPrint (char *fmat,...);

#define OSRTALLOCELEMDNODEZ(pctxt,type) \
(type*) (((char*)rtxMemAllocZ (pctxt, sizeof(type) + \
sizeof(OSRTDListNode))) + sizeof(OSRTDListNode))

/* Error status text */
#if !defined(_ARMTCC) && !defined(_COMPACT) && !defined(__SYMBIAN32__)
static const char* const g_status_text[] = {
    "Encode buffer overflow",
    "Unexpected end of buffer on decode",
    "Unexpected identifier encountered: expected = %s, parsed = %s",
    "Enumerated value %s not in defined set",
    "Duplicate element in ASN.1 SET or XSD all type",
    "Missing required element in ASN.1 SET or XSD all type",
    "Element index %s not within bounds of ASN.1 SET or XSD all type",
    "Max elements defined for repeating field exceeded",
    "Element with identifier %s is an invalid option in choice",
    "No dynamic memory available",
    "Invalid hex string",
    "Invalid real value",
    "Max items in sized character or binary string field exceeded",
    "Invalid value specification",
    "Nesting level too deep",
    "Value constraint violation: field %s, value %s",
    "Unexpected end of file detected",
    "Invalid UTF-8 character at index %s",
    "Array index out of bounds",
    "Invalid parameter passed to function or method",
    "Invalid value format",
    "Context is not initialized",
    "Value will not fit in target variable",
    "Character is not within the defined character set",
    "Invalid XML state for attempted operation",
    "Error condition returned from XML parser:\n%s",
    "Sequence elements not in correct order",
    "File not found or can't be opened",
    "Read error",
    "Write error",
    "Invalid Base64 string",
    "Socket error",
    "Attribute \"%s.%s\" not defined",
    "Regexp error: %s: %s",
    "Pattern match violation: field %s, value %s",
    "Missing required attribute \"%s\"",
    "Host name could not be resolved",
    "HTTP error: %s",
    "SOAP error. Code: %s, Reason:\n%s",
#ifdef RTEVAL
    "Evaluation license is expired",
#else
    "", /* placeholder */
#endif
    "Unexpected element \"%s\" found",
    "Invalid number of occurences of element %s (%s)",
    "Invalid message buffer",
    "Decode \"%s\" for element \"%s.%s\" failed",
    "Decode of attribute \"%s.%s\" failed",
    "Current stream must be closed before opening a new stream", 
    "Unexpected null pointer value: %s",
    "General failure: %s", 
    "Attribute '%s' value '%s' does not match defined fixed value", 
    "Multiple errors; see context error list for details on each error", 
    "Derived type could not be decoded due to missing type info",
    "Address is already in use",
    "Remote connection was reset",
    "Host was unreachable due to network or host failure",
    "Socket is not connected",
    "Connection refused",
    "Invalid socket option",
    "SOAP fault message", 
    "Mark is not supported on this type of stream"
} ;

struct OSRTErrorTable {
   const char* const* ppStatusText;
   OSINT32      minErrCode;
   OSINT32      maxErrCode;
} ;

#define OSRTMAXERRTABENTRIES 5

static struct OSRTErrorTable g_error_table[OSRTMAXERRTABENTRIES];
static OSINT16 g_numErrorTableEntries = 0;
#endif /* COMPACT, ARMTCC, SYMBIAN */

/* Add error table entry to error table array */

EXTRTMETHOD OSBOOL rtxErrAddErrorTableEntry (const char* const* ppStatusText, 
      OSINT32 minErrCode, OSINT32 maxErrCode)
{
#if !defined(_ARMTCC) && !defined(_COMPACT) && !defined(__SYMBIAN32__)
   OSINT16 i;

   if (g_numErrorTableEntries < OSRTMAXERRTABENTRIES) {

      /* Make sure table entry has not already been added */

      for (i = 0; i < g_numErrorTableEntries; i++) {
         if (g_error_table[g_numErrorTableEntries].ppStatusText == 
             ppStatusText) return FALSE;
      }

      /* Add entry */

      g_error_table[g_numErrorTableEntries].ppStatusText = ppStatusText;
      g_error_table[g_numErrorTableEntries].minErrCode = minErrCode;
      g_error_table[g_numErrorTableEntries++].maxErrCode = maxErrCode;

      return TRUE;
   }
#endif
   return FALSE;
}

EXTRTMETHOD void rtxErrInit ()
{
#if !defined(_ARMTCC) && !defined(_COMPACT) && !defined(__SYMBIAN32__)
   rtxErrAddErrorTableEntry (g_status_text, -1, -99);
#endif
}

EXTRTMETHOD OSBOOL rtxErrAddCtxtBufParm (OSCTXT* pctxt)
{
   return rtxErrAddStrnParm 
      (pctxt, (const char*)OSRTBUFPTR (pctxt), OSRTBUFSIZE (pctxt));
}

EXTRTMETHOD OSBOOL rtxErrAddElemNameParm (OSCTXT* pctxt)
{
   OSBOOL res;

   if (pctxt->elemNameStack.count > 0) {
      OSUTF8CHAR* elemName = 0;
      rtxDListToUTF8Str (pctxt, &pctxt->elemNameStack, &elemName, '.');

      if (0 != elemName) {
         /* Add string parameter */
         res = rtxErrAddStrParm (pctxt, (const char*)elemName);

         /* Free temp memory */
         rtxMemFreePtr (pctxt, elemName);
      }
      else res = FALSE;
   }
   else res = rtxErrAddStrParm (pctxt, "?");

   return res;
}

/* Add an integer parameter to an error message */

EXTRTMETHOD OSBOOL rtxErrAddIntParm (OSCTXT* pctxt, int errParm)
{
   char lbuf[16];
   rtxIntToCharStr (errParm, lbuf, sizeof(lbuf), 0);
   return rtxErrAddStrParm (pctxt, lbuf);
}

#if !defined(_NO_INT64_SUPPORT)
/* Add an 64-bit integer parameter to an error message */

EXTRTMETHOD OSBOOL rtxErrAddInt64Parm (OSCTXT* pctxt, OSINT64 errParm)
{
   char lbuf[32];
   rtxInt64ToCharStr (errParm, lbuf, sizeof(lbuf), 0);
   return rtxErrAddStrParm (pctxt, lbuf);
}
#endif /* !defined(_NO_INT64_SUPPORT) */

/* Add a character string parameter to an error message */

EXTRTMETHOD OSBOOL rtxErrAddStrParm (OSCTXT* pctxt, const char* pErrParm)
{
   OSRTErrInfo* pErrInfo = &pctxt->errInfo.reserved;
   if (pErrParm == 0) pErrParm = "(null)";
   if (pErrInfo != 0 && pErrInfo->parmcnt < OSRTMAXERRPRM) {
      size_t bufsiz = OSCRTLSTRLEN(pErrParm) + 1;
      OSUTF8CHAR* tmpstr = 
         rtxMemAllocArray (pctxt, bufsiz, OSUTF8CHAR);
      if (tmpstr == NULL) return FALSE;
      rtxStrcpy ((char*)tmpstr, bufsiz, pErrParm);
      pErrInfo->parms[pErrInfo->parmcnt] = tmpstr;
      pErrInfo->parmcnt++;
      return TRUE;
   }
   else
      return FALSE;
}

/* Add a character string parameter to an error message */

EXTRTMETHOD OSBOOL rtxErrAddStrnParm 
(OSCTXT* pctxt, const char* pErrParm, size_t nchars)
{
   OSRTErrInfo* pErrInfo = &pctxt->errInfo.reserved;
   if (pErrParm == 0) pErrParm = "(null)";
   if (pErrInfo != 0 && pErrInfo->parmcnt < OSRTMAXERRPRM) {
      OSUTF8CHAR* tmpstr = 
         rtxMemAllocArray (pctxt, nchars + 1, OSUTF8CHAR);
      if (tmpstr == NULL) return FALSE;
      rtxStrncpy ((char*)tmpstr, nchars + 1, pErrParm, nchars);
      pErrInfo->parms[pErrInfo->parmcnt] = tmpstr;
      pErrInfo->parmcnt++;
      return TRUE;
   }
   else
      return FALSE;
}

/* Add a Unicode character string parameter to an error message */

EXTRTMETHOD OSBOOL rtxErrAddUniStrParm (OSCTXT* pctxt, const OSUNICHAR* pErrParm)
{
   OSRTErrInfo* pErrInfo = &pctxt->errInfo.reserved;
   if (pErrParm == 0) pErrParm = (const OSUNICHAR*)"";
   if (pErrInfo != 0 && pErrInfo->parmcnt < OSRTMAXERRPRM) {
      pErrInfo->parms[pErrInfo->parmcnt] =
         (OSUTF8CHAR*) rtxUCSToCStr (pctxt, pErrParm);
      pErrInfo->parmcnt++;
      return TRUE;
   }
   else
      return FALSE;
}

/* Add an unsigned integer parameter to an error message */

EXTRTMETHOD OSBOOL rtxErrAddUIntParm (OSCTXT* pctxt, unsigned int errParm)
{
   char lbuf[16];
   rtxUIntToCharStr (errParm, lbuf, sizeof(lbuf), 0);
   return rtxErrAddStrParm (pctxt, lbuf);
}

#if !defined(_NO_INT64_SUPPORT)
/* Add an unsigned 64-bit integer parameter to an error message */

EXTRTMETHOD OSBOOL rtxErrAddUInt64Parm (OSCTXT* pctxt, OSUINT64 errParm)
{
   char lbuf[32];
   rtxUInt64ToCharStr (errParm, lbuf, sizeof(lbuf), 0);
   return rtxErrAddStrParm (pctxt, lbuf);
}
#endif /* !defined(_NO_INT64_SUPPORT) */

/* Add a double parameter to an error message */

EXTRTMETHOD OSBOOL rtxErrAddDoubleParm (OSCTXT* pctxt, double errParm)
{
   char lbuf[200];
#if !defined(_ARMTCC) && !defined(_COMPACT) && !defined(__SYMBIAN32__)
   os_snprintf (lbuf, 200, "%E", errParm);
#else
   OSCRTLSTRCPY (lbuf, "?");
#endif
   return rtxErrAddStrParm (pctxt, lbuf);
}

void rtxErrFreeNodeParms (OSCTXT* pctxt, OSRTErrInfo* pErrInfo)
{
   int i;

   if (pErrInfo == 0) return;
   for (i = 0; i < pErrInfo->parmcnt; i++)
      rtxMemFreeArray (pctxt, (char*)pErrInfo->parms[i]);

   pErrInfo->parmcnt = 0;
#if 0
   if (0 != pErrInfo->elemName) {
      rtxMemFreePtr (pctxt, pErrInfo->elemName);
      pErrInfo->elemName = 0;
   }
#endif
   pErrInfo->status = 0;
}

/* Free error parameter memory */

EXTRTMETHOD void rtxErrFreeParms (OSCTXT* pctxt)
{
   OSRTDListNode* pNode = pctxt->errInfo.list.head;

   for (;pNode != 0; pNode = pNode->next) {
      OSRTErrInfo* pErrInfo = (OSRTErrInfo*)pNode->data;

      rtxErrFreeNodeParms (pctxt, pErrInfo);
   }
}

/* Reset error */

EXTRTMETHOD int rtxErrReset (OSCTXT* pctxt)
{
   OSRTDListNode* pNode = pctxt->errInfo.list.head, *pNextNode;

   rtxErrFreeParms (pctxt);

   for (;pNode != 0; pNode = pNextNode) {
      OSRTErrInfo* pErrInfo = (OSRTErrInfo*)pNode->data;
      pNextNode = pNode->next;
      if (pErrInfo != &pctxt->errInfo.reserved) {
         rtxDListFreeNode (pctxt, &pctxt->errInfo.list, pNode);
      }
      else { /* just remove, but not free */
         rtxDListRemove (&pctxt->errInfo.list, pNode);
      }
   }
   return 0;
}

/* Format error message */

static char* rtxErrFmtMsgText 
(OSRTErrInfo* pErrInfo, const char* errmsg, char* bufp, size_t bufsiz)
{
   const char* tp;
   OSUINT32 j, pcnt;

   /* Substitute error parameters into error message */

   j  = pcnt = 0;
   tp = errmsg;

   while (*tp) {
      if (*tp == '%' && *(tp+1) == 's') {

         /* Plug in error parameter */

         if (pcnt < (size_t)pErrInfo->parmcnt && pErrInfo->parms[pcnt]) {
            OSUINT32 k = j + OSCRTLSTRLEN ((const char*)pErrInfo->parms[pcnt]);
            if (k < (bufsiz - 1)) {
               rtxStrcpy (&bufp[j], bufsiz-j, 
                          (const char*)pErrInfo->parms[pcnt++]);
               j = k;
            }
            else break;
         }
         else
            bufp[j++] = '?';

         tp += 2;
      }
      else if (j < (bufsiz - 1))
         bufp[j++] = *tp++;
      else break;
   }

   /* append additional params */
   while (pcnt < (size_t)pErrInfo->parmcnt && pErrInfo->parms[pcnt]) {
      OSUINT32 k = 1 + j + OSCRTLSTRLEN ((const char*)pErrInfo->parms[pcnt]);
      if (k < (bufsiz - 1)) {
         bufp[j++] = ' ';
         rtxStrcpy (&bufp[j], bufsiz-j, 
                    (const char*)pErrInfo->parms[pcnt++]);
         j = k;
      }
      else break;
   }

   bufp[j] = '\0';        /* null terminate string */

   return bufp;
}

static const char* rtxErrGetStatusText (OSRTErrInfo* pErrInfo)
{
#if !defined(_ARMTCC) && !defined(_COMPACT) && !defined(__SYMBIAN32__)
   const char* const* ppStatusText = 0;
   OSINT16 i;

   /* Find error table */

   for (i = 0; i < g_numErrorTableEntries; i++) {
      /* Note: test is reversed because status codes are negative */
      if (pErrInfo->status <= g_error_table[i].minErrCode && 
          pErrInfo->status > g_error_table[i].maxErrCode) {
         ppStatusText = g_error_table[i].ppStatusText;
         break;
      }
   }

   /* Return error text template */

   if (0 != ppStatusText) {
      OSINT32 erridx = abs (pErrInfo->status - g_error_table[i].minErrCode);
      return ppStatusText[erridx];
   }
#endif
   return 0;
}

char* rtxErrFmtMsg (OSRTErrInfo* pErrInfo, char* bufp, size_t bufsiz)
{
   if (pErrInfo->status < 0)
   {
      const char* pErrMsgText = rtxErrGetStatusText (pErrInfo);

      if (0 != pErrMsgText) {
         rtxErrFmtMsgText (pErrInfo, pErrMsgText, bufp, bufsiz);
      }
      else
         rtxStrcpy (bufp, bufsiz, "unrecognized completion status");
   }
   else rtxStrcpy (bufp, bufsiz, "normal completion status");

   return (bufp);
}

/* Get error text in a dynamic memory buffer.  This allocates memory    */
/* using the 'rtxMemAlloc' function.  This memory is automatically      */
/* freed at the time the 'rtxMemFree' function is called.               */
/* The calling function should free the memory.                         */

EXTRTMETHOD char* rtxErrGetText (OSCTXT* pctxt, char* pBuf, size_t* pBufSize)
{
   size_t bufsiz;
   OSRTDListNode* pNode;   

   if (pBuf == 0 || pBufSize == 0) {
      /* calculate buffer size */ 
      bufsiz = 200;
      for (pNode = pctxt->errInfo.list.head; pNode != 0; pNode = pNode->next) {
         OSRTErrInfo* pErrInfo = (OSRTErrInfo*)pNode->data;
         bufsiz += 100 * (2 + pErrInfo->stkx) * sizeof(char);
         if (0 != pErrInfo->elemName) {
            bufsiz += rtxUTF8LenBytes (pErrInfo->elemName) + 20;
         }
      }
      pBuf = rtxMemAllocArray (pctxt, bufsiz, char);
      if (pBuf == NULL) return NULL;
      if (pBufSize != 0) *pBufSize = bufsiz;
   }
   else
      bufsiz = *pBufSize;

   return rtxErrGetTextBuf (pctxt, pBuf, bufsiz);
}

/* Get error text in static buffer */
EXTRTMETHOD char* rtxErrGetTextBuf (OSCTXT* pctxt, char* pbuf, size_t bufsiz)
{
   char lbuf[200], numbuf[32];
   OSRTDListNode* pNode;   

   if (pbuf == 0 || bufsiz == 0) return 0;

   *pbuf = '\0';
  
   for (pNode = pctxt->errInfo.list.head; pNode != 0; pNode = pNode->next) {
      OSRTErrInfo* pErrInfo = (OSRTErrInfo*)pNode->data;
      OSUINT8 stkx = pErrInfo->stkx;

      rtxStrcat (pbuf, bufsiz, "ERROR: Status ");
      rtxIntToCharStr (pErrInfo->status, numbuf, sizeof(numbuf), 0);
      rtxStrcat (pbuf, bufsiz, numbuf);
      if (!rtxStrcat (pbuf, bufsiz, "\n")) break;

      rtxStrcat (pbuf, bufsiz, rtxErrFmtMsg (pErrInfo, lbuf, sizeof(lbuf)));
      if (!rtxStrcat (pbuf, bufsiz, "\n")) break;
#ifndef _COMPACT
      if (0 != pErrInfo->elemName) {
         rtxStrcat (pbuf, bufsiz, "Element name: ");
         rtxStrcat (pbuf, bufsiz, (const char*)pErrInfo->elemName);
         if (!rtxStrcat (pbuf, bufsiz, "\n")) break;
      }
      if (!rtxStrcat (pbuf, bufsiz, "Stack trace:\n")) break;

      while (stkx > 0) {
         stkx--;
         rtxStrcat (pbuf, bufsiz, "  Module: ");
         rtxStrcat (pbuf, bufsiz, (const char*)pErrInfo->stack[stkx].module);
         rtxStrcat (pbuf, bufsiz, " Line ");
         rtxIntToCharStr 
            (pErrInfo->stack[stkx].lineno, numbuf, sizeof(numbuf), 0);
         rtxStrcat (pbuf, bufsiz, numbuf);
         if (!rtxStrcat (pbuf, bufsiz, "\n")) break;
      }
#endif
   }
  
   return pbuf;
}

/* Log error using given callback function */

EXTRTMETHOD void rtxErrLogUsingCB (OSCTXT* pctxt, OSErrCbFunc cb, void* cbArg_p)
{
   const char* pBuf = rtxErrGetText (pctxt, 0, 0);

   if (pBuf == NULL) {
      pBuf = "ERROR : no memory available";
   }
   (*cb) (pBuf, cbArg_p);

   rtxErrFreeParms (pctxt);
}

/* Print error information to the standard output */

EXTRTMETHOD void rtxErrPrintElement (OSRTErrInfo* pErrInfo)
{
   char lbuf[400];
   OSUINT8 stkx = pErrInfo->stkx;

   printf ("ERROR: Status %d\n", pErrInfo->status);
   printf ("%s\n", rtxErrFmtMsg (pErrInfo, lbuf, sizeof(lbuf)));
#ifndef _COMPACT
   if (0 != pErrInfo->elemName) {
      printf ("Element name: %s\n", pErrInfo->elemName);
   }
   printf ("Stack trace:");
   while (stkx > 0) {
      stkx--;
      printf ("  Module: %s, Line %d\n",
              pErrInfo->stack[stkx].module,
              pErrInfo->stack[stkx].lineno);
   }
#endif
}

EXTRTMETHOD void rtxErrPrint (OSCTXT* pctxt)
{
   OSRTDListNode* pNode;

   for (pNode = pctxt->errInfo.list.head; pNode != 0; pNode = pNode->next) {
      OSRTErrInfo* pErrInfo = (OSRTErrInfo*)pNode->data;
      rtxErrPrintElement (pErrInfo);
   }
}

/* Set error data */

EXTRTMETHOD int rtxErrSetData (OSCTXT* pctxt, int status,
                   const char* module, int lineno)
{
   OSRTErrInfo* pErrInfo = OSRT_GET_LAST_ERROR_INFO (pctxt);
   if (pErrInfo == 0) {
      return rtxErrSetNewData (pctxt, status, module, lineno);
   }
   if (pErrInfo->status == 0) {
      pErrInfo->status = (OSINT16)status;
   }
#ifndef _COMPACT
   /* copy parameters from reserved */
   if ((pErrInfo != &pctxt->errInfo.reserved)
         && (pctxt->errInfo.reserved.parmcnt != 0)) {
      OSUINT32 i;
      for (i = 0; i < pctxt->errInfo.reserved.parmcnt; i++) {
         pErrInfo->parms[i] = pctxt->errInfo.reserved.parms[i];
         pctxt->errInfo.reserved.parms[i] = 0;
      }
      pErrInfo->parmcnt = pctxt->errInfo.reserved.parmcnt;
      pctxt->errInfo.reserved.parmcnt = 0;
   }
   if (pErrInfo->stkx < OSRTERRSTKSIZ) {
      pErrInfo->stack[pErrInfo->stkx].module = (const OSUTF8CHAR*)module;
      pErrInfo->stack[pErrInfo->stkx++].lineno = lineno;
   }
   /* If XML element name is present, copy it to the error structure */
   if (0 != pctxt->pXMLInfo) {
      rtxDListToUTF8Str 
         (pctxt, &pctxt->elemNameStack, &pErrInfo->elemName, '.');
   }
#endif
   return (status);
}

EXTRTMETHOD int rtxErrSetNewData (OSCTXT* pctxt, int status,
                      const char* module, int lineno)
{
   OSRTErrInfo* pErrInfo;

   /* create new error info node */

   pErrInfo = rtxErrNewNode (pctxt);
   if (pErrInfo == 0) {

      /* use reseved OSRTErrInfo element */
      
      if (pctxt->errInfo.reserved.status == 0 && status == RTERR_NOMEM) {
         pErrInfo = &pctxt->errInfo.reserved;
         pctxt->errInfo.reservedNode.data = pErrInfo;
         rtxDListAppendNode (&pctxt->errInfo.list, 
            &pctxt->errInfo.reservedNode);
      }
      else
         return RTERR_NOMEM;
   }
   else {
      pctxt->errInfo.reserved.status = 0; /* clear reserved errInfo */
   }
   return rtxErrSetData (pctxt, status, module, lineno);
}

EXTRTMETHOD OSRTErrInfo* rtxErrNewNode (OSCTXT* pctxt)
{
   OSRTErrInfo* pErrInfo;

   pErrInfo = OSRTALLOCELEMDNODEZ (pctxt,OSRTErrInfo);
   if (pErrInfo != 0) {
      rtxDListAppendData (pctxt, &pctxt->errInfo.list, pErrInfo);
   }
   return pErrInfo;
}

EXTRTMETHOD void rtxErrAssertionFailed (const char* conditionText,
                            int lineNo, const char* fileName)
{
   printf ("Run-time assertion '%s' failed.  Line %d, File %s\n",
           conditionText, lineNo, fileName);
#ifndef _ARMTCC
   exit (-1);
#endif
}

EXTRTMETHOD int rtxErrGetFirstError (const OSCTXT* pctxt) 
{
   OSRTErrInfo* pErrInfo = OSRT_GET_FIRST_ERROR_INFO (pctxt);
   if (pErrInfo != 0)
      return pErrInfo->status;
   return 0;
}

EXTRTMETHOD int rtxErrGetLastError (const OSCTXT* pctxt) 
{
   OSRTErrInfo* pErrInfo = OSRT_GET_LAST_ERROR_INFO (pctxt);
   if (pErrInfo != 0)
      return pErrInfo->status;
   return 0;
}

EXTRTMETHOD OSUINT32 rtxErrGetErrorCnt (const OSCTXT* pctxt)
{
   return pctxt->errInfo.list.count;
}

EXTRTMETHOD int rtxErrGetStatus (const OSCTXT* pctxt)
{
   int errcnt = rtxErrGetErrorCnt (pctxt);
   if (errcnt == 0) return 0;
   else if (errcnt == 1) {
      return rtxErrGetFirstError (pctxt);
   }
   else return RTERR_MULTIPLE;
}

EXTRTMETHOD int rtxErrResetLastErrors (OSCTXT* pctxt, int errorsToReset)
{
   OSRTDListNode* pNode = pctxt->errInfo.list.tail, *pPrevNode;

   for (;errorsToReset > 0 && pNode != 0; pNode = pPrevNode, errorsToReset--) {
      OSRTErrInfo* pErrInfo = (OSRTErrInfo*)pNode->data;
      pPrevNode = pNode->prev;

      rtxErrFreeNodeParms (pctxt, pErrInfo);

      if (pErrInfo != &pctxt->errInfo.reserved) {
         rtxDListFreeNode (pctxt, &pctxt->errInfo.list, pNode);
      }
      else { /* just remove, but not free */
         rtxDListRemove (&pctxt->errInfo.list, pNode);
      }
   }
   return 0;
}

