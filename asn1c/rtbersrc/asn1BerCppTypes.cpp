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
// 04/19/02     ED      Throw exceptions in ctors
// 07/14/02     ED      Lowercase method names
//
////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <string.h>
#include "rtbersrc/asn1BerCppTypes.h"
#include "rtsrc/asn1intl.h"
#include "rtsrc/rt_common.hh"

//////////////////////////////////////////
//                                      //
// ASN1BEREncodeBuffer methods          //
//                                      //
//////////////////////////////////////////

ASN1BEREncodeBuffer::ASN1BEREncodeBuffer () : ASN1BERMessageBuffer(BEREncode)
{ 
   int stat;
   if ((stat = xe_setp (mpContext->getPtr(), 0, 0)) != 0) {
      LOG_RTERR (mpContext->getPtr(), stat);
      setStatus (stat);
   }
}

ASN1BEREncodeBuffer::ASN1BEREncodeBuffer (OSOCTET* pMsgBuf, size_t msgBufLen) :
   ASN1BERMessageBuffer (BEREncode) 
{
   int stat;
   if ((stat = xe_setp 
        (mpContext->getPtr(), pMsgBuf, (int)msgBufLen)) != 0)
   {
      LOG_RTERR (mpContext->getPtr(), stat);
      setStatus (stat);
   }
}

ASN1BEREncodeBuffer::ASN1BEREncodeBuffer (OSOCTET* pMsgBuf, size_t msgBufLen,
      OSRTContext *pContext) :
   ASN1BERMessageBuffer (BEREncode, pContext) 
{
   int stat;
   if ((stat = xe_setp 
        (mpContext->getPtr(), pMsgBuf, (int)msgBufLen)) != 0)
   {
      LOG_RTERR (mpContext->getPtr(), stat);
      setStatus (stat);
   }
}
// This method returns a copy of the encoded message in a dynamic
// memory buffer.  It is the programmer's responsibility to free 
// this memory when done with the message..

OSOCTET* ASN1BEREncodeBuffer::getMsgCopy ()
{
   if (getStatus () != 0) return 0;

   OSCTXT* pCtxt = getCtxtPtr();
   OSOCTET* msg_p = xe_getp (pCtxt);
   size_t msgLen = pCtxt->buffer.size - pCtxt->buffer.byteIndex;

   if (msg_p) {
      OSOCTET* temp_p = msg_p;
      msg_p = new OSOCTET [msgLen];
      memcpy (msg_p, temp_p, msgLen);
   }

   int stat;
   if ((stat = rtBerCheckLicense (pCtxt, LIC_CPP)) != 0) {
      mpContext->setStatus (stat);
      delete [] msg_p;
      msg_p = 0;
   }
   return (msg_p);
}

// This method returns a pointer to the encoded message.  The encode 
// buffer class retains ownership of the message; therefore, this 
// pointer will become invalid when the encode buffer object instance
// goes out-of-scope..

const OSOCTET* ASN1BEREncodeBuffer::getMsgPtr ()
{
   return xe_getp (getCtxtPtr());
}

// This method moves the encode buffer cursor to the end of the 
// buffer to allow a new message to be encoded..

int ASN1BEREncodeBuffer::init ()
{
   if (getStatus () != 0) return getStatus ();

   OSCTXT* pCtxt = getCtxtPtr();
   int stat;

   if ((stat = rtBerCheckLicense (pCtxt, LIC_CPP)) != 0)
      return mpContext->setStatus (stat); // do not log license checking loc

   pCtxt->buffer.byteIndex = pCtxt->buffer.size - 1;
   return 0;
}

int ASN1BEREncodeBuffer::setBuffer (OSOCTET* pMsgBuf, size_t msgBufLen)
{
   if (getStatus () != 0) return getStatus ();

   OSCTXT* pctxt = getCtxtPtr();
   int stat = xe_setp (pctxt, pMsgBuf, (int)msgBufLen);
   if (stat != 0) return LOG_RTERR (pctxt, stat);
   return 0;
}

ASN1BEREncodeBuffer& ASN1BEREncodeBuffer::operator << (ASN1CType& val) 
{
   OSCTXT* pCtxt = getCtxtPtr();
   int stat;

   if (getStatus () != 0) {
      return *this; // do nothing, if error is set
   }

   if ((stat = rtBerCheckLicense (pCtxt, LIC_CPP)) != 0) {
      mpContext->setStatus (stat);
   }
   else {
      stat = val.EncodeTo (*this);
      if (stat != 0) LOG_RTERR (pCtxt, stat);
   }
   return *this;
}

//////////////////////////////////////////
//                                      //
// ASN1BERDecodeBuffer methods          //
//                                      //
//////////////////////////////////////////

ASN1BERDecodeBuffer::ASN1BERDecodeBuffer (const OSOCTET* pMsgBuf, 
                                          size_t msgBufLen) :
   ASN1BERMessageBuffer(BERDecode), mpMsgBuf(pMsgBuf), mMsgBufLen(msgBufLen), 
   mBufSetFlag (FALSE)
{
}

ASN1BERDecodeBuffer::ASN1BERDecodeBuffer () :
   ASN1BERMessageBuffer(BERDecode), mpMsgBuf(0), mMsgBufLen(0), 
   mBufSetFlag (FALSE)
{
}

int ASN1BERDecodeBuffer::init () { 
   int stat = setBuffer (mpMsgBuf, mMsgBufLen); 
   mBufSetFlag = FALSE; // necessary to allow reset buffer by call to 
                        // setBuffer with the same address and length.
                        // (AB, 05/13/2004).
   return stat;
}

OSOCTET* ASN1BERDecodeBuffer::findElement (ASN1TAG tag, 
                                           OSINT32& elemLen, 
                                           OSBOOL firstFlag)
{
   OSOCTET lflgs = XM_SEEK;
   OSCTXT* pCtxt = getCtxtPtr();
   int     stat;

   if (getStatus () != 0) return 0;

   // If first time called, set the decode buffer pointer; otherwise,
   // modify the match flags to skip the current element

   if (firstFlag) {
      mBufSetFlag = TRUE;
      stat = xd_setp (pCtxt, mpMsgBuf, (int)mMsgBufLen, 0, 0);
      if (stat != 0) return ((OSOCTET*) 0);
   }
   else
      lflgs |= XM_SKIP;

   stat = xd_match (pCtxt, tag, &elemLen, lflgs);
   mpContext->setStatus (stat);

   return (stat == 0) ? OSRTBUFPTR(pCtxt) : ((OSOCTET*) 0);
}

int ASN1BERDecodeBuffer::readBinaryFile (const char* filePath)
{
   if (getStatus () != 0) return getStatus ();

   OSOCTET* pMsgBuf;
   OSCTXT* pctxt = getCtxtPtr();
   size_t msgLen = 0;
   int stat = rtxFileReadBinary (pctxt, filePath, &pMsgBuf, &msgLen);

   if (stat == 0) 
      stat = setBuffer (pMsgBuf, msgLen);

   return mpContext->setStatus (stat);
}

int ASN1BERDecodeBuffer::setBuffer (const OSOCTET* pMsgBuf, size_t msgBufLen)
{
   if (getStatus () != 0) return getStatus ();

   OSCTXT* pctxt = getCtxtPtr();

   if (mpMsgBuf == pMsgBuf && mMsgBufLen == msgBufLen && mBufSetFlag)
      return 0;

   mpMsgBuf = pMsgBuf;
   mMsgBufLen = msgBufLen;

   mBufSetFlag = TRUE;
   return xd_setp (pctxt, mpMsgBuf, (int)mMsgBufLen, 0, 0);
}

ASN1BERDecodeBuffer& ASN1BERDecodeBuffer::operator >> (ASN1CType& val) 
{
   OSCTXT* pCtxt = getCtxtPtr();
   int stat;

   mpContext->setStatus (0);
   if ((stat = rtBerCheckLicense (pCtxt, LIC_CPP)) != 0)
      mpContext->setStatus (stat);
   else {
      stat = val.DecodeFrom (*this);
      if (stat != 0) LOG_RTERR (pCtxt, stat);
   }
   return *this;
}
