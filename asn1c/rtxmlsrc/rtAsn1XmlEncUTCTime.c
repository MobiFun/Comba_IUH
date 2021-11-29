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

#include "rtsrc/asn1type.h"
#include "rtxsrc/rtxDateTime.h"
#include "rtxmlsrc/asn1xml.h"

EXTXMLMETHOD int rtAsn1XmlEncUTCTime 
(OSCTXT *pctxt, const char* value, const OSUTF8CHAR* elemName, 
 const OSUTF8CHAR* nsPrefix) 
{
   OSNumDateTime dateTime;
   OSUTF8CHAR dateTimeStr[46];
   int stat;

   stat = rtParseUTCTime (pctxt, value, &dateTime);
   if (stat != 0) return LOG_RTERR(pctxt, stat);

   stat = rtxDateTimeToString 
      (&dateTime, dateTimeStr, sizeof (dateTimeStr));
   if (stat < 0) return LOG_RTERR(pctxt, stat);

   stat = rtXmlEncUTF8Str (pctxt, dateTimeStr, elemName, 0);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return 0;
}
