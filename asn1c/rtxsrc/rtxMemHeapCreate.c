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

/* Memory management utility functions, ver. 5.6.0 */

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "rtxsrc/rtxMemHeap.hh"
#include "rtxsrc/rtxErrCodes.h"

EXTRTMETHOD int rtxMemHeapCreate (void** ppvMemHeap) 
{
   OSMemHeap* pMemHeap;
   if (ppvMemHeap == 0) return RTERR_INVPARAM;

   pMemHeap = (OSMemHeap*) _g_malloc_func (ppvMemHeap, sizeof (OSMemHeap));
   if (pMemHeap == NULL) return RTERR_NOMEM;
   OSCRTLMEMSET (pMemHeap, 0, sizeof (OSMemHeap));
   pMemHeap->defBlkSize = rtxMemGetDefBlkSize();
   pMemHeap->refCnt = 1;
   pMemHeap->flags = RT_MH_FREEHEAPDESC;
   *ppvMemHeap = (void*)pMemHeap;
   return 0;
}

