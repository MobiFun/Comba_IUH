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

#include "rtxmlsrc/osrtxml.hh"
#include "rtxmlsrc/rtXmlPull.h"
#include "rtxsrc/rtxCtype.h"
#include "rtxsrc/rtxErrCodes.h"

static int createReader (OSCTXT* pctxt, OSXMLCtxtInfo* xmlCtxt)
{
   struct OSXMLReader* pXmlReader;

   if (0 == xmlCtxt->pXmlPPReader) {
      pXmlReader = rtXmlRdCreateXmlReader (pctxt);
      if (pXmlReader == 0) return LOG_RTERR (pctxt, RTERR_NULLPTR);

      xmlCtxt->pXmlPPReader = pXmlReader;
   }
   else {
      rtXmlRdResetXmlReader (xmlCtxt->pXmlPPReader);
   }

#ifndef __SYMBIAN32__ /* Symbian doesn't support global diag. */
   if (rtxDiagEnabled(pctxt))
      rtxSetGlobalDiag (TRUE);
#endif

   return 0;
}

EXTXMLMETHOD int rtXmlpCreateReader (OSCTXT* pctxt)
{
   OSRTASSERT (0 != pctxt->pXMLInfo);
   
   createReader (pctxt, (OSXMLCtxtInfo*)pctxt->pXMLInfo);

   return 0;
}

EXTXMLMETHOD struct OSXMLReader* rtXmlpGetReader (OSCTXT* pctxt)
{
   OSXMLCtxtInfo* xmlCtxt;
   struct OSXMLReader* pXmlReader;

   OSRTASSERT (0 != pctxt->pXMLInfo);
   xmlCtxt = ((OSXMLCtxtInfo*)pctxt->pXMLInfo);
   if (0 == xmlCtxt->pXmlPPReader) {
      createReader (pctxt, xmlCtxt);
   }

   pXmlReader = xmlCtxt->pXmlPPReader;
   OSRTASSERT (0 != pXmlReader);

   return pXmlReader;
}

