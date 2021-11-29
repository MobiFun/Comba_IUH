/*
 * Copyright (c) 2008 Objective Systems, Inc.
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
/** 
 * @file rtxBitEncode.h
 * Bit encode functions.
 */
#ifndef _RTXBITENCODE_H_
#define _RTXBITENCODE_H_

#include "rtxsrc/rtxContext.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This function will set the bit at the current encode bit cursor 
 * position to 1 or 0 and advance the cursor pointer.
 *
 * @param pctxt       Pointer to a context structure. This provides a storage
 *                       area for the function to store all working variables
 *                       that must be maintained between function calls.
 * @param value        The value to be encoded.
 */
EXTERNRT int rtxEncBit (OSCTXT* pctxt, OSBOOL value);

/**
 * This function will encode a series of bits (up to 32) from an unsigned
 * integer value/
 *
 * @param pctxt       Pointer to a context structure. This provides a storage
 *                       area for the function to store all working variables
 *                       that must be maintained between function calls.
 * @param value       The value to be encoded.
 * @param nbits       Number of bits from the value to encode.
 * @return            Status of the operation.  Zero if successful; a 
 *                       negative status code if failed.
 */
EXTERNRT int rtxEncBits (OSCTXT* pctxt, OSUINT32 value, OSUINT32 nbits);

/**
 * This macro will byte-align the encode buffer in the context.
 */
#define rtxByteAlign(pctxt) \
if ((pctxt)->buffer.bitOffset != 8) { \
(pctxt)->buffer.byteIndex++; (pctxt)->buffer.bitOffset = 8; }

#ifdef __cplusplus
}
#endif

#endif
