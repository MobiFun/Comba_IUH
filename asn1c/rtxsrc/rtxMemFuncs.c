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

/* Memory management utility functions */

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "rtxsrc/rtxMemHeap.hh"

#if !defined(_ARMTCC) && !defined(__SYMBIAN32__)
static OSUINT32 g_defBlkSize = OSRTXM_K_MEMBLKSIZ;

EXTRTMETHOD void rtxMemSetDefBlkSize (OSUINT32 blkSize) 
{
   g_defBlkSize = blkSize;
}
#else
#define g_defBlkSize 1024
#endif

EXTRTMETHOD OSUINT32 rtxMemGetDefBlkSize () 
{
   return g_defBlkSize;
}

#ifndef __SYMBIAN32__ 
EXTRTMETHOD void rtxMemSetAllocFuncs
(OSMallocFunc malloc_func, OSReallocFunc realloc_func, OSFreeFunc free_func)
{
#if !defined(_ARMTCC_) && !defined(__SYMBIAN32__)
   g_malloc_func  = malloc_func;
   g_free_func    = free_func;

   /* the realloc func could be set to NULL. In this case,
    * malloc/OSCRTLMEMCPY/free will be used. */
   g_realloc_func = realloc_func;
#endif
}
#endif

#if 0 /* was #ifdef _RT_ALLOC_FUNC_WITH_CONTEXT */
EXTRTMETHOD void rtxMemSetAllocCtxtFuncs (OSMallocCtxtFunc malloc_func,
                              OSReallocCtxtFunc realloc_func,
                              OSFreeCtxtFunc free_func)
{
   g_malloc_ctxt_func = malloc_func;
   g_realloc_ctxt_func = realloc_func;
   g_free_ctxt_func = free_func;
}
#endif

EXTRTMETHOD void* rtxMemHeapAllocZ (void** ppvMemHeap, size_t nbytes)
{
   void* ptr = rtxMemHeapAlloc (ppvMemHeap, nbytes);
   if (0 != ptr) OSCRTLMEMSET (ptr, 0, nbytes);
   return ptr;
}

EXTRTMETHOD OSUINT32 rtxMemHeapGetDefBlkSize (OSCTXT* pctxt) 
{
   if (pctxt == 0 || pctxt->pMemHeap == 0) return g_defBlkSize;
   return ((OSMemHeap*)pctxt->pMemHeap)->defBlkSize;
}

/* Determine if a block of memory is all zero */
EXTRTMETHOD OSBOOL rtxMemIsZero (const void* pmem, size_t memsiz)
{
   size_t i;
   const OSOCTET* pbytes = (const OSOCTET*) pmem;
   for (i = 0; i < memsiz; i++) {
      if (pbytes[i] != 0) return FALSE;
   }
   return TRUE;
}

