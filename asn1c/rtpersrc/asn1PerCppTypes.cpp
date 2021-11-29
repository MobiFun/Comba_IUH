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
//
// CHANGE LOG
// Date         Init    Description
// 07/14/02     ED      Lowercase method names
//
////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <string.h>
#include "asn1PerCppTypes.h"
#include "rtsrc/asn1intl.h"
#include "rtsrc/rt_common.hh"

//////////////////////////////////////////
//                                      //
// ASN1PERMessageBuffer methods          //
//                                      //
//////////////////////////////////////////

EXTPERMETHOD ASN1PERMessageBuffer::ASN1PERMessageBuffer (Type bufferType, 
                                            OSBOOL aligned) : 
   ASN1MessageBuffer(bufferType) 
{
   int stat;
   if ((stat = pu_setBuffer (mpContext->getPtr(), 0, 0, aligned)) != 0)
      LOG_RTERR (mpContext->getPtr(), stat);
}

EXTPERMETHOD ASN1PERMessageBuffer::ASN1PERMessageBuffer (Type bufferType, 
                                            OSOCTET* pMsgBuf, 
                                            size_t msgBufLen, 
                                            OSBOOL aligned) :
   ASN1MessageBuffer (bufferType) 
{
   int stat;
   if ((stat = pu_setBuffer 
                 (mpContext->getPtr(), pMsgBuf, msgBufLen, aligned)) != 0)
      LOG_RTERR (mpContext->getPtr(), stat);
}

EXTPERMETHOD ASN1PERMessageBuffer::ASN1PERMessageBuffer (Type bufferType, 
                                            OSOCTET* pMsgBuf, 
                                            size_t msgBufLen, 
                                            OSBOOL aligned, 
                                            OSRTContext *pContext) :
   ASN1MessageBuffer (bufferType, pContext) 
{
   int stat;
   if ((stat = pu_setBuffer 
                 (mpContext->getPtr(), pMsgBuf, msgBufLen, aligned)) != 0)
      LOG_RTERR (mpContext->getPtr(), stat);
}

EXTPERMETHOD int ASN1PERMessageBuffer::setBuffer 
   (const OSOCTET* pMsgBuf, size_t msgBufLen)
{
   if (getStatus () != 0) return getStatus ();

   OSCTXT* pctxt = getCtxtPtr();
   int stat = pu_setBuffer (pctxt, (OSOCTET*)pMsgBuf, msgBufLen, 
                            pctxt->buffer.aligned);
   if (stat != 0) return LOG_RTERR (pctxt, stat);
   return 0;
}

//////////////////////////////////////////
//                                      //
// ASN1PEREncodeBuffer methods          //
//                                      //
//////////////////////////////////////////

// This method returns a copy of the encoded message in a dynamic
// memory buffer.  It is the programmer's responsibility to free 
// this memory when done with the message..

EXTPERMETHOD OSOCTET* ASN1PEREncodeBuffer::getMsgCopy ()
{
   if (getStatus () != 0) return 0;

   int msgLen;
   OSCTXT*  pCtxt = mpContext->getPtr();
   OSOCTET* msg_p = pe_GetMsgPtr (pCtxt, &msgLen);

   if (msg_p) {
      OSOCTET* temp_p = msg_p;
      msg_p = new OSOCTET [msgLen];
      memcpy (msg_p, temp_p, msgLen);
   }

   return (msg_p);
}

// This method returns a pointer to the encoded message.  The encode 
// buffer class retains ownership of the message; therefore, this 
// pointer will become invalid when the encode buffer object instance
// goes out-of-scope..

EXTPERMETHOD const OSOCTET* ASN1PEREncodeBuffer::getMsgPtr ()
{
   if (getStatus () != 0) return 0;
   return pe_GetMsgPtr (mpContext->getPtr(), 0);
}

// This method initializes the encode buffer for encoding
// Frees the memory used by trace information of previous encode
// This function should only keep memory heap / stream & reset all other 
// parameter of context AP 8/19/2003
EXTPERMETHOD int ASN1PEREncodeBuffer::init ()
{
   if (getStatus () != 0) return getStatus ();

   OSCTXT* pCtxt = mpContext->getPtr();
   pCtxt->buffer.byteIndex = 0;
   pCtxt->buffer.bitOffset = 8;
   rtxSListFree (&ACINFO(pCtxt)->fieldList);

   return 0;
}

//////////////////////////////////////////
//                                      //
// ASN1PERDecodeBuffer methods          //
//                                      //
//////////////////////////////////////////

EXTPERMETHOD ASN1PERDecodeBuffer::ASN1PERDecodeBuffer (const char* filePath, 
                                          OSBOOL aligned) :
   ASN1PERMessageBuffer (PERDecode, 0, 0, aligned)
{
   if (getStatus () != 0) return;

   int stat = readBinaryFile (filePath);
   if (stat != 0) mpContext->setStatus (stat);
}

EXTPERMETHOD int ASN1PERDecodeBuffer::readBinaryFile (const char* filePath)
{
   OSOCTET* pMsgBuf;
   OSCTXT* pctxt = getCtxtPtr();
   size_t msgLen = 0;
   int stat = rtxFileReadBinary (pctxt, filePath, &pMsgBuf, &msgLen);

   if (stat == 0) 
      stat = setBuffer (pMsgBuf, msgLen);

   return mpContext->setStatus (stat);
}
