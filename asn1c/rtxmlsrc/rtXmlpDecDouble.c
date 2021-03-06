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

#include <math.h>
#include "rtxmlsrc/osrtxml.h"
#include "rtxmlsrc/rtXmlPull.h"

static const char nanStr[3] = { 'N', 'a', 'N' };
static const char infStr[3] = { 'I', 'N', 'F' };

EXTXMLMETHOD int rtXmlpDecDouble (OSCTXT* pctxt, OSREAL* pvalue)
{
   size_t i;
   OSBOOL minus = FALSE;
   OSREAL value = 0.;
   OSREAL fracPos = 0.1;
   OSINT32 expVal = 0;
   OSBOOL expMinus = FALSE;
   int pos = 0;
   int stat = 0;
   
   struct OSXMLReader* pXmlReader;
   OSXMLCtxtInfo* xmlCtxt;
   OSXMLDataCtxt dataCtxt;
   
   int mode = 0; 
   /* 0 - sign, 1 - detect, 2 - int, 3 - frac, 
      4 - expSign, 5 - exp, 6 - INF, 7 - NaN */

   OSRTASSERT (0 != pctxt->pXMLInfo);
   xmlCtxt = ((OSXMLCtxtInfo*)pctxt->pXMLInfo);
   pXmlReader = xmlCtxt->pXmlPPReader;
   OSRTASSERT (0 != pXmlReader);

   if (pvalue)
      *pvalue = 0.;

   rtXmlRdSetWhiteSpaceMode (pXmlReader, OSXMLWSM_COLLAPSE);

   if ((stat = rtXmlRdFirstData (pXmlReader, &dataCtxt)) > 0) {
      do {
         const OSUTF8CHAR* const inpdata = dataCtxt.mData.value;
         size_t nbytes = dataCtxt.mData.length;

         i = 0;

         while (i < nbytes && stat >= 0) {
            switch (mode) {
            case 0: /* sign */
               if (inpdata[i] == '+') {
                  i++;
                  mode = 1;
               }
               else if (inpdata[i] == '-') {
                  minus = TRUE;
                  i++;
                  mode = 1;
               }
               else if (inpdata[i] == 'N') {
                  i++;
                  pos++;
                  mode = 7;
               }
               else if (inpdata[i] == 'I') {
                  i++;
                  pos++;
                  mode = 6;
               }
               else if (OS_ISDIGIT (inpdata[i])) {
                  mode = 2;
               }
               else if (inpdata[i] == '.') {
                  i++;
                  mode = 3;
               }
               else {
                  rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, nbytes - i);
                  stat = LOG_RTERRNEW (pctxt, RTERR_INVCHAR);
               }
               break;
            case 1: /* detect */
               if (inpdata[i] == 'I') {
                  i++;
                  pos++;
                  mode = 6;
               }
               else if (OS_ISDIGIT (inpdata[i])) {
                  mode = 2;
               }
               else if (inpdata[i] == '.') {
                  i++;
                  mode = 3;
               }
               else {
                  rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, nbytes - i);
                  stat = LOG_RTERRNEW (pctxt, RTERR_INVCHAR);
               }   
               break;
            case 2: /* integer */
               if (OS_ISDIGIT (inpdata[i])) {
                  OSINT32 tm = inpdata[i] - '0';
                  i++;
                  value = value * 10. + tm;
               }
               else if (inpdata[i] == '.') {
                  i++;
                  mode = 3;
               }
               else if (inpdata[i] == 'E' || inpdata[i] == 'e') {
                  i++;
                  mode = 4;
               }
               else {
                  rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, nbytes - i);
                  stat = LOG_RTERRNEW (pctxt, RTERR_INVCHAR);
               }
               break;
            case 3: /* fractional */
               if (OS_ISDIGIT (inpdata[i])) {
                  OSINT32 tm = inpdata[i] - '0';
                  i++;
                  value += tm * fracPos;
                  fracPos *= 0.1;
               }
               else if (inpdata[i] == 'E' || inpdata[i] == 'e') {
                  i++;
                  mode = 4;
               }
               else {
                  rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, nbytes - i);
                  stat = LOG_RTERRNEW (pctxt, RTERR_INVCHAR);
               }   
               break;
            case 4: /* expSign */
               if (inpdata[i] == '+') {
                  i++;
                  mode = 5;
               }
               else if (inpdata[i] == '-') {
                  expMinus = TRUE;
                  i++;
                  mode = 5;
               }
               else if (OS_ISDIGIT (inpdata[i])) {
                  mode = 5;
               }
               else {
                  rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, nbytes - i);
                  stat = LOG_RTERRNEW (pctxt, RTERR_INVCHAR);
               }
               break;
            case 5: /* exp */
               expVal = expVal * 10 + (inpdata[i] - '0');
               i++;
               if (expVal > 325) { 
                  /* in double ~ 15 digits ( limit 309 + 15 ) */
                  rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, nbytes - i);
                  stat = LOG_RTERRNEW (pctxt, RTERR_TOOBIG);
               }
               break;
            case 6: /* INF */
               if (pos >= 3 || inpdata[i] != infStr[pos]) {
                  rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, nbytes - i);
                  stat = LOG_RTERRNEW (pctxt, RTERR_INVREAL);
               }
               
               i++;
               pos++;
               break;
            case 7: /* NaN */
               if (pos >= 3 || inpdata[i] != nanStr[pos]) {
                  rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, nbytes - i);
                  stat = LOG_RTERRNEW (pctxt, RTERR_INVREAL);
               }
               
               i++;
               pos++;
               break;
            }
         }

         if (stat >= 0) {
            stat = rtXmlRdNextData (pXmlReader, &dataCtxt);
            if (stat < 0)
               LOG_RTERR (pctxt, stat);
         }   
      } while (stat > 0);
   }
   else if (stat < 0)
      LOG_RTERR (pctxt, stat);
   else { /* empty content */
      rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, 1);
      stat = LOG_RTERRNEW (pctxt, RTERR_INVFORMAT);
   }
   
   if (stat >= 0) {
      stat = 0;
      /* If negative, negate number */
      if (mode == 6) {
         if (minus) 
            value = rtxGetMinusInfinity ();
         else
            value = rtxGetPlusInfinity ();
      }
      else if (mode == 7) {
         value = rtxGetNaN ();
      }
      else {
         if (minus) 
            value = -value;
         
         if (expMinus)
            expVal = -expVal;

         if (expVal != 0)
            value *= pow (10., expVal);
         
         if (minus) {
            if (rtxIsMinusInfinity (value)) {
               rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, 1);
               return LOG_RTERRNEW (pctxt, RTERR_TOOBIG);
            }
         }
         else if (rtxIsPlusInfinity (value)) {
            rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, 1);
            return LOG_RTERRNEW (pctxt, RTERR_TOOBIG);
         }
      }   
         
      if (pvalue)
         *pvalue = value;
   }
   
   return stat;
}


