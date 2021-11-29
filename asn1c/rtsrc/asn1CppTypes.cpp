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

#include "rtsrc/asn1CppTypes.h"
#include "rtsrc/rt_common.hh"

// ASN1Context methods

EXTRTMETHOD ASN1Context::ASN1Context () : OSRTContext()
{
   /* Add ASN.1 error codes to global table */
   rtErrASN1Init ();
   if (mbInitialized) {
      /* Init ASN.1 info block */
      mStatus = rtCtxtInitASN1Info (&mCtxt);
   }
   mbInitialized = (OSBOOL)(mStatus == 0);
   RTDIAG2 (&mCtxt, "context %x created, ref count = 0\n", &mCtxt);
}

EXTRTMETHOD int ASN1Context::setRunTimeKey (const OSOCTET* key, size_t keylen)
{
   int stat = OSRTContext::setRunTimeKey (key, keylen);
   return (0 != stat) ? stat : rtBaseCheckLicense (&mCtxt, LIC_CPP);
}

// ASN1CType

EXTRTMETHOD ASN1CType::ASN1CType () : mpContext (new ASN1Context()), mpMsgBuf (0) 
{
}

EXTRTMETHOD ASN1CType::ASN1CType (OSRTContext& ctxt) : mpContext (&ctxt), mpMsgBuf (0) 
{
}

EXTRTMETHOD ASN1CType::ASN1CType (OSRTMessageBufferIF& msgBuf) :  
   mpContext (msgBuf.getContext()), mpMsgBuf(&msgBuf)
{
}

EXTRTMETHOD ASN1CType::ASN1CType (const ASN1CType& orig) : 
   mpContext (orig.mpContext), mpMsgBuf (orig.mpMsgBuf) 
{
}

EXTRTMETHOD int ASN1CType::Decode ()
{ 
   if (mpContext.isNull ()) return RTERR_NOTINIT;

   int stat = getStatus ();
   if (stat != 0) return stat;

   stat = rtBaseCheckLicense (getCtxtPtr(), LIC_CPP);
   if (stat == 0) {
      stat = DecodeFrom (*mpMsgBuf);
      if (stat < 0)
         return LOG_RTERR (getCtxtPtr(), stat);
   } // do not log the location of license checking.
   return stat; 
}

EXTRTMETHOD int ASN1CType::Encode ()
{ 
   if (mpContext.isNull ()) return RTERR_NOTINIT;

   int stat = getStatus ();
   if (stat != 0) return stat;

   stat = rtBaseCheckLicense (getCtxtPtr(), LIC_CPP);
   if (stat == 0) {
      stat = EncodeTo (*mpMsgBuf);
      if (stat < 0)
         return LOG_RTERR (getCtxtPtr(), stat);
   } // do not log the location of license checking.
   return stat; 
}

EXTRTMETHOD int ASN1CType::setMsgBuf (OSRTMessageBufferIF& msgBuf, OSBOOL initBuf) 
{
   if (mpContext.isNull ()) return RTERR_NOTINIT;
   if (getStatus() != 0) return getStatus ();

   mpMsgBuf = &msgBuf;
   OSCTXT* pctxt = mpContext->getPtr();

   // This is causing a crash in employee-socketstream.  It is causing 
   // the memHeap of pctxt to be released which holds the data to be 
   // encoded (ED, 6/25/06)
   // rtxCtxtSetMemHeap (pctxt, msgBuf.getCtxtPtr());

   if (pctxt->key != 0 && msgBuf.getCtxtPtr()->key == 0) {
      msgBuf.getCtxtPtr()->key = pctxt->key;
      msgBuf.getCtxtPtr()->keylen = pctxt->keylen;
   }

   if (initBuf && getStatus() == 0) {
      int stat = msgBuf.init();
      mpContext->setStatus (stat);
   }

   return getStatus();
}

EXTRTMETHOD int ASN1CType::setRunTimeKey (const OSOCTET* key, size_t keylen)
{
   if (mpContext.isNull ()) return RTERR_NOTINIT;
   return mpContext->setStatus (mpContext->setRunTimeKey (key, keylen));
}

// ASN1MessageBuffer methods

EXTRTMETHOD ASN1MessageBuffer::ASN1MessageBuffer (Type bufferType) : 
   OSRTMessageBuffer (bufferType, new ASN1Context)
{
}

EXTRTMETHOD ASN1MessageBuffer::ASN1MessageBuffer (Type bufferType, OSRTContext* pContext) :
   OSRTMessageBuffer (bufferType, pContext)
{
}

EXTRTMETHOD int ASN1MessageBuffer::initBuffer (OSRTMEMBUF& membuf)
{
   int len;
   OSOCTET* data = rtxMemBufGetData (&membuf, &len);
   return rtxInitContextBuffer (getCtxtPtr(), data, len);
}

EXTRTMETHOD int ASN1MessageBuffer::initBuffer (OSUNICHAR* unistr)
{
   // Currently only supported for XER decode
   return setStatus (RTERR_NOTSUPP);
}

EXTRTMETHOD int ASN1MessageBuffer::setRunTimeKey (const OSOCTET* key, size_t keylen)
{
   if (mpContext.isNull ()) return RTERR_NOTINIT;
   return mpContext->setStatus (mpContext->setRunTimeKey (key, keylen));
}

#ifndef __SYMBIAN32__
ASN1BMPString* ASN1MessageBuffer::CStringToBMPString 
(const char* cstring, ASN1BMPString* pBMPString, 
 Asn116BitCharSet* pCharSet)
{
   return rtCToBMPString (getCtxtPtr(), cstring, pBMPString, pCharSet);
}
#endif

// 64-bit object identifier class methods

EXTRTMETHOD ASN1TObjId64::ASN1TObjId64 (OSOCTET _numids, const OSINT64* _subids) {
   numids = _numids;
   for (OSUINT32 ui = 0; ui < numids; ui++) {
      subid[ui] = _subids[ui];
   }
}

EXTRTMETHOD ASN1TObjId64::ASN1TObjId64 (const ASN1OID64& oid) {
   numids = oid.numids;
   for (OSUINT32 ui = 0; ui < numids; ui++) {
      subid[ui] = oid.subid[ui];
   }
}

EXTRTMETHOD ASN1TObjId64::ASN1TObjId64 (const ASN1TObjId64& oid) {
   numids = oid.numids;
   for (OSUINT32 ui = 0; ui < numids; ui++) {
      subid[ui] = oid.subid[ui];
   }
}

  void ASN1TObjId64::operator= (const ASN1OID64& rhs) {
   numids = rhs.numids;
   for (OSUINT32 ui = 0; ui < numids; ui++) {
      subid[ui] = rhs.subid[ui];
   }
}

void ASN1TObjId64::operator= (const ASN1TObjId64& rhs) {
   numids = rhs.numids;
   for (OSUINT32 ui = 0; ui < numids; ui++) {
      subid[ui] = rhs.subid[ui];
   }
}
