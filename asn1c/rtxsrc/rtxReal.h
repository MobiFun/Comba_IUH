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
/** 
 * @file rtxReal.h 
 * Common runtime functions for working with floating-point numbers.
 */
#ifndef _RTXREAL_H_
#define _RTXREAL_H_

#include "rtxsrc/osSysTypes.h"
#include "rtxsrc/rtxExternDefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup rtxReal Floating-point number utility functions
 * @{
 * Floating-point utility function provide run-time functions for handling 
 * floating-point number types defined within a schema.
 */

/**
 * Returns the IEEE negative infinity value.  This is defined as
 * 0xfff0000000000000 in IEEE standard 754.  We assume the presence of the
 * IEEE double type, that is, 64-bits of precision. */
EXTERNRT OSREAL rtxGetMinusInfinity (void);

/**
 * Returns the IEEE minus zero value.  This is defined as
 * 0x8000000000000000 in IEEE standard 754.  We assume the presence of the
 * IEEE double type, that is, 64-bits of precision. */
EXTERNRT OSREAL rtxGetMinusZero (void);

/**
 * Returns the IEEE Not-A-Number (NaN) value.  This is defined as
 * 0x7ff8000000000000 in IEEE standard 754.  We assume the presence of the
 * IEEE double type, that is, 64-bits of precision. */
EXTERNRT OSREAL rtxGetNaN (void);

/**
 * Returns the IEEE posative infinity value.  This is defined as
 * 0x7ff0000000000000 in IEEE standard 754.  We assume the presence of the
 * IEEE double type, that is, 64-bits of precision. */
EXTERNRT OSREAL rtxGetPlusInfinity (void);

/**
 * A utility function that compares the given input value to the IEEE 754
 * value for negative infinity.
 *
 * @param   value    The input real value. */
EXTERNRT OSBOOL rtxIsMinusInfinity (OSREAL value);

/**
 * A utility function that compares the given input value to the IEEE 754
 * value for minus zero.
 *
 * @param   value    The input real value. */
EXTERNRT OSBOOL rtxIsMinusZero (OSREAL value);

/**
 * A utility function that compares the given input value to the IEEE 754
 * value for Not-A-Number (NaN).
 *
 * @param   value    The input real value. */
EXTERNRT OSBOOL rtxIsNaN (OSREAL value);

/**
 * A utility function that compares the given input value to the IEEE 754
 * value for positive infinity.
 *
 * @param   value    The input real value. */
EXTERNRT OSBOOL rtxIsPlusInfinity (OSREAL value);

/**
 * @} rtxReal
 */

#ifdef __cplusplus
}
#endif

#endif
