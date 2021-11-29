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
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxMemory.h"

static int readFile (OSCTXT* pctxt, const char* filePath, 
                     OSOCTET** ppMsgBuf, size_t* pLength, char fileType)
{
   const char* access = (fileType == 'a') ? "r" : "rb";
   FILE* fp = fopen (filePath, access);
   OSOCTET* msgbuf;
   if (0 != fp) {
      long len;
      size_t len2;
      fseek (fp, 0L, SEEK_END);
      if ((len = ftell(fp)) != -1L) {
         /* If text file, allocate one more char than length to hold 
            null terminator char */
         size_t memsize = len;
         if (fileType == 'a') memsize++;
         msgbuf = (OSOCTET*) rtxMemAlloc (pctxt, memsize);
         if (msgbuf == NULL) {
            fclose (fp);
            return LOG_RTERR (pctxt, RTERR_NOMEM);
         }
         fseek (fp, 0L, SEEK_SET);

         len2 = fread (msgbuf, 1, (size_t)len, fp);
         fclose (fp);

         if ((long)len2 != len && !OSCRTLSTRCMP (access, "rb")) {
            rtxMemFreeArray (pctxt, msgbuf);
            return LOG_RTERR (pctxt, RTERR_READERR);
         }

         *ppMsgBuf = msgbuf;
         *pLength = len2;

         /* Add null terminator */
         if (fileType == 'a') msgbuf[len2] = '\0';

         return 0;
      }
      else {
         fclose (fp);
         return LOG_RTERR (pctxt, RTERR_READERR);
      }
   }
   else
      return LOG_RTERR (pctxt, RTERR_FILNOTFOU);
}

EXTRTMETHOD int rtxFileReadBinary (OSCTXT* pctxt, const char* filePath, 
                       OSOCTET** ppMsgBuf, size_t* pLength)
{
   return readFile (pctxt, filePath, ppMsgBuf, pLength, 'b');
}

EXTRTMETHOD int rtxFileReadText (OSCTXT* pctxt, const char* filePath, 
                     OSOCTET** ppMsgBuf, size_t* pLength)
{
   return readFile (pctxt, filePath, ppMsgBuf, pLength, 'a');
}

EXTRTMETHOD int rtxFileWriteBinary 
(const char* filePath, const OSOCTET* pMsgBuf, size_t length)
{
   FILE* fp;
   int stat = 0;
   if ( 0 != (fp = fopen (filePath, "wb")) ) {
      fwrite (pMsgBuf, 1, length, fp);
      fclose (fp);
   }
   else stat = RTERR_WRITEERR;

   return stat;
}

