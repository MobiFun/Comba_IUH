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

#include "rtxmlsrc/osrtxml.h"
#include "rtxmlsrc/rtXmlPull.h"

#define BASE64TOINT(c) (((c) < 128) ? decodeTable [(c) - 40] : -1)

/*
 * This array is a lookup table that translates characters
 * drawn from the "Base64 Alphabet" (as specified in Table 1 of RFC 2045)
 * into their 6-bit positive integer equivalents. Characters that
 * are not in the Base64 alphabet but fall within the bounds of the
 * array are translated to -1. Note, first 40 values are omitted, because
 * all of them are -1. Use offset -40 to fetch values from this table.
 */
static const signed char decodeTable[] = {
   /*   
   -1, -1, -1, -1, -1, -1, -1, -1, 
   -1, -1, -1, -1, -1, -1, -1, -1, 
   -1, -1, -1, -1, -1, -1, -1, -1, 
   -1, -1, -1, -1, -1, -1, -1, -1, 
   -1, -1, -1, -1, -1, -1, -1, -1, */
   -1, -1, -1, 62, -1, -1, -1, 63, 
   52, 53, 54, 55, 56, 57, 58, 59, 
   60, 61, -1, -1, -1, -1, -1, -1, 
   -1,  0,  1,  2,  3,  4,  5,  6, 
   7,   8,  9, 10, 11, 12, 13, 14, 
   15, 16, 17, 18, 19, 20, 21, 22, 
   23, 24, 25, -1, -1, -1, -1, -1, 
   -1, 26, 27, 28, 29, 30, 31, 32, 
   33, 34, 35, 36, 37, 38, 39, 40, 
   41, 42, 43, 44, 45, 46, 47, 48, 
   49, 50, 51, -1, -1, -1, -1, -1
};

EXTXMLMETHOD int rtXmlpDecBase64Str (OSCTXT* pctxt, 
                       OSOCTET* pvalue, OSUINT32* pnocts, 
                       OSINT32 bufsize)
{
   OSXMLDataCtxt dataCtxt;
   OSXMLCtxtInfo* xmlCtxt;
   struct OSXMLReader* pXmlReader;
   size_t oldsize = 0;
   size_t dstPos = 0;
   size_t srcPos = 0;
   OSBOOL pad = FALSE;
   int prevVal = 0; /* remove warning C4701 */
   int stat = 0;

   OSRTASSERT (0 != pctxt->pXMLInfo);
   xmlCtxt = ((OSXMLCtxtInfo*)pctxt->pXMLInfo);
   pXmlReader = xmlCtxt->pXmlPPReader;
   OSRTASSERT (0 != pXmlReader);

   if (pnocts)
      *pnocts = 0;
   
   rtXmlRdSetWhiteSpaceMode (pXmlReader, OSXMLWSM_COLLAPSE);

   if ((stat = rtXmlRdFirstData (pXmlReader, &dataCtxt)) > 0) {
      do {
         const OSUTF8CHAR* const inpdata = dataCtxt.mData.value;
         size_t nbytes = dataCtxt.mData.length;
         size_t i;

         for (i = 0; i < nbytes; i++, oldsize++) {
            OSUTF8CHAR c = inpdata[i];
            int val;
            
#ifdef _PULL_FROM_BUFFER
            if (c == ' ') continue;
#else
            if (c == ' ' || c == '\r' || c == '\n' || c == '\t') continue;
#endif            
            if (c == '=') {
               if ((srcPos & 3) >= 2) {
                  pad = TRUE;
                  srcPos++;
                  continue;
               }
               else {
                  rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, nbytes - i);
                  stat = LOG_RTERRNEW (pctxt, RTERR_INVBASE64);
                  break;
               }   
            }
            
            if (pad) {
               rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, nbytes - i);
               stat = LOG_RTERRNEW (pctxt, RTERR_INVBASE64);
               break;
               }
            
            val = BASE64TOINT(c);
            
            if (val < 0) {
               rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, nbytes - i);
               stat = LOG_RTERRNEW (pctxt, RTERR_INVBASE64);
               break;
            }   

            if (dstPos >= (size_t)bufsize) {
               rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, nbytes - i);
               stat = LOG_RTERRNEW (pctxt, RTERR_STROVFLW);
               break;
            }   
            
            if (pvalue) {
               switch (srcPos & 3) {
               case 0:
                  pvalue[dstPos] = (OSOCTET)(val << 2);
                  break;
               case 1:
                  pvalue[dstPos] |= (OSOCTET)(val >> 4);
                  dstPos++;
                  break;
               case 2:
                  pvalue[dstPos] = (OSOCTET)((prevVal << 4) | (val >> 2));
                  dstPos++;
                  break;
               case 3:
                  pvalue[dstPos] = (OSOCTET)((prevVal << 6) | val);
                  dstPos++;
                  break;
               }
            }
            else if ((srcPos & 3) > 0)
               dstPos++;
            
            srcPos++;
            prevVal = val;
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

   if (stat >= 0 && (srcPos % 4) != 0) {
      rtXmlRdErrAddDataSrcPos (pXmlReader, &dataCtxt, 1);
      stat = LOG_RTERRNEW (pctxt, RTERR_INVBASE64);
   }
   
   if (stat >= 0) {
      stat = 0;
      if (pnocts)
         *pnocts = (OSUINT32)dstPos;
   }
   
   return stat;
}


