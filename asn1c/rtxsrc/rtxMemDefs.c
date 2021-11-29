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
#include "rtxsrc/rtxMemHeap.hh"

/* For ARM thumb compiler or Symbian, these are defined using #define's
   in rtxMemHeap.hh */
#if !defined(_ARMTCC) && !defined(__SYMBIAN32__) 
OSMallocFunc  g_malloc_func = malloc;
#ifndef _NO_REALLOC
OSReallocFunc g_realloc_func = realloc;
#else
OSReallocFunc g_realloc_func = 0;
#endif
OSFreeFunc    g_free_func = free;

#ifdef _RT_ALLOC_FUNC_WITH_CONTEXT

OSMallocCtxtFunc  g_malloc_ctxt_func = 0;
OSReallocCtxtFunc g_realloc_ctxt_func = 0;
OSFreeCtxtFunc    g_free_ctxt_func = 0;

#endif
#endif
