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

#include "rtxsrc/rtxBase64.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxMemory.h"

static char getBase64Char (int index)
{
   if (index >= 0 && index <= 25) return (char)('A' + (char)index);
   else if (index > 25 && index <= 51) return (char)('a' + (char)index);
   else if (index > 51 && index <= 61) return (char)('0' + (char)index);
   else if (index == 62) return '+';
   else if (index == 63) return '/';
   else return -1;
}

EXTRTMETHOD long rtxBase64EncodeData 
(OSCTXT* pctxt, const char* pSrcData, size_t srcDataSize, OSOCTET** ppDstData) 
{
   size_t i;
   OSOCTET* pDstData;
   size_t numFullGroups = srcDataSize/3;
   size_t numBytesInPartialGroup = srcDataSize - 3*numFullGroups;
   size_t resultLen = 4*((srcDataSize + 2)/3);

   pDstData = *ppDstData = rtxMemAllocArray (pctxt, resultLen + 1, OSOCTET);
   if (pDstData == 0) return LOG_RTERRNEW (pctxt, RTERR_NOMEM);

   /* Translate all full groups from byte array elements to Base64 */
   for (i = 0; i < numFullGroups; i++) {
       int byte0 = *pSrcData++ & 0xff;
       int byte1 = *pSrcData++ & 0xff;
       int byte2 = *pSrcData++ & 0xff;
       *pDstData++ = getBase64Char (byte0 >> 2);
       *pDstData++ = getBase64Char (((byte0 << 4) & 0x3f) | (byte1 >> 4));
       *pDstData++ = getBase64Char (((byte1 << 2) & 0x3f) | (byte2 >> 6));
       *pDstData++ = getBase64Char (byte2 & 0x3f);
   }

   /* Translate partial group if present */
   if (numBytesInPartialGroup != 0) {
       int byte0 = *pSrcData++ & 0xff;
       *pDstData++ = getBase64Char (byte0 >> 2);
       if (numBytesInPartialGroup == 1) {
          *pDstData++ = getBase64Char ((byte0 << 4) & 0x3f);
          *pDstData++ = '=';
          *pDstData++ = '=';
       } else {
          /* assert numBytesInPartialGroup == 2; */
          int byte1 = *pSrcData++ & 0xff;
          *pDstData++ = getBase64Char (((byte0 << 4) & 0x3f) | (byte1 >> 4));
          *pDstData++ = getBase64Char ((byte1 << 2) & 0x3f);
          *pDstData++ = '=';
       }
   }
   return (long)resultLen;
}

/* Decode */

static long base64ToBin (OSCTXT* pctxt, 
                         const char* pSrcData, 
                         OSOCTET* pvalue, 
                         size_t numFullGroups, 
                         size_t missingBytesInLastGroup)
{
   OSOCTET* bufp = pvalue;
   size_t i;
   int ch0, ch1, ch2, ch3;

   /* Translate all full groups from base64 to byte array elements */
   for (i = 0; i < numFullGroups; i++) {
      ch0 = *pSrcData; pSrcData++;
      ch1 = *pSrcData; pSrcData++;
      ch2 = *pSrcData; pSrcData++;
      ch3 = *pSrcData; pSrcData++;
      if ((ch0 | ch1 | ch2 | ch3) < 0) 
         return (0 != pctxt) ? 
            LOG_RTERRNEW (pctxt, RTERR_INVBASE64) : RTERR_INVBASE64;

      *pvalue++ = (OSOCTET) ((ch0 << 2) | (ch1 >> 4));
      *pvalue++ = (OSOCTET) ((ch1 << 4) | (ch2 >> 2));
      *pvalue++ = (OSOCTET) ((ch2 << 6) | ch3);
   }

   /* Translate partial group, if present */
   if (missingBytesInLastGroup != 0) {
      ch0 = *pSrcData; pSrcData++;
      ch1 = *pSrcData; pSrcData++;
      if ((ch0 | ch1) < 0) 
         return (0 != pctxt) ? 
            LOG_RTERRNEW (pctxt, RTERR_INVBASE64) : RTERR_INVBASE64;
      *pvalue++ = (OSOCTET) ((ch0 << 2) | (ch1 >> 4));

      if (missingBytesInLastGroup == 1) {
         ch2 = *pSrcData; pSrcData++;
         if (ch2 < 0) 
            return (0 != pctxt) ? 
               LOG_RTERRNEW (pctxt, RTERR_INVBASE64) : RTERR_INVBASE64;
         *pvalue++ = (OSOCTET) ((ch1 << 4) | (ch2 >> 2));
      }
   }

   return (long)(pvalue - bufp);
}

static long getBinDataLen (const char* pSrcData, 
                           size_t srcDataSize, 
                           size_t* pNumFullGroups, 
                           size_t* pMissingBytesInLastGroup)
{
   size_t numGroups = srcDataSize/4;
   size_t missingBytesInLastGroup = 0;
   size_t numFullGroups = numGroups;

   if (4*numGroups != srcDataSize)
      return RTERR_INVBASE64;

   if (srcDataSize != 0) {
      if (pSrcData[srcDataSize - 1] == '=') {
         missingBytesInLastGroup++;
         numFullGroups--;
      }
      if (pSrcData[srcDataSize - 2] == '=')
         missingBytesInLastGroup++;
   }

   if (0 != pNumFullGroups) *pNumFullGroups = numFullGroups;
   if (0 != pMissingBytesInLastGroup) 
      *pMissingBytesInLastGroup = missingBytesInLastGroup;

   return 3*numGroups - missingBytesInLastGroup;
}

EXTRTMETHOD long rtxBase64DecodeData 
(OSCTXT* pctxt, const char* pSrcData, size_t srcDataSize, OSOCTET** ppDstData) 
{
   size_t missingBytesInLastGroup;
   size_t numFullGroups;
   size_t bufsiz;
   OSOCTET* pvalue;
   long stat = getBinDataLen 
      (pSrcData, srcDataSize, &numFullGroups, &missingBytesInLastGroup);

   if (stat < 0) return LOG_RTERRNEW (pctxt, (int)stat);
   else bufsiz = (size_t) stat;

   pvalue = *ppDstData = rtxMemAllocArray (pctxt, bufsiz, OSOCTET);
   if (pvalue == 0) return LOG_RTERRNEW (pctxt, RTERR_NOMEM);

   return base64ToBin (pctxt, pSrcData, pvalue, 
                       numFullGroups, missingBytesInLastGroup);
}

EXTRTMETHOD long rtxBase64DecodeDataToFSB 
(OSCTXT* pctxt, const char* pSrcData, size_t srcDataSize, 
 OSOCTET* buf, size_t bufsiz)
{
   size_t missingBytesInLastGroup;
   size_t numFullGroups;
   size_t nbytes;
   long stat = getBinDataLen 
      (pSrcData, srcDataSize, &numFullGroups, &missingBytesInLastGroup);

   if (stat < 0) 
      return (0 != pctxt) ? LOG_RTERRNEW (pctxt, (int)stat) : (int)stat;
   else 
      nbytes = (size_t) stat;

   if (nbytes > bufsiz) 
      return (0 != pctxt) ? 
         LOG_RTERRNEW (pctxt, RTERR_BUFOVFLW) : RTERR_BUFOVFLW;

   return base64ToBin (pctxt, pSrcData, buf, 
                       numFullGroups, missingBytesInLastGroup);
}

EXTRTMETHOD long rtxBase64GetBinDataLen 
(const char* pSrcData, size_t srcDataSize)
{
   return getBinDataLen (pSrcData, srcDataSize, 0, 0);
}
