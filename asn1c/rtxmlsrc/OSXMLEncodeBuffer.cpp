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
#include "rtxmlsrc/OSXMLEncodeBuffer.h"
#include "rtxsrc/osMacros.h"

//////////////////////////////////////////
//                                      //
// OSXMLEncodeBuffer methods            //
//                                      //
//////////////////////////////////////////

EXTXMLMETHOD OSXMLEncodeBuffer::OSXMLEncodeBuffer () : OSXMLMessageBuffer(XMLEncode)
{ 
   if (mpContext->getStatus () != 0) return;

   int stat = rtXmlSetEncBufPtr (getCtxtPtr(), 0, 0);
   if (stat != 0) LOG_RTERR (getCtxtPtr(), stat);
}

EXTXMLMETHOD OSXMLEncodeBuffer::OSXMLEncodeBuffer (OSOCTET* pMsgBuf, size_t msgBufLen) :
   OSXMLMessageBuffer (XMLEncode)
{
   if (mpContext->getStatus () != 0) return;

   int stat = rtXmlSetEncBufPtr (getCtxtPtr(), pMsgBuf, msgBufLen);
   if (0 != stat) LOG_RTERR (getCtxtPtr(), stat);
}

// This method adds an XML header to the encode buffer

EXTXMLMETHOD int OSXMLEncodeBuffer::addXMLHeader (
const OSUTF8CHAR* version, const OSUTF8CHAR* encoding, OSBOOL newLine)
{
   if (0 != version && 0 != encoding) {
      size_t len = OSUTF8LEN(version) + OSUTF8LEN(encoding) + 32;
      OSCTXT* pctxt = getCtxtPtr();

      /* Encode Unicode BOM */
      int stat = rtXmlEncBOM (pctxt);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      // Verify text will fit in encode buffer
      stat = rtxCheckBuffer (pctxt, len+1);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      OSRTMEMCPY (pctxt, "<?xml version=\"", 15);
      OSRTMEMCPY (pctxt, version, OSUTF8LEN(version));
      OSRTMEMCPY (pctxt, "\" encoding=\"", 12);
      OSRTMEMCPY (pctxt, encoding, OSUTF8LEN(encoding));
      OSRTMEMCPY (pctxt, "\"?>", 3);
      if (newLine) OSRTPUTCHAR (pctxt, '\n');

      // Indicate XML message shouls be encoded as a fragment since
      // header had already been added manually..
      setFragment ();
   }
   return 0;
}

// This method adds encoded XML text to the encode buffer

EXTXMLMETHOD int OSXMLEncodeBuffer::addXMLText (const OSUTF8CHAR* text)
{
   if (0 != text) {
      size_t len = rtxUTF8LenBytes (text);
      OSCTXT* pctxt = getCtxtPtr();

      // Verify text will fit in encode buffer
      int stat = rtxCheckBuffer (pctxt, len+1);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      OSRTMEMCPY (pctxt, text, len);
   }
   return 0;
}

// This method resets the encode buffer to allow another message to be 
// encoded..

EXTXMLMETHOD int OSXMLEncodeBuffer::init ()
{
   OSCTXT* pctxt = getCtxtPtr();
   pctxt->buffer.byteIndex = 0;
   pctxt->state = OSXMLINIT;
   return 0;
}

// Indicate data to be encoded as XML fragment

EXTXMLMETHOD void OSXMLEncodeBuffer::setFragment (OSBOOL value)
{
   OSCTXT* pctxt = getCtxtPtr();
   rtXmlSetEncDocHdr (pctxt, !value);
}

// Write XML document out to given filename
// returns: number of bytes written or negative status code if error

EXTXMLMETHOD long OSXMLEncodeBuffer::write (const char* filename)
{
   FILE* fp;
   long nbytes = -1;
   fp = fopen (filename, "wb");
   if (0 != fp) {
      nbytes = write (fp);
      fclose (fp);
   }
   return nbytes;
}

// Write XML document out to given file
// returns: number of bytes written or negative status code if error

EXTXMLMETHOD long OSXMLEncodeBuffer::write (FILE* fp)
{
   return (long)fwrite (getMsgPtr(), 1, getMsgLen(), fp);
}

