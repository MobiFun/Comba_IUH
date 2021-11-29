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

/* Run-time utility functions */

#include <stdarg.h>
#include <stdlib.h>
#include "rt_common.hh"

#ifdef __SYMBIAN32__
#include "asn1compat.h"
#define ASN_E_OUTOFBND RTERR_OUTOFBND
#endif

/* Object identifier helper functions */

EXTRTMETHOD void rtSetOID (ASN1OBJID* ptarget, ASN1OBJID* psource)
{
   ASN1UINT ui;
   ptarget->numids = psource->numids;
   for (ui = 0; ui < psource->numids && ui < ASN_K_MAXSUBIDS; ui++) {
      ptarget->subid[ui] = psource->subid[ui];
   }
}

/* Adds one OID to another */
EXTRTMETHOD void rtAddOID (ASN1OBJID* ptarget, ASN1OBJID* psource)
{
   ASN1UINT ui, ti = ptarget->numids;
   for (ui = 0; ui < psource->numids && ti < ASN_K_MAXSUBIDS; ui++, ti++) {
      ptarget->subid[ti] = psource->subid[ui];
   }
   ptarget->numids = ti;
}

/* Sets bit in bit string */
int rtSetBit (ASN1OCTET* pBits, int numbits, int bitIndex) 
{
   ASN1OCTET prev, mask = 0x80, *pbyte;

   if (bitIndex >= numbits)
      return ASN_E_OUTOFBND;
   pbyte = pBits + bitIndex / 8;
   mask >>= bitIndex % 8;
   prev = *pbyte;
   *pbyte = prev | mask;
   return prev & mask;
}

/* Clears bit in bit string */
int rtClearBit (ASN1OCTET* pBits, int numbits, int bitIndex) 
{
   ASN1OCTET prev, mask = 0x80, *pbyte;

   if (bitIndex >= numbits)
      return ASN_E_OUTOFBND;
   pbyte = pBits + bitIndex / 8;
   mask >>= bitIndex % 8;
   prev = *pbyte;
   *pbyte = prev & (~mask);
   return prev & mask;
}

/* Tests bit in bit string */
ASN1BOOL rtTestBit (ASN1ConstOctetPtr pBits, int numbits, int bitIndex) 
{
   return (bitIndex >= numbits) ? FALSE :
      (ASN1BOOL)(pBits [bitIndex / 8] & (0x80 >> bitIndex % 8));
}

