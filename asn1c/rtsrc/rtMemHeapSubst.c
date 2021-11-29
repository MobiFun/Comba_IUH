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
#include "rtxsrc/rtxMemory.h"

/* Creates a memory heap */
int rtMemHeapCreate (void** ppvMemHeap) 
{
   return ASN_OK;
}

/* Allocates memory */
void* rtMemHeapAlloc (void** ppvMemHeap, size_t nbytes)
{
   return malloc (nbytes);
}

/* Allocate and zero memory */
void* rtMemHeapAllocZ (void** ppvMemHeap, size_t nbytes)
{
   void* ptr = malloc (nbytes);
   if (0 != ptr) memset (ptr, 0, nbytes);
   return ptr;
}

/* Frees memory pointer */
void rtMemHeapFreePtr (void** ppvMemHeap, void* mem_p) 
{
   free (mem_p);
} 

/* Reallocates memory pointer */
void* rtMemHeapRealloc (void** ppvMemHeap, void* mem_p, size_t nbytes_)
{
   return realloc (mem_p, nbytes_);
}

/* Clears heap memory (frees all memory, reset all heap's variables) */
void rtMemHeapFreeAll (void** ppvMemHeap)
{
   /* should remove all allocated memory. there is no analog in standard memory
      management. */
}

/* increments internal refCnt. use rtMemHeapRelease to decrement and release */
void rtMemHeapAddRef (void** ppvMemHeap)
{
   /* should increment a refCnt of memory heap object to avoid release */
}

/* Frees all memory and heap structure as well (if was allocated) */
void rtMemHeapRelease (void** ppvMemHeap)
{
   /* should free all memory allocated + free memory heap object if exists */
}

/* This function is used for marking memory block as "saved". It means
 * that the memory block containing the specified memory pointer won't be
 * freed after calls to rtMemHeapFreeAll/rtMemHeapReset. User is responsible to free
 * the marked memory block by call to rtMemFreeBlock */

void* rtMemHeapMarkSaved (void** ppvMemHeap, ASN1ConstVoidPtr mem_p, 
                          ASN1BOOL saved) 
{
   return 0;
}

/* This function should return non-zero if the specified pointer is a 
   valid pointer for this memory heap, zero otherwise */
int rtMemHeapCheckPtr (void** ppvMemHeap, void* mem_p)
{
   return 1;
}

/* This function will set the free index in all blocks to zero thereby  */
/* allowing the blocks to be reused (ED, 3/17/2002)..                   */

void rtMemHeapReset (void** ppvMemHeap)
{
}

/* sets the property to the heap */
void rtMemHeapSetProperty (void** ppvMemHeap, ASN1UINT propId, void* pProp)
{
} 
