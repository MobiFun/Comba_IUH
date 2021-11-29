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
/*
// CHANGE LOG
// Date         Init    Description
// 06/20/02     ED      Modified to copy data directly 
//
////////////////////////////////////////////////////////////////////////////
*/
#include "xee_common.hh"
#if OS_ASN1RT_VERSION >= 600
#include "rtxsrc/rtxBuffer.h"
#endif

static int isBinaryData (const OSOCTET *data, OSUINT32 nocts);

int xerEncOpenType (OSCTXT* pctxt, OSUINT32 nocts, 
                    const OSOCTET* data, 
                    const char* elemName)
{
   int stat;

/*   if (0 != isBinaryData (data, nocts)) {
      stat = xerEncStartElement (pctxt, "binext", 0);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      stat = xerEncHexStrValue (pctxt, nocts, data);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      stat = xerEncEndElement (pctxt, "binext");
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }

   else { */
		if (0 != elemName) {
	   	stat = xerEncStartElement (pctxt, elemName, 0);
	   	if (stat != 0) return LOG_RTERR (pctxt, stat);
		}
		else {
	   	stat = xerEncIndent (pctxt);
	  	   if (stat != 0) return LOG_RTERR (pctxt, stat);

	   	pctxt->state = XERSTART;
		}

		/* Copy bytes as-is to the output buffer (ED, 6/20/02) */
		stat = rtxWriteBytes (pctxt, data, nocts);
		if (stat != 0) return LOG_RTERR (pctxt, stat);

		if (0 != elemName) {
		   stat = xerEncEndElement (pctxt, elemName);
		   if (stat != 0) return LOG_RTERR (pctxt, stat);
		}
		else {
		   pctxt->state = XEREND;
		}
//   }

   return (0);
}

int
isBinaryData (const OSOCTET *data, OSUINT32 nocts)
{
   unsigned int i;

   if (data[0] != 0) return -1;

   for (i = 0; i < nocts; i ++) {
      if (data[i] < 32 || data[i] > 127) {
         return -1;
      }
   }

   return 0;
}

