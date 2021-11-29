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
#include "rtsrc/rt_common.hh"

/* Object identifier helper functions */

void rtSetOID (ASN1OBJID* ptarget, ASN1OBJID* psource)
{
   OSUINT32 ui;
   ptarget->numids = psource->numids;
   for (ui = 0; ui < psource->numids && ui < ASN_K_MAXSUBIDS; ui++) {
      ptarget->subid[ui] = psource->subid[ui];
   }
}

/* Adds one OID to another */
void rtAddOID (ASN1OBJID* ptarget, ASN1OBJID* psource)
{
   OSUINT32 ui, ti = ptarget->numids;
   for (ui = 0; ui < psource->numids && ti < ASN_K_MAXSUBIDS; ui++, ti++) {
      ptarget->subid[ti] = psource->subid[ui];
   }
   ptarget->numids = ti;
}

