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

#include "rtxsrc/rtxCtype.h"
#include "rtxsrc/rtxStreamBuffered.h"
#include "rtxmlsrc/osrtxml.hh"

static int expandNameBuffer (OSCTXT* pctxt, OSRTBuffer* pNameBuf);

EXTXMLMETHOD int rtXmlParseElemQName (OSCTXT* pctxt, OSXMLQName* pQName)
{
   int stat = 0, len = 0;
   OSOCTET buf[512], *p, *pend;
   int state = 0;
   OSRTBuffer namebuf;
   size_t nameIdx = 0;

   if (pctxt->pStream == 0 && OSRTBUFFER (pctxt) == 0) {
      return LOG_RTERRNEW (pctxt, RTERR_NOTINIT);
   }

   OSCRTLMEMSET (&namebuf, 0, sizeof(namebuf));
   pQName->nsPrefix = pQName->ncName = 0;

   if (pctxt->pStream != 0 && !rtxStreamMarkSupported (pctxt)) {
      stat = rtxStreamBufferedCreate (pctxt, 
         OSRTSTRMCM_RESTORE_UNDERLAYING_AFTER_RESET);
   }

   if (stat == 0) {
      int i;
      if (pctxt->pStream != 0) {
         rtxStreamMark (pctxt, INT_MAX);
      }
      for (i = 0; ; i++) {
         if (pctxt->pStream != 0) {
            if ((len = rtxStreamRead (pctxt, buf, sizeof (buf))) <= 0)
               break;
            p = buf;
            pend = &buf [len - 1];
         }
         else {
            if (i > 0) {
               /* only one iteration for buffered pctxt is necessary, since 
                  whole buffer is available immediatelly. */
               break;
            }
            len = (int)(OSRTBUFSIZE (pctxt) - (OSRTBUFPTR (pctxt) - OSRTBUFFER (pctxt)));
            p = OSRTBUFPTR (pctxt);
            pend = p + len - 1;
         }
         for (; state >= 0 && p <= pend; ) {
            switch (state) {
               case 0: /* search for '<' */
                  if (*p == '<') {
                     state = 1; /* change state to 1 */
                  }
                  p++;
                  break;

               case 1: /* '<' found, check the next letter */
                  if (OS_ISALPHA (*p)) {
                     /* retrieve name - state 2 */
                     state = 2;
                  }
                  else if (*p == '!') {
                     state = 10; /* comments, state 10 */
                     p++;
                  }
                  else state = 0; /* not alpha - return state to 0 */
                  break;

               case 2: /* retrieve name until space */
                  if (nameIdx + 1 >= namebuf.size) {
                     stat = expandNameBuffer (pctxt, &namebuf);
                     if (0 != stat) return LOG_RTERR (pctxt, stat);
                  }

                  /* if colon (:), this is a qname, state 3 */
                  if (*p == ':') {
                     state = 3; /* parsed namespace prefix */
                  }

                  /* if space, this is end of local part of name */
                  else if (!OS_ISALPHA (*p) && !OS_ISDIGIT (*p) && 
                           *p != '-' && *p != '_') {
                     state = 4; /* parsed local name */
                  }
                  else
                     namebuf.data[nameIdx++] = *p++;

                  break;

               case 3: { /* set namespace prefix in QName */
                  OSUTF8CHAR* nsPrefix;

                  namebuf.data[nameIdx++] = 0;

                  nsPrefix = 
                     (OSUTF8CHAR*) rtxMemAlloc (pctxt, nameIdx);
                  OSCRTLMEMCPY (nsPrefix, namebuf.data, nameIdx);
                  pQName->nsPrefix = nsPrefix;

                  /* set state to parse local name */
                  p++; /* move past colon */
                  nameIdx = 0;
                  state = 2; 
                  break;
               }

               case 4: { /* set local name in QName */
                  OSUTF8CHAR* ncName;
                  namebuf.data[nameIdx++] = 0;

                  ncName = 
                     (OSUTF8CHAR*) rtxMemAlloc (pctxt, nameIdx);
                  OSCRTLMEMCPY (ncName, namebuf.data, nameIdx);
                  pQName->ncName = ncName;

                  state = -1; 
                  break;
               }

               case 10: /* comments, '-' */
               case 11: /* comments, '-' */
                  if (*p == '-') {
                     state++;
                     p++;
                  }
                  else 
                     return LOG_RTERRNEW (pctxt, RTERR_XMLPARSE);
                  break;

               case 12: /* comments, now wait for end of comments */
               case 13:
                  if (*p == '-')
                     state++;
                  else 
                     state = 12;
                  p++;
                  break;

               case 14: /* comments, check for '>' */
                  if (*p == '>') {
                     state = 0;
                     p++;
                  }
                  else
                     state = 12;
                  break;
            }
         }
         if (state < 0) break;
      }
      if (len < 0) stat = len;
      if (state != -1)
         stat = LOG_RTERRNEW (pctxt, RTERR_XMLPARSE);

      if (pctxt->pStream != 0) {
         rtxStreamReset (pctxt);
      }
      rtxMemFreePtr (pctxt, namebuf.data);
   }

   return stat;
}

static int expandNameBuffer (OSCTXT* pctxt, OSRTBuffer* pNameBuf)
{
   OSOCTET* pNewName = (OSOCTET*)
      rtxMemRealloc (pctxt, pNameBuf->data, pNameBuf->size += 100);

   if (pNewName == 0) {
      rtxMemFreePtr (pctxt, pNameBuf->data);
      if (pctxt->pStream != 0) {
         rtxStreamBufferedRelease (pctxt);
      }
      return LOG_RTERRNEW (pctxt, RTERR_NOMEM);
   }

   pNameBuf->data = pNewName;

   return 0;
}


