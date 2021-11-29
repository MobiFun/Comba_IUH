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
 * @file rtxCharStr.h
 */
/**
 * @defgroup rtxCharStr Character string functions
 * @{
 * These functions are more secure versions of several of the character 
 * string functions available in the standard C run-time library.
 */
#ifndef _RTXCHARSTR_H_
#define _RTXCHARSTR_H_

#include "rtxsrc/rtxContext.h"

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * This function concatanates the given string onto the string buffer.
 * It is similar to the C \c strcat function except more secure because 
 * it checks for buffer overrun.
 *
 * @param dest         Pointer to destination buffer to receive string.
 * @param bufsiz       Size of the destination buffer.
 * @param src          Pointer to null-terminated string to copy.
 * @return             Pointer to destination buffer or NULL if copy failed.
 */
EXTERNRT char* rtxStrcat (char* dest, size_t bufsiz, const char* src);

/** 
 * This function concatanates the given number of characters from the 
 * given string onto the string buffer.  It is similar to the C \c strncat 
 * function except more secure because it checks for buffer overrun.
 *
 * @param dest         Pointer to destination buffer to receive string.
 * @param bufsiz       Size of the destination buffer.
 * @param src          Pointer to null-terminated string to copy.
 * @param nchars       Number of characters to copy.
 * @return             Pointer to destination buffer or NULL if copy failed.
 */
EXTERNRT char* rtxStrncat 
(char* dest, size_t bufsiz, const char* src, size_t nchars);

/** 
 * This function copies a null-terminated string to a target buffer. 
 * It is similar to the C \c strcpy function except more secure because 
 * it checks for buffer overrun.
 *
 * @param dest         Pointer to destination buffer to receive string.
 * @param bufsiz       Size of the destination buffer.
 * @param src          Pointer to null-terminated string to copy.
 * @return             Pointer to destination buffer or NULL if copy failed.
 */
EXTERNRT char* rtxStrcpy (char* dest, size_t bufsiz, const char* src);

/** 
 * This function copies the given number of characters from a string to 
 * a target buffer. It is similar to the C \c strncpy function except more 
 * secure because it checks for buffer overrun and ensures a null-terminator 
 * is copied to the end of the target buffer
 *
 * @param dest         Pointer to destination buffer to receive string.
 * @param bufsiz       Size of the destination buffer.
 * @param src          Pointer to null-terminated string to copy.
 * @param nchars       Number of characters to copy.
 * @return             Pointer to destination buffer or NULL if copy failed.
 */
EXTERNRT char* rtxStrncpy 
(char* dest, size_t bufsiz, const char* src, size_t nchars);

/** 
 * This function converts a signed 32-bit integer into a character
 * string.  It is similar to the C \c itoa function.
 *
 * @param value        Integer to convert.
 * @param dest         Pointer to destination buffer to receive string.
 * @param bufsiz       Size of the destination buffer.
 * @param padchar      Left pad char, set to zero for no padding.
 * @return             Number of characters or negative status value if fail.
 */
EXTERNRT int rtxIntToCharStr
(OSINT32 value, char* dest, size_t bufsiz, char padchar);

/** 
 * This function converts an unsigned 32-bit integer into a character
 * string.  It is similar to the C \c itoa function.
 *
 * @param value        Integer to convert.
 * @param dest         Pointer to destination buffer to receive string.
 * @param bufsiz       Size of the destination buffer.
 * @param padchar      Left pad char, set to zero for no padding.
 * @return             Number of characters or negative status value if fail.
 */
EXTERNRT int rtxUIntToCharStr
(OSUINT32 value, char* dest, size_t bufsiz, char padchar);

#if !defined(_NO_INT64_SUPPORT)
/** 
 * This function converts a signed 64-bit integer into a character
 * string.  It is similar to the C \c itoa function.
 *
 * @param value        Integer to convert.
 * @param dest         Pointer to destination buffer to receive string.
 * @param bufsiz       Size of the destination buffer.
 * @param padchar      Left pad char, set to zero for no padding.
 * @return             Number of characters or negative status value if fail.
 */
EXTERNRT int rtxInt64ToCharStr
(OSINT64 value, char* dest, size_t bufsiz, char padchar);

/** 
 * This function converts an unsigned 64-bit integer into a character
 * string.  It is similar to the C \c itoa function.
 *
 * @param value        Integer to convert.
 * @param dest         Pointer to destination buffer to receive string.
 * @param bufsiz       Size of the destination buffer.
 * @param padchar      Left pad char, set to zero for no padding.
 * @return             Number of characters or negative status value if fail.
 */
EXTERNRT int rtxUInt64ToCharStr
(OSUINT64 value, char* dest, size_t bufsiz, char padchar);

#endif /* !defined(_NO_INT64_SUPPORT) */

/** 
 * This function returns a count of the number of bytes the would result 
 * from the conversion of a hexadecimal character string to binary.  Any 
 * whitespace characters in the string are ignored.
 *
 * @param hexstr       Hex character string to convert.
 * @param nchars       Number of characters in string.  If zero, 
 *                      characters are read up to null-terminator.
 * @return             Number of bytes or negative status value if fail.
 */
EXTERNRT int rtxHexCharsToBinCount (const char* hexstr, size_t nchars);

/** 
 * This function converts the given hex string to binary.  The result is 
 * stored in the given binary buffer. Any whitespace characters in the 
 * string are ignored.
 *
 * @param hexstr       Hex character string to convert.
 * @param nchars       Number of characters in string.  If zero, 
 *                      characters are read up to null-terminator.
 * @param binbuf       Buffer to hold converted binary data.
 * @param bufsize      Size of the binary data buffer.
 * @return             Number of bytes or negative status value if fail.
 */
EXTERNRT int rtxHexCharsToBin 
(const char* hexstr, size_t nchars, OSOCTET* binbuf, size_t bufsize);

/**
 * @} rtxCharStr
 */
#ifdef __cplusplus
}
#endif

#endif
