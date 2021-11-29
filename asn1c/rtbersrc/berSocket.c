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

#include "rtbersrc/asn1berSocket.h"
#include "rtsrc/asn1intl.h"
#include "rtxsrc/rtxMemBuf.h"

int berReadFromSocket (OSRTSOCKET socket, OSOCTET* buf, int len)
{
   int curlen = 0;

   while (curlen < len) {
      int rlen = rtxSocketRecv (socket, buf + curlen, len - curlen);
      if (rlen < 0) return rlen;
      if (rlen == 0) break;
      curlen += rlen;
   }

   if (curlen != len)
      return RTERR_READERR;
   return curlen;
}

int berReadTagFromSocket (OSRTSOCKET socket, ASN1TAG* ptag, OSRTMEMBUF* pMemBuf)
{
   OSOCTET	b;
   ASN1TAG	class_form, id_code;
   int  	lcnt = 0, stat = 0;

   *ptag = 0;

   if (berReadFromSocket (socket, &b, 1) == 1)
   {
      stat = rtxMemBufAppend (pMemBuf, &b, 1);
      if (stat != 0) return stat;

      class_form = (ASN1TAG)(b & TM_CLASS_FORM);
      class_form <<= ASN1TAG_LSHIFT;

      if ((id_code = b & TM_B_IDCODE) == 31)
      {
         id_code = 0;
         do {
            if (berReadFromSocket (socket, &b, 1) == 1) {
               stat = rtxMemBufAppend (pMemBuf, &b, 1);
               if (stat != 0) return stat;
               
               id_code = (id_code * 128) + (b & 0x7F);
               if (id_code > TM_IDCODE || lcnt++ > 8) 
                  return (ASN_E_BADTAG);
            }
            else {
               stat = RTERR_ENDOFFILE;
               break;
            }
         } while (b & 0x80);
      }

      *ptag = class_form | id_code;
   }
   else
      stat = RTERR_ENDOFFILE;

   return (stat);
}

int berReadLengthFromSocket (OSRTSOCKET socket, OSINT32* plen, OSRTMEMBUF* pMemBuf)
{ 
   OSOCTET    i, b;
   int          stat = 0;

   *plen = 0;

   if (berReadFromSocket (socket, &b, 1) == 1)
   {
      stat = rtxMemBufAppend (pMemBuf, &b, 1);
      if (stat != 0) return stat;

      if (b > 0x80)
      {
         i = (OSOCTET) (b & 0x7F);
         if (i > 4) return ASN_E_INVLEN;
         for (*plen = 0; i > 0; i--) 
            if (berReadFromSocket (socket, &b, 1) == 1) {

               stat = rtxMemBufAppend (pMemBuf, &b, 1);
               if (stat != 0) return stat;
               
               *plen = (*plen * 256) + b;
            }
            else 
               return (RTERR_ENDOFFILE);
      }
      else if (b == 0x80) *plen = ASN_K_INDEFLEN;
      else *plen = b;
   }
   else stat = RTERR_ENDOFFILE;

   return (stat);
} 

int berReadTagAndLenFromSocket (OSRTSOCKET socket, ASN1TAG* ptag, OSINT32* plen, 
                                OSRTMEMBUF* pMemBuf)
{
   int stat;

   stat = berReadTagFromSocket (socket, ptag, pMemBuf);
   if (stat != 0) return stat;

   stat = berReadLengthFromSocket (socket, plen, pMemBuf);
   if (stat != 0) return stat;

   return 0;
}

int berReadPastEOCFromSocket (OSRTSOCKET socket, OSRTMEMBUF* pMemBuf)
{
   ASN1TAG tag;
   int ilcnt = 1, len, stat = 0;

   while (ilcnt > 0) {
      stat = berReadTagAndLenFromSocket (socket, &tag, &len, pMemBuf);
      if (stat != 0) break;

      if (len > 0) {
         stat = rtxMemBufPreAllocate (pMemBuf, (OSUINT32)len);
         if (stat != 0) break;

         if (berReadFromSocket (socket, OSMEMBUFENDPTR(pMemBuf), len) != len)
         {
            stat = RTERR_READERR;
            break;
         }
         pMemBuf->usedcnt += len;
      }
      else if (len == ASN_K_INDEFLEN) ilcnt++;
      else if (tag == 0 && len == 0) ilcnt--;
   }

   return stat;
}

int berReadContentsFromSocket (OSRTSOCKET socket, int len, OSRTMEMBUF* pMemBuf)
{
   int stat;

   if (len > 0) {
      /* First check to make sure that component will fit in buffer */

      stat = rtxMemBufPreAllocate (pMemBuf, (OSUINT32)len);
      if (stat != 0) return stat;

      /* Read component from file into the message buffer */

      if (berReadFromSocket (socket, OSMEMBUFENDPTR(pMemBuf), len) != len)
      {
         return RTERR_READERR;
      }
      pMemBuf->usedcnt += len;
      return 0;
   }
   else if (len == ASN_K_INDEFLEN)
      return berReadPastEOCFromSocket (socket, pMemBuf);
   else
      return len;

}

int berReadMsgFromSocket (OSCTXT* pctxt, OSRTSOCKET socket, 
                          OSOCTET* buffer, int bufsiz, 
                          OSOCTET** ppDestBuffer, int* pMessageSize)
{
   OSRTMEMBUF membuf;
   int stat, len;
   ASN1TAG tag;

   if ((buffer == 0 || bufsiz == 0) && ppDestBuffer == 0) 
      return LOG_RTERR (pctxt, RTERR_INVPARAM);
   if (buffer == 0 || bufsiz == 0) {
      rtxMemBufInit (pctxt, &membuf, ASN_K_MEMBUFSEG);
   }
   else {
      rtxMemBufInitBuffer (pctxt, &membuf, buffer, bufsiz, ASN_K_MEMBUFSEG);
      rtxMemBufSetExpandable (&membuf, FALSE);
   }

   stat = berReadTagAndLenFromSocket (socket, &tag, &len, &membuf);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   stat = berReadContentsFromSocket (socket, len, &membuf);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   if (ppDestBuffer != 0) {
      *ppDestBuffer = membuf.buffer;
      membuf.buffer = 0; /* prevent from freeing */
   }
   if (pMessageSize != 0) 
      *pMessageSize = (int)membuf.usedcnt;

   rtxMemBufFree (&membuf);
   return 0;
}


