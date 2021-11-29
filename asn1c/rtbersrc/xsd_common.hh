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
// 01/27/03     AB      initial issue
//
////////////////////////////////////////////////////////////////////////////
*/

/**
 * @file xsd_common.hh
 */

#ifndef _XSD_COMMON_HH_
#define _XSD_COMMON_HH_

#include "rtbersrc/asn1berStream.h"
#include "rtbersrc/xd_common.hh"
#include "rtsrc/asn1intl.h"
#include "rtxsrc/rtxStreamDirectBuf.hh"

/* Read byte from stream */
/*
#define BS_READBYTE(pctxt) (\
((pctxt)->buffer.byteIndex < (pctxt)->buffer.size) ? \
((pctxt)->buffer.data[(pctxt)->buffer.byteIndex++]) : \
((rtxStreamDirectBufPreRead (pctxt, 1) >= 0) ? \
((pctxt)->buffer.data[(pctxt)->buffer.byteIndex++]) : RTERR_READERR))
*/

#endif
