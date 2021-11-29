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
 * @file rtxBitDecode.h
 * Bit decode functions.
 */
#ifndef _RTXBITDECODE_H_
#define _RTXBITDECODE_H_

#include "rtxsrc/rtxContext.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  This function decodes up to sizeof(unsigned) bits
 *  and returns the result in an unsigned integer value.
 *
 * @param pctxt       Pointer to a context structure. This provides a storage
 *                       area for the function to store all working variables
 *                       that must be maintained between function calls.
 * @param pvalue      Pointer to value to be receive decoded result.
 * @param nbits       Number of bits to read from decode buffer.
 * @return            Status of the operation.  Zero if successful; a 
 *                       negative status code if failed.
 */
EXTERNRT int rtxDecBits (OSCTXT* pctxt, OSUINT32* pvalue, OSUINT32 nbits);

#ifdef __cplusplus
}
#endif

#endif
