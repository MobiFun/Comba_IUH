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

#include "rtbersrc/ASN1BEREncodeStream.h"

////////////////////////////////////////
//
// ASN1BEREncodeStream

ASN1BEREncodeStream::ASN1BEREncodeStream (OSRTOutputStreamIF& os) :
   ASN1MessageBuffer (OSRTMessageBuffer::BEREncode, os.getContext ()),
   mpStream (&os), mbOwnStream (FALSE)
{
   OSRTASSERT (0 != mpStream);
}

ASN1BEREncodeStream::ASN1BEREncodeStream (OSRTOutputStreamIF* pos, OSBOOL bOwnStream) :
   ASN1MessageBuffer (OSRTMessageBuffer::BEREncode, pos->getContext ()),
   mpStream (pos), mbOwnStream (bOwnStream)
{
   OSRTASSERT (0 != mpStream);
}

ASN1BEREncodeStream::~ASN1BEREncodeStream ()
{
   if (mbOwnStream) {
      mpStream->close ();
      delete mpStream;
   }
}

ASN1BEREncodeStream& ASN1BEREncodeStream::operator << (ASN1CType& val) 
{
   if (getStatus () != 0) return *this;

   int stat = val.EncodeTo (*this);
   if (stat != 0) LOG_RTERR (mpContext->getPtr (), stat);
   return *this;
}

int ASN1BEREncodeStream::encodeTag (ASN1TAG tag)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmTag (mpContext->getPtr (), tag);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeIndefLen ()
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmLength (mpContext->getPtr (), ASN_K_INDEFLEN);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeTagAndIndefLen (ASN1TAG tag)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmTagAndIndefLen (mpContext->getPtr (), tag);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeTagAndLen (ASN1TAG tag, OSINT32 len)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmTagAndLen (mpContext->getPtr (), tag, len);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeEoc ()
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmEOC (mpContext->getPtr ());
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeInt (OSINT32 val, ASN1TagType tagging)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmInt (mpContext->getPtr (), val, tagging);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeInt8 (OSINT8 val, ASN1TagType tagging)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmInt8 (mpContext->getPtr (), val, tagging);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeInt16 (OSINT16 val, ASN1TagType tagging)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmInt16 (mpContext->getPtr (), val, tagging);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeInt64 (OSINT64 val, ASN1TagType tagging)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmInt64 (mpContext->getPtr (), val, tagging);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeUInt (OSUINT32 val, ASN1TagType tagging)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmUInt (mpContext->getPtr (), val, tagging);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeUInt8 (OSUINT8 val, ASN1TagType tagging)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmUInt8 (mpContext->getPtr (), val, tagging);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeUInt16 (OSUINT16 val, ASN1TagType tagging)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmUInt16 (mpContext->getPtr (), val, tagging);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeUInt64 (OSUINT64 val, ASN1TagType tagging)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmUInt64 (mpContext->getPtr (), val, tagging);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeBigInt (const char *pval, ASN1TagType tagging)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmBigInt (mpContext->getPtr (), pval, tagging);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeEnum (OSINT32 val, ASN1TagType tagging)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmEnum (mpContext->getPtr (), val, tagging);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeBool (OSBOOL val, ASN1TagType tagging)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmBool (mpContext->getPtr (), val, tagging);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeReal (OSREAL val, ASN1TagType tagging)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmReal (mpContext->getPtr (), val, tagging);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeBitStr (const OSOCTET* pbits, OSUINT32 numbits, 
   ASN1TagType tagging)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmBitStr (mpContext->getPtr (), pbits, numbits, tagging);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeBitStr (const ASN1DynBitStr& val, ASN1TagType tagging)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmBitStr (mpContext->getPtr (), val.data, val.numbits, tagging);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeOctStr (const OSOCTET* pocts, OSUINT32 numocts, 
   ASN1TagType tagging)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmOctStr (mpContext->getPtr (), pocts, numocts, tagging);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeOctStr (const ASN1DynOctStr& val, ASN1TagType tagging)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmOctStr (mpContext->getPtr (), val.data, val.numocts, tagging);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeCharStr (const char* pval, ASN1TagType tagging, ASN1TAG tag)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmCharStr (mpContext->getPtr (), pval, tagging, tag);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeObjId (const ASN1OBJID& val, ASN1TagType tagging)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmObjId (mpContext->getPtr (), &val, tagging);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeObjId64 (const ASN1OID64& val, ASN1TagType tagging)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmObjId64 (mpContext->getPtr (), &val, tagging);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeRelativeOID (const ASN1OBJID& val, ASN1TagType tagging)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmRelativeOID (mpContext->getPtr (), &val, tagging);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeNull (ASN1TagType tagging)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmNull (mpContext->getPtr (), tagging);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeBMPStr (const Asn116BitCharString& val, ASN1TagType tagging)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmBMPStr (mpContext->getPtr (), &val, tagging);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeUnivStr (const Asn132BitCharString& val, ASN1TagType tagging)
{
   if (getStatus () != 0) return getStatus ();

   int stat = berEncStrmUnivStr (mpContext->getPtr (), &val, tagging);
   if (stat != 0) return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

int ASN1BEREncodeStream::encodeObj (ASN1CType& val)
{
   if (getStatus () != 0) return getStatus ();

   int stat = val.EncodeTo (*this);
   if (stat != 0) 
      return LOG_RTERR (mpContext->getPtr (), stat);
   return 0;
}

OSBOOL ASN1BEREncodeStream::isA (int bufferType)
{
   return (bufferType == BEREncode || bufferType == Stream);
}

