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

#include <stdarg.h>
#include <stdlib.h>

#include "rtsrc/asn1ErrCodes.h"
#include "rtsrc/rtContext.h"
#include "rtxsrc/rtxError.h"

#if !defined(_COMPACT) && !defined(__SYMBIAN32__)

/* Error status text */
static const char* g_status_text[] = {
    "Invalid object identifier",
    "Invalid field length detected",
    "Invalid tag value", 
    "Invalid binary string value", 
    "Invalid index for table constraint identifier",
    "Invalid value for relational table constraint fixed type field", 
    "List error: concurrent modification attempt while iterating", 
    "List error: illegal state for attempted operation", 
    "Attempt to invoke encode or decode method on a non-PDU type", 
    "Element type could not be resolved"
} ;

void rtErrASN1Init ()
{
   rtxErrAddErrorTableEntry (g_status_text, ASN_E_BASE, (ASN_E_BASE-99));
}
#else
void rtErrASN1Init () {}
#endif
