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
#include "rtxsrc/rtxCtype.h"
#include "rtxsrc/rtxBigInt.h"
#include "rtxsrc/rtxErrCodes.h"

EXTXMLMETHOD int rtXmlEncBigIntAttr (OSCTXT* pctxt, const OSUTF8CHAR* value, 
                        const OSUTF8CHAR* attrName, size_t attrNameLen)
{
   int stat;

   OSRTASSERT (0 != attrName);

   /* Verify element will fit in encode buffer */

   /* 4 extra chars = space + equal sign + two double quotes + final '>' */
   stat = rtxCheckBuffer (pctxt, attrNameLen + 5); 
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   /* Copy data to buffer */

   OSRTPUTCHAR (pctxt, ' ');
   OSRTMEMCPY (pctxt, attrName, attrNameLen);
   OSRTPUTCHAR (pctxt, '=');
   OSRTPUTCHAR (pctxt, '\"');
   
   stat = rtXmlEncBigIntValue (pctxt, value);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   OSRTPUTCHAR (pctxt, '\"');

   if (rtxCtxtTestFlag (pctxt, OSXMLC14N)) {
      stat = rtXmlEncAttrC14N (pctxt);     
      if (0 != stat) return LOG_RTERR (pctxt, stat);
   }

   return 0;
}

