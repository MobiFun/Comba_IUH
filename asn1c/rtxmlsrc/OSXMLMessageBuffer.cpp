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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rtxmlsrc/osrtxml.hh"
#include "rtxmlsrc/OSXMLMessageBuffer.h"

//////////////////////////////////////////
//                                      //
// OSXMLMessageBuffer methods           //
//                                      //
//////////////////////////////////////////

EXTXMLMETHOD OSXMLMessageBuffer::OSXMLMessageBuffer 
(Type bufferType, OSRTContext* pContext) : 
OSRTMessageBuffer (bufferType, pContext) 
{
   if (mpContext->getStatus() != 0) return;

   int stat = rtXmlInitCtxtAppInfo (getCtxtPtr());
   if (0 != stat) LOG_RTERR (getCtxtPtr(), stat);

   /* Add XML error codes to global table */
   rtErrXmlInit ();
}

EXTXMLMETHOD void* OSXMLMessageBuffer::getAppInfo () 
{
   return rtXmlCtxtAppInfoDup 
      (mpContext->getPtr(), mpContext->getPtr());
}

EXTXMLMETHOD void OSXMLMessageBuffer::setNamespace 
(const OSUTF8CHAR* prefix, const OSUTF8CHAR* uri, OSRTDList* pNSAttrs)
{
   rtXmlNSSetNamespace (getCtxtPtr(), pNSAttrs, prefix, uri, TRUE);
}

EXTXMLMETHOD void OSXMLMessageBuffer::setAppInfo (void* pXMLInfo) 
{
   rtXmlSetCtxtAppInfo (mpContext->getPtr(), (OSXMLCtxtInfo*)pXMLInfo);
   // it is necessary to make a copy of pXMLInfo, using the current memory 
   // heap. rtXmlSetCtxtAppInfo does not do copying of pXMLInfo, that is
   // why we need to call ...Dup and ...Set functions.
   pXMLInfo = rtXmlCtxtAppInfoDup 
      (mpContext->getPtr(), mpContext->getPtr());
   rtXmlSetCtxtAppInfo (mpContext->getPtr(), (OSXMLCtxtInfo*)pXMLInfo);
}

EXTXMLMETHOD int OSXMLMessageBuffer::getIndent ()
{
   if (mpContext->getStatus () != 0) return RTERR_NOTINIT;

   return rtXmlGetIndent (mpContext->getPtr());
}

EXTXMLMETHOD int OSXMLMessageBuffer::getIndentChar ()
{
   if (mpContext->getStatus () != 0) return RTERR_NOTINIT;

   return rtXmlGetIndentChar (mpContext->getPtr());
}

EXTXMLMETHOD OSBOOL OSXMLMessageBuffer::getWriteBOM ()
{
   if (mpContext->getStatus () != 0) return FALSE;

   return rtXmlGetWriteBOM (mpContext->getPtr());
}

EXTXMLMETHOD void OSXMLMessageBuffer::setFormatting (OSBOOL doFormatting) 
{
   if (mpContext->getStatus () != 0) return;

   rtXmlSetFormatting (mpContext->getPtr(), doFormatting);
}

EXTXMLMETHOD void OSXMLMessageBuffer::setIndent (OSUINT8 indent) 
{
   if (mpContext->getStatus () != 0) return;

   rtXmlSetIndent (mpContext->getPtr(), indent);
}

EXTXMLMETHOD void OSXMLMessageBuffer::setIndentChar (char indentChar) 
{
   if (mpContext->getStatus () != 0) return;

   rtXmlSetIndentChar (mpContext->getPtr(), indentChar);
}

EXTXMLMETHOD void OSXMLMessageBuffer::setWriteBOM (OSBOOL write)
{
   if (mpContext->getStatus () != 0) return;

   rtXmlSetWriteBOM (mpContext->getPtr(), write);
}


