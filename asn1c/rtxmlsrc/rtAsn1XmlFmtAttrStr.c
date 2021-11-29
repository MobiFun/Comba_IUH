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
#include "rtxmlsrc/asn1xml.h"

EXTXMLMETHOD int rtAsn1XmlFmtAttrStr 
(OSCTXT* pctxt, const OSUTF8CHAR* name, const OSUTF8CHAR* value, 
 OSUTF8CHAR** ppAttrStr)
{
  int nLen, vLen;
  OSUTF8CHAR *t;
  
  /* Provided name, value pair should not be null. */
  if (name == NULL) {
    return LOG_RTERR (pctxt, RTERR_NULLPTR);
  }
  else if (value == NULL) {
    return LOG_RTERR (pctxt, RTERR_NULLPTR);
  }
  
  nLen = rtxUTF8Len (name); 
  vLen = rtxUTF8Len (value);

  /* The name should not be empty. */
  if (nLen == 0) {
    return LOG_RTERR (pctxt, RTERR_INVFORMAT);
  }

  /* Allocate memory for the formatted string. */
  t = (OSUTF8CHAR *) rtxMemAlloc (pctxt, sizeof(OSUTF8CHAR)*(nLen+vLen+4));
  if (t == NULL) {
    return LOG_RTERR (pctxt, RTERR_NOMEM);
  }
  *t = '\0';

  /* Concatenate the values together, dying gracefully if it fails.  No 
     rtxUTFStrcat function exists, so I've simply done type-casting; this is
     possibly dangerous! */
  if (strncat ((char *)t, (char *)name, nLen) == NULL || 
      strncat ((char *)t, "=\"", 2) == NULL || 
      strncat ((char *)t, (char *)value, vLen) == NULL || 
      strncat ((char *)t, "\"", 2) == NULL) {
    return LOG_RTERR (pctxt, RTERR_NOMEM);
  }

  /* Success! */
  *ppAttrStr = t;
  
  return 0;
}
