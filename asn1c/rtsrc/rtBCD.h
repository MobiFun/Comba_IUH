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
/** 
 * @file rtBCD.h 
 * Binary-decimal conversion functions.
 */
#ifndef _RTBCD_H_
#define _RTBCD_H_

#include "rtsrc/asn1type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup bcdHelper Binary Coded Decimal (BCD) Helper Functions 
 * @{
 *
 * Binary Coded Decimal (BCD) helper functions provide assistance in working
 * with BCD numbers. Functions are provided to convert to a BCD values to 
 * and from string form.
 */
/**
 * This function converts a packed BCD value to a standard null-terminated 
 * string. Octet values may contain filler digits if the number of BCD digits is
 * odd.
 *
 * BCD digits can be 0(0000) to 9(1001).
 * Filler digits can be A(1010), B(1011), C(1100), D(1101), E(1110) or F(1111)
 *
 * @param numocts      The number of octets in the BCD value.
 * @param data         The pointer to the BCD value.
 * @param buffer       The destination buffer. Should not be less than buffsiz
 *                       argument is.
 * @param bufsiz       The size of the destination buffer (in octets). The 
 *                       buffer size should be atleast ((numocts * 2) + 1) to
 *                       hold the BCD to String conversion.
 * @param isTBCD       Whether the input data is formatted as a TBCD string
 *                       or not.
 * @return             The converted null-terminated string. NULL, if error has
 *                       occurred or destination buffer is not enough.
 * @see rtTBCDToString
 */
EXTERNRT const char* rtBCDToString 
   (OSUINT32 numocts, const OSOCTET* data, char* buffer, size_t bufsiz,
    OSBOOL isTBCD);

/** 
 * This function converts a standard null-terminated string into a BCD value.
 * The source string should contain only characters '0' - '9', 'A' - 'F', or
 * 'a' - 'f'. Otherwise, an error will occur.
 *
 * @param str          The source standard null-terminated string.
 * @param bcdStr       The destination buffer. Should not be less than bufsiz
 *                       is.
 * @param bufsiz       The size of the destination buffer (in octets).
 * @param isTBCD       Whether the string is a TBCD string or not.
 * @return             The number of octets in the resulting BCD value or 
 *                       a negative value if an error occurs.
 * @see rtStringToTBCD
 */
EXTERNRT int rtStringToBCD 
   (const char* str, OSOCTET* bcdStr, size_t bufsiz, OSBOOL isTBCD);

/** 
 * This function converts a standard null-terminated string into a BCD value.
 * The source string should contain only characters '0' - '9', 'A' - 'F', or
 * 'a' - 'f'. Otherwise, an error will occur.
 *
 * @param str          The source standard null-terminated string.
 * @param pctxt        Pointer to a context structure block.
 * @param poctstr      Pointer to a dynamic octet string variable.  Memory 
 *                       will be allocated for the data member of this 
 *                       structure with rtMemAlloc.
 * @return             The number of octets in the resulting BCD value or
 *                       a negative value if an error occurs.
 */
EXTERNRT int rtStringToDynBCD 
   (OSCTXT* pctxt, const char* str, ASN1DynOctStr* poctstr);

/**
 * This function converts a packed TBCD value to a standard null-terminated 
 * string. Octet value can contain the filler digit to represent the odd
 * number of BCD digits.  A TBCD string differs from a normal BCD string
 * in that the byte values of the octets are flipped.  The BCD string
 * 0x12345f would be represented 0x2143f5 as a TBCD string.
 *
 * TBCD digits can be 0(0000) to 9(1001).
 * Filler digits can be A(1010), B(1011), C(1100), D(1101), E(1110) or F(1111)
 *
 * @param numocts      The number of octets in the BCD value.
 * @param data         The pointer to the BCD value.
 * @param buffer       The destination buffer. Should not be less than buffsiz
 *                       argument is.
 * @param bufsiz       The size of the destination buffer (in octets). The 
 *                       buffer size should be atleast ((numocts * 2) + 1) to
 *                       hold the BCD to String conversion.
 * @return             The converted null-terminated string. NULL, if error has
 *                       occurred or destination buffer is not enough.
 * @since 6.06
 */
EXTERNRT const char* rtTBCDToString 
   (OSUINT32 numocts, const OSOCTET* data, char* buffer, size_t bufsiz);

/** 
 * This function converts a standard null-terminated string into a TBCD value.
 * The source string should contain only characters '0' - '9', 'A' - 'F', or
 * 'a' - 'f'. Otherwise, an error will occur.  A TBCD string differs from a
 * normal BCD string in that its bytes are flipped.  The BCD string
 * 0x12345f would be represented 0x2143f5 as a TBCD string.
 *
 * @param str          The source standard null-terminated string.
 * @param bcdStr       The destination buffer. Should not be less than bufsiz
 *                       is.
 * @param bufsiz       The size of the destination buffer (in octets).
 * @return             The number of octets in the resulting BCD value or 
 *                       a negative value if an error occurs.
 * @since 6.06
 */
EXTERNRT int rtStringToTBCD 
   (const char* str, OSOCTET* bcdStr, size_t bufsiz);

/**
 * @} bcdHelper
 */

#ifdef __cplusplus
}
#endif

#endif
