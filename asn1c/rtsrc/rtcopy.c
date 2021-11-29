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

/* Run-time copy utility functions */

#include <stdarg.h>
#include <stdlib.h>
#include "rtsrc/asn1type.h"
#include "rtsrc/rtCopy.h"

/* copy static bit string to another one. pDstData buffer should have 
enough size for storing all bits (srcNumbits). */
EXTRTMETHOD OSBOOL rtCopyBitStr (OSUINT32 srcNumbits, 
                     const OSOCTET* pSrcData, 
                     OSUINT32* pDstNumbits, OSOCTET* pDstData)
{
   if (pDstNumbits == NULL || pDstData == NULL || pSrcData == NULL) 
      return FALSE;

   *pDstNumbits = srcNumbits;

   if (srcNumbits > 0) {
      memcpy (pDstData, pSrcData, (srcNumbits + 7) / 8);
   }
   else return FALSE;

   return TRUE;
}

/* copy dynamic bit string to another one. pDstData->data will be 
allocated using rtxMemAlloc. */
EXTRTMETHOD OSBOOL rtCopyDynBitStr 
(OSCTXT* pctxt, ASN1DynBitStr* pSrcData, ASN1DynBitStr* pDstData)
{
   if (pSrcData == NULL || pDstData == NULL) return FALSE;
   pDstData->numbits = pSrcData->numbits;
   if (pSrcData->numbits > 0) {
      OSOCTET* _dstData = 
         (OSOCTET*) rtxMemAlloc (pctxt, (pSrcData->numbits + 7) / 8);
      if (_dstData == NULL) return FALSE;
      memcpy (_dstData, pSrcData->data, (pSrcData->numbits + 7) / 8);
      pDstData->data = _dstData;
   }
   else pDstData->data = 0;
   return TRUE;
}

/* copy static octet string to another one. pDstData buffer should have 
enough size for storing all octets (srcNumocts). */
EXTRTMETHOD OSBOOL rtCopyOctStr (OSUINT32 srcNumocts, 
                     const OSOCTET* pSrcData, 
                     OSUINT32* pDstNumocts, OSOCTET* pDstData)
{
   if (pDstNumocts == NULL || pDstData == NULL || pSrcData == NULL) 
      return FALSE;

   *pDstNumocts = srcNumocts;

   if (srcNumocts > 0) {
      memcpy (pDstData, pSrcData, srcNumocts);
   }
   else return FALSE;

   return TRUE;
}

/* copy dynamic octet string to another one. pDstData->data will be 
allocated using rtxMemAlloc. */
EXTRTMETHOD OSBOOL rtCopyDynOctStr 
(OSCTXT* pctxt, ASN1DynOctStr* pSrcData, ASN1DynOctStr* pDstData) 
{
   if (pDstData == NULL || pSrcData == NULL) return FALSE;
   pDstData->numocts = pSrcData->numocts;
   if (pSrcData->numocts > 0) {
      OSOCTET* _dstData = (OSOCTET*) rtxMemAlloc (pctxt, pSrcData->numocts);
      if (_dstData == NULL) return FALSE;
      memcpy (_dstData, pSrcData->data, pSrcData->numocts);
      pDstData->data = _dstData;
   }
   else pDstData->data = 0;
   return TRUE;
}

EXTRTMETHOD OSBOOL rtCopyCharStr (OSCTXT* pctxt, const char* srcStr, char** dstStr) 
{
   size_t len;

   if (srcStr == NULL || dstStr == NULL) return FALSE;
   len = strlen (srcStr);
   *dstStr = (char*) rtxMemAlloc (pctxt, len + 1);
   if (dstStr == NULL) return FALSE;
   strcpy (*dstStr, srcStr);
   return TRUE;
}

EXTRTMETHOD OSBOOL rtCopy16BitCharStr 
(OSCTXT* pctxt, Asn116BitCharString* srcStr, Asn116BitCharString* dstStr) 
{
   if (srcStr == NULL || dstStr == NULL) return FALSE;
   if (srcStr->nchars > 0) {
      dstStr->data = (OSUNICHAR*) rtxMemAlloc (pctxt, 
         srcStr->nchars * sizeof (OSUNICHAR));
      if (dstStr->data == NULL) return FALSE;
      dstStr->nchars = srcStr->nchars;
      memcpy (dstStr->data, srcStr->data, dstStr->nchars * sizeof (OSUNICHAR));
   }
   else {
      dstStr->nchars = 0;
      dstStr->data = NULL;
   }
   return TRUE;
}

EXTRTMETHOD OSBOOL rtCopy32BitCharStr 
(OSCTXT* pctxt, Asn132BitCharString* srcStr, Asn132BitCharString* dstStr) 
{
   if (srcStr == NULL || dstStr == NULL) return FALSE;
   if (srcStr->nchars > 0) {
      dstStr->data = (OS32BITCHAR*) rtxMemAlloc (pctxt, 
         srcStr->nchars * sizeof (OS32BITCHAR));
      if (dstStr->data == NULL) return FALSE;
      dstStr->nchars = srcStr->nchars;
      memcpy (dstStr->data, srcStr->data, 
              dstStr->nchars * sizeof (OS32BITCHAR));
   }
   else {
      dstStr->nchars = 0;
      dstStr->data = NULL;
   }
   return TRUE;
}

EXTRTMETHOD OSBOOL rtCopyOID (ASN1OBJID* srcOID, ASN1OBJID* dstOID)
{
   if (srcOID == NULL || dstOID == NULL) return FALSE;
   if (srcOID->numids > 0) {
      dstOID->numids = srcOID->numids;
      memcpy (dstOID->subid, srcOID->subid, 
              dstOID->numids * sizeof (dstOID->subid[0]));
   }
   else {
      dstOID->numids = 0;
   }
   return TRUE;
}

EXTRTMETHOD OSBOOL rtCopyOID64 (ASN1OID64* srcOID, ASN1OID64* dstOID)
{
   if (srcOID == NULL || dstOID == NULL) return FALSE;
   if (srcOID->numids > 0) {
      dstOID->numids = srcOID->numids;
      memcpy (dstOID->subid, srcOID->subid, 
              dstOID->numids * sizeof (dstOID->subid[0]));
   }
   else {
      dstOID->numids = 0;
   }
   return TRUE;
}

EXTRTMETHOD OSBOOL rtCopyOpenType (OSCTXT* pctxt, ASN1OpenType* srcOT, ASN1OpenType* dstOT)
{
   if (srcOT == NULL || dstOT == NULL) return FALSE;
   dstOT->numocts = srcOT->numocts;
   if (srcOT->numocts > 0) {
      OSOCTET* _dstData = (OSOCTET*) rtxMemAlloc (pctxt, srcOT->numocts);
      if (_dstData == NULL) return FALSE;
      memcpy (_dstData, srcOT->data, srcOT->numocts);
      dstOT->data = _dstData;
   }
   else dstOT->data = NULL;
   return TRUE;
}

EXTRTMETHOD OSBOOL rtCopyOpenTypeExt 
(OSCTXT* pctxt, OSRTDList* srcList, OSRTDList* dstList)
{
   OSRTDListNode* pnode;
   if (srcList == NULL || dstList == NULL) return FALSE;

   pnode = srcList->head;
   rtxDListInit (dstList);

   /* Check all the octets are equal */
   while (0 != pnode) {
      if (0 != pnode->data) {
         ASN1OpenType* pSrcOT = (ASN1OpenType*) pnode->data;
         ASN1OpenType* pDestOT = (ASN1OpenType*) 
            rtxMemAlloc (pctxt, sizeof (ASN1OpenType));
         if (pDestOT == NULL) return FALSE;

         if (!rtCopyOpenType (pctxt, pSrcOT, pDestOT))
            return FALSE;

         rtxDListAppend (pctxt, dstList, pDestOT);
      }
      pnode = pnode->next;
   }
   return TRUE;
}
