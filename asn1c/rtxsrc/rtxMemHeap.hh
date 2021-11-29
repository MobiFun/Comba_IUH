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
#ifndef __RTXMEMHEAP_HH__
#define __RTXMEMHEAP_HH__

#ifndef __RTXMEMORY_H__
#define __RTXMEMORY_H__ /* prevent early include of rtxMemory.h */
#define __RTXMEMORY_H__INCLUDED
#endif /* __RTXMEMORY_H__ */
#include "rtxsrc/osSysTypes.h"
#include "rtxsrc/rtxExternDefs.h"
#ifdef __RTXMEMORY_H__INCLUDED
#undef  __RTXMEMORY_H__ 
#endif /* __RTXMEMORY_H__INCLUDED */

#include "rtxsrc/rtxMemory.h"

/* internal heap flags */
#define RT_MH_INTERNALMASK OSUINTCONST(0xF0000000)
#define RT_MH_FREEHEAPDESC OSUINTCONST(0x10000000)
#define RT_MH_USEATOMBLOCK OSUINTCONST(0x20000000)

typedef struct OSMemLink {
   struct OSMemLink* pnext;
   struct OSMemLink* pprev;
   struct OSMemLink* pnextRaw;  /* next RAW block                           */
   void*             pMemBlk;
   OSUINT8           blockType; /* 1 = standard, 2 = raw (see RTMEM* flags) */
   OSUINT8           refcnt; /* reference counter for RAW blocks */
   OSUINT16          spare; /* need to align position of RAW memory block size*/
} OSMemLink;

typedef struct OSRawMemLink {
   OSMemLink base;
   size_t memsize;
} OSRawMemLink;

/* MemLink blockTypes */
#define RTMEMSTD        0x0001
#define RTMEMRAW        0x0002
#define RTMEMMALLOC     0x0004
#define RTMEMSAVED      0x0008
#define RTMEMLINK       0x0010  /* contains MemLink */

/* Memory allocation structures */

typedef struct OSMemHeap {
   OSMemLink*      phead;
   OSUINT32        usedUnits;
   OSUINT32        usedBlocks;
   OSUINT32        freeUnits;
   OSUINT32        freeBlocks;
   OSUINT32        keepFreeUnits;
   OSUINT32        defBlkSize;
   OSUINT32        refCnt;
   OSUINT32        flags;
} OSMemHeap;

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_ARMTCC) && !defined(__SYMBIAN32__)
/* see rtxMemDefs.c file */
extern OSMallocFunc  g_malloc_func;
extern OSReallocFunc g_realloc_func;
extern OSFreeFunc    g_free_func;

#ifdef _RT_ALLOC_FUNC_WITH_CONTEXT
OSMallocCtxtFunc  g_malloc_ctxt_func;
OSReallocCtxtFunc g_realloc_ctxt_func;
OSFreeCtxtFunc    g_free_ctxt_func;
#endif

#else /* ARM thumb compiler or Symbian */
#define g_malloc_func  malloc
#define g_realloc_func realloc
#define g_free_func    free
#endif

#if 0
#define g_malloc_func  OSCRTLMALLOC
#define g_realloc_func OSCRTLREALLOC
#define g_free_func    OSCRTLFREE
#endif

#ifdef __cplusplus
}
#endif

#ifndef _RT_ALLOC_FUNC_WITH_CONTEXT

#define is_realloc_available() (g_realloc_func != 0)
#define _g_malloc_func(h, s) g_malloc_func(s)
#define _g_realloc_func(h, p, s) g_realloc_func(p, s)
#define _g_free_func(h, p) g_free_func(p)

#else /* _RT_ALLOC_FUNC_WITH_CONTEXT defined */

#define H2CTXT(h) ((OSCTXT*)h)
#define is_realloc_available() (g_realloc_ctxt_func != 0)
#define _g_malloc_func(h, s) g_malloc_ctxt_func(H2CTXT(h), s)
#define _g_realloc_func(h, p, s) g_realloc_ctxt_func(H2CTXT(h), p, s)
#define _g_free_func(h, p) g_free_ctxt_func(H2CTXT(h), p)

#endif /* _RT_ALLOC_FUNC_WITH_CONTEXT */

#endif /* __RTXMEMHEAP_HH__ */
