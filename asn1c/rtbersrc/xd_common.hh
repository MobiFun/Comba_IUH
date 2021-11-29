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
/*
// CHANGE LOG
// Date         Init    Description
// 04/24/02     ED      Move XD_ macros to asn1intl.h
//
////////////////////////////////////////////////////////////////////////////
*/

/**
 * @file rtbersrc/xd_common.hh
 */

#ifndef _XD_COMMON_HH_
#define _XD_COMMON_HH_

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rtbersrc/asn1ber.h"
#include "rtsrc/asn1intl.h"
#include "rtsrc/rt_common.hh"

/* This macro will match a single-byte tag (assumes it is primitive only) 
   and advances the decode cursor if it matches. It also clears the 
   ASN1CONSTAG flag bit in the context. */

#define XD_MATCH1(pctxt, tag) \
(((pctxt)->buffer.data[(pctxt)->buffer.byteIndex] == tag) ? \
((pctxt)->flags &= (~ASN1CONSTAG), (pctxt)->buffer.byteIndex++, TRUE) : FALSE)

/* This macro is optimized version of xd_len function */

#define XD_LEN(pctxt,len_p) \
(((pctxt)->buffer.byteIndex < (pctxt)->buffer.size) ? \
(((pctxt)->buffer.data[(pctxt)->buffer.byteIndex] < 0x80) ? \
(*(len_p)=(pctxt)->buffer.data[(pctxt)->buffer.byteIndex++], 0) : \
 xd_len ((pctxt),len_p)) : RTERR_ENDOFBUF)

/* These macros set the constructed tag bit in the context flags based on 
   the parsed value */

#define SET_ASN1CONSTAG(pctxt,tag) \
((pctxt)->flags = (OSRTFLAGS)(((pctxt)->flags & (~ASN1CONSTAG)) \
| ((!(((tag) & TM_CONS) >> (ASN1TAG_LSHIFT - 8 + 5)) - 1) & ASN1CONSTAG)))

#define SET_ASN1CONSTAG_BYTE(pctxt,tag) \
((pctxt)->flags = (OSRTFLAGS)(((pctxt)->flags & (~ASN1CONSTAG)) | \
((!(((tag) & TM_FORM) >> 5) - 1) & ASN1CONSTAG)))

/* This macro is an optimized version of the xd_tag function */

#define XD_TAG(pctxt,tag_p) \
(((pctxt)->buffer.byteIndex < (pctxt)->buffer.size) ? \
((((pctxt)->buffer.data[(pctxt)->buffer.byteIndex] & TM_B_IDCODE) != 31) ? \
(*(tag_p) = (((ASN1TAG)((pctxt)->buffer.data[(pctxt)->buffer.byteIndex] & \
TM_CLASS_FORM) << ASN1TAG_LSHIFT) | \
((pctxt)->buffer.data[(pctxt)->buffer.byteIndex] & TM_B_IDCODE)), \
SET_ASN1CONSTAG((pctxt),*(tag_p)), (pctxt)->buffer.byteIndex++, 0) : \
xd_tag((pctxt), (tag_p))) : RTERR_ENDOFBUF)

#define _GENASN1TAG(t) \
(((ASN1TAG)((t) & TM_CLASS_FORM) << ASN1TAG_LSHIFT) | (t) & TM_B_IDCODE)

/***********************************************************************
 *
 *  DECODE FUNCTIONS
 *
 **********************************************************************/

int xd_MovePastEOC (OSCTXT* pctxt);

int xd_consStrIndefLenAndSize 
(OSCTXT* pctxt, ASN1TAG expectedTag, int* length, int* size);

#endif
