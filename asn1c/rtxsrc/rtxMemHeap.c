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
#include <stdio.h>
#include <stdlib.h>
#include "rtxsrc/rtxCommonDefs.h"
#include "rtxsrc/rtxMemHeap.hh"
#include "rtxsrc/rtxErrCodes.h"

#if defined(_WIN32_WCE)
#include "rtxsrc/wceAddon.h"
#endif

#ifdef _DEBUG
#include "rtxsrc/rtxDiag.h"
/* Note: by default debug support is disabled because it makes the 
 * memory manager run extrememly slow.  This should only be turned on 
 * if it is necessary to debug a memory problem..
 * #define _MEMDEBUG
 * #define _MEMTRACE */
#endif

#if defined (WIN32) && defined (_MEMDEBUG)
#include <windows.h>
#endif

/* Encoded copyright string. */
#define copyright __s25x
const char copyright[] = {
   '\x00', '\xC1', '\x3B', '\xD6', '\xC6', '\xAF', '\xF6', '\x57', 
   '\xAC', '\xB3', '\x4E', '\x3D', '\xC7', '\xBB', '\xF7', '\x5A', 
   '\xEA', '\xF6', '\x45', '\x24', '\x99', '\xB3', '\xEA', '\x60', 
   '\xA6', '\xE9', '\x5E', '\x12', '\xE9', '\xE3', '\x54', '\x22', 
   '\xAF', '\xDA', '\x0D', '\x8B', '\x90', '\xF2', '\xCB', '\x2E', 
   '\xED', '\xD5', '\x56', '\x03', '\xB1', '\xCA', '\x27', '\xCE', 
   '\xA4', '\xC1', '\x69', '\xC1', '\xDE', '\x3D', '\xE9', '\x5E', 
   '\xA7', '\xE7', '\x05', '\x73', '\x08', '\xED', '\x65', '\x22', 
   '\x5D'
};

static OSMemLink* rtxMemHeapAddBlock (OSMemLink** ppMemLink, 
                                      void* pMemBlk, int blockType);

typedef void OSMemElemDescr;

#if 0
/* Structure cannot be used here because we need to be sure that the 
   size of this structure is exactly 8 bytes. On XScale CPU, this 
   structure is size 12 bytes, because of alignment of short values on 
   32-bit boundary. To prevent this, use pElem_<> macros instead of 
   structure fields. */
typedef struct MemElemDescr {
   OSUINT8        flags;       /* isFree = 1, isLast = 2, isSaved = 4 */
   OSUINT8        refcnt;      /* reference counter to memory block */
   OSUINT16       nunits;      /* size = nunits * 8 */
   OSUINT16       prevOff;     /* offset of the prev block (-prevOff * 8) */
   union {
      OSUINT16    nextFreeOff; /* offset/8 of the next free block */
      OSUINT16    beginOff;    /* offset/8 of the beginning of data block in MemBlk */
   } u;

} OSMemElemDescr;
#endif

#define pElem_flags(pElem)       (*((OSOCTET*)pElem))
#define pElem_refcnt(pElem)      (*(((OSOCTET*)pElem)+1))
#define pElem_nunits(pElem)      (*((OSUINT16*)(((OSOCTET*)pElem)+2)))
#define pElem_prevOff(pElem)     (*((OSUINT16*)(((OSOCTET*)pElem)+4)))
#define pElem_nextFreeOff(pElem) (*((OSUINT16*)(((OSOCTET*)pElem)+6)))
#define pElem_beginOff(pElem)    (*((OSUINT16*)(((OSOCTET*)pElem)+6)))
#define sizeof_OSMemElemDescr    8
#define pElem_data(pElem)        (((OSOCTET*)pElem)+sizeof_OSMemElemDescr)

typedef struct MemBlk {
   OSMemLink*      plink;
   OSUINT16       free_x;      /* index of free space at end of block */
   OSUINT16       freeMem;     /* size of free space before free_x    */
   OSUINT16       nunits;      /* size of data                        */
   OSUINT16       lastElemOff; /* last element offset in block        */
   OSUINT16       freeElemOff; /* first free element offset in block  */
   OSUINT16       nsaved;      /* num of saved elems in the block     */

   OSUINT16       spare[2];    /* forces alignment on 8-bytes boundary,
                                   for 64-bit systems */
/*   
   OSOCTET       spare [
      (sizeof (OSUINT16) * 6 + sizeof (void*) + 7) / 8 * 8 - 
      (sizeof (OSUINT16) * 6 + sizeof (void*))];
*/
   char            data[8];
} OSMemBlk;

/* Macros for convinient operations with memory blocks */

#define QOFFSETOF(pElem, pPrevElem) \
((OSUINT16)(((unsigned)((char*)pElem - (char*)pPrevElem)) >> 3u))

#define OFFSETOF(pElem, pPrevElem) \
((OSUINT32)((char*)pElem - (char*)pPrevElem))

#define ISFREE(pElem)      (pElem_flags(pElem) & 1)
#define SET_FREE(pElem)    (pElem_flags(pElem) |= 1)
#define CLEAR_FREE(pElem)  (pElem_flags(pElem) &= (OSOCTET)(~1))

#define ISLAST(pElem)      (pElem_flags(pElem) & 2)
#define SET_LAST(pElem)    (pElem_flags(pElem) |= 2)
#define CLEAR_LAST(pElem)  (pElem_flags(pElem) &= (OSOCTET)(~2))

#define ISSAVED(pElem)      (pElem_flags(pElem) & 4)
#define SET_SAVED(pMemBlk,pElem)    do { \
(pElem_flags (pElem) |= 4); pMemBlk->nsaved++; } while (0)
#define CLEAR_SAVED(pMemBlk,pElem)  do { \
(pElem_flags (pElem) &= (OSOCTET)(~4)); pMemBlk->nsaved--; } while (0)

#define ISFIRST(pElem)    (int)(pElem_prevOff (pElem) == 0)

#define GETPREV(pElem) \
((pElem_prevOff (pElem) == 0) ? 0 : \
((OSMemElemDescr*) (((char*)pElem) - (pElem_prevOff (pElem) * 8u))))

#define GETNEXT(pElem) \
((ISLAST (pElem)) ? 0 : \
((OSMemElemDescr*)(((char*)pElem) + ((pElem_nunits (pElem) + 1) * 8u))))

#define GET_NEXT_FREE(pElem) \
((pElem_nextFreeOff (pElem) == 0) ? 0 : \
((OSMemElemDescr*) (((char*)pElem) + (pElem_nextFreeOff (pElem) * 8u))))

#define GET_MEMBLK(pElem) \
((OSMemBlk*) (((char*)pElem) - (pElem_beginOff (pElem) * 8u) - \
sizeof (OSMemBlk) + sizeof ((OSMemBlk*)0)->data))

#define GET_LAST_ELEM(pMemBlk) \
((pMemBlk->lastElemOff == 0) ? 0 : \
(OSMemElemDescr*)&pMemBlk->data[(pMemBlk->lastElemOff - 1) * 8u])

#define SET_LAST_ELEM(pMemBlk, pElem) \
pMemBlk->lastElemOff = (OSUINT16)((pElem == 0) ? 0 : \
(SET_LAST (pElem), (QOFFSETOF (pElem, pMemBlk->data) + 1)))

#define GET_FREE_ELEM(pMemBlk) \
((pMemBlk->freeElemOff == 0) ? 0 : \
(OSMemElemDescr*)&pMemBlk->data[(pMemBlk->freeElemOff - 1) * 8u])

#define FORCE_SET_FREE_ELEM(pMemBlk, pElem) do { \
if (pElem == 0) { pMemBlk->freeElemOff = 0; break; } \
SET_FREE (pElem); \
pMemBlk->freeElemOff = (OSUINT16)(QOFFSETOF (pElem, pMemBlk->data) + 1); \
} while (0)

#define SET_FREE_ELEM(pMemBlk, pElem) setLastElem (pMemBlk, pElem)

/* Memory debugging macros */

#ifdef _MEMDEBUG
#define FILLFREEMEM(mem,size)   OSCRTLMEMSET (mem, 0xFE, size)
#define FILLNEWMEM(mem,size)    OSCRTLMEMSET (mem, 0xA0, size)
#define CHECKMEMELEM(memblk,elem) \
_rtxMemCheckElement (memblk, elem, __FILE__, __LINE__)
#define CHECKMEMBLOCK(memheap,memblk) \
_rtxMemCheckBlock (memheap,memblk, __FILE__, __LINE__)
#define CHECKMEMHEAP(memheap)   _rtxMemCheckHeap (memheap, __FILE__, __LINE__)
#ifdef WIN32
#define DEBUG_BREAK do { DebugBreak (); abort (); } while (0)
#else
#define DEBUG_BREAK abort ()
#endif /* WIN32 */

#ifdef _MEMTRACE
OSCTXT gs_diag_pctxt;
#define RTMEMDIAG1(msg)         do { \
rtxSetDiag (&gs_diag_pctxt, 1); rtxDiagPrint(&gs_diag_pctxt,msg); } while(0)
#define RTMEMDIAG2(msg,a)       do { \
rtxSetDiag (&gs_diag_pctxt, 1); rtxDiagPrint(&gs_diag_pctxt,msg,a); } while(0)
#define RTMEMDIAG3(msg,a,b)     do { \
rtxSetDiag (&gs_diag_pctxt, 1); rtxDiagPrint(&gs_diag_pctxt,msg,a,b); \
} while(0)
#define RTMEMDIAG4(msg,a,b,c)   do { \
rtxSetDiag (&gs_diag_pctxt, 1); rtxDiagPrint(&gs_diag_pctxt,msg,a,b,c); \
} while(0)

#define RTMEMDIAGSTRM1(msg)       RTMEMDIAG1(msg)
#define RTMEMDIAGSTRM2(msg,a)     RTMEMDIAG2(msg,a)
#define RTMEMDIAGSTRM3(msg,a,b)   RTMEMDIAG3(msg,a,b)
#define RTMEMDIAGSTRM4(msg,a,b,c) RTMEMDIAG4(msg,a,b,c)

#define TRACEMEMELEM(memblk, elem, name) do { \
   _rtxMemPrintMemElem (memblk, elem, name); fprintf (stderr, "\n"); \
   fflush (stderr); \
   } while (0)
#define TRACEFREE(memlink,name) do { \
   fprintf (stderr, "%s 0x%X\n", name, memlink); \
   fflush (stderr); \
   } while (0)
#else
#define TRACEMEMELEM(memblk, elem, name)
#define TRACEFREE(memlink,name)

#define RTMEMDIAG1(msg)
#define RTMEMDIAG2(msg,a)
#define RTMEMDIAG3(msg,a,b)
#define RTMEMDIAG4(msg,a,b,c)

#define RTMEMDIAGSTRM1(msg)
#define RTMEMDIAGSTRM2(msg,a)
#define RTMEMDIAGSTRM3(msg,a,b)
#define RTMEMDIAGSTRM4(msg,a,b,c)
#endif /* _MEMTRACE */


void _rtxMemPrintMemBlk (OSMemBlk* pMemBlk) {
   fprintf (stderr, "pMemBlk = %p\n", pMemBlk);
   fprintf (stderr, "pMemBlk->nunits *8      = %i\n", pMemBlk->nunits*8);
   fprintf (stderr, "pMemBlk->free_x *8      = %i\n", pMemBlk->free_x*8);
   fprintf (stderr, "pMemBlk->freeMem *8     = %i\n", pMemBlk->freeMem*8);
   fprintf (stderr, "pMemBlk->lastElemOff *8 = %i\n", pMemBlk->lastElemOff*8);
   fprintf (stderr, "pMemBlk->freeElemOff *8 = %i\n", pMemBlk->freeElemOff*8);
   fprintf (stderr, "pMemBlk->nsaved         = %i\n", pMemBlk->nsaved);
   fflush (stderr);
}

void _rtxMemPrintMemElem (OSMemBlk* pMemBlk, OSMemElemDescr* pElem, 
   const char* elemName) 
{
   if (pElem == 0) {
      fprintf (stderr, "pMemBlk = %p\n", pMemBlk);
      fprintf (stderr, "%s == NULL\n", elemName);
      fflush (stderr);
      return;
   }
   fprintf (stderr, "Offset of %s is %i (%i units)\n", elemName,
      OFFSETOF (pElem, pMemBlk->data), QOFFSETOF (pElem, pMemBlk->data));
   fprintf (stderr, "%s->flags            = 0x%x\n", elemName, pElem_flags (pElem));
   fprintf (stderr, "%s->refcnt           = %d\n", elemName, pElem_refcnt (pElem));
   fprintf (stderr, "%s->nunits *8        = %d\n", elemName, pElem_nunits (pElem)*8);
   fprintf (stderr, "%s->prevOff *8       = %d\n", elemName, pElem_prevOff (pElem)*8);
   if (ISFREE(pElem))
      fprintf (stderr, "%s->u.nextFreeOff *8 = %d\n", elemName, 
         pElem_nextFreeOff (pElem) *8);
   else
      fprintf (stderr, "%s->u.beginOff *8    = %d\n", elemName, 
         pElem_beginOff (pElem) *8);
   fflush (stderr);
}

void _rtxMemCheckReport (OSMemBlk* pMemBlk, OSMemElemDescr* pElem, 
   const char* file, int line) 
{
   fprintf (stderr, "Memory report at %s, line %i\n", file, line);
   _rtxMemPrintMemBlk (pMemBlk);
   fprintf (stderr, "\n");

   if (pElem != 0) {
      _rtxMemPrintMemElem (pMemBlk, pElem, "pElem");
      fprintf (stderr, "\n");
   }
   fflush (stderr);
}

void _rtxMemCheckElement (OSMemBlk* pMemBlk, OSMemElemDescr* pElem, 
                         const char* file, int line) 
{
   OSMemElemDescr* pPrevElem;
   OSMemElemDescr* pCurElem;

   if (pElem == 0) return;

   if (pElem_flags (pElem) > 8 ||
      (char*)pElem < (char*)pMemBlk->data ||
      (char*)pElem > (char*)pMemBlk->data + 
      (((OSUINT32)(pMemBlk->nunits - pElem_nunits (pElem) - 1)) * 8u))
   {
      fprintf (stderr, "Error 1 occurred from %s, line %i\n", file, line);
      _rtxMemCheckReport (pMemBlk, pElem, __FILE__, __LINE__);
      DEBUG_BREAK;
   }
   
   pPrevElem = GETPREV (pElem);
   if (pPrevElem != 0 && GETNEXT (pPrevElem) != pElem) {
      fprintf (stderr, "Error 2 occurred from %s, line %i\n", file, line);
      _rtxMemCheckReport (pMemBlk, pPrevElem, __FILE__, __LINE__);
      DEBUG_BREAK;
   }

   /* check is element inside the memblk and is it legal? */
   pCurElem = (OSMemElemDescr*) pMemBlk->data;
   for (; pCurElem != 0; pCurElem = GETNEXT (pCurElem)) {
      if (pElem == pCurElem)
         break;
   }
   if (pCurElem == 0) {
      /* not found! */
      fprintf (stderr, "Error 23 occurred from %s, line %i\n", file, line);
      _rtxMemCheckReport (pMemBlk, pElem, __FILE__, __LINE__);
      DEBUG_BREAK;
   }

   if (ISFREE (pElem)) {
      OSMemElemDescr* pNextElem = GET_NEXT_FREE (pElem);

      if (pElem_nextFreeOff (pElem) != 0 && 
         pElem_nextFreeOff (pElem) < pElem_nunits (pElem) + 1) 
      {
         fprintf (stderr, "Error 15 occurred from %s, line %i\n", file, line);
         _rtxMemCheckReport (pMemBlk, pElem, __FILE__, __LINE__);
         DEBUG_BREAK;
      }

      if (pNextElem != 0 && (pNextElem < pElem ||
         (char*)pNextElem < (char*)pMemBlk->data ||
         (char*)pNextElem > (char*)pMemBlk->data + 
         (((OSUINT32)(pMemBlk->nunits - pElem_nunits (pNextElem) - 1)) * 8u)))
      {
         fprintf (stderr, "Error 3 occurred from %s, line %i\n", file, line);
         _rtxMemCheckReport (pMemBlk, pElem, __FILE__, __LINE__);
         _rtxMemPrintMemElem (pMemBlk, pNextElem, "pNextElem");
         DEBUG_BREAK;
      }

      pNextElem = GETNEXT (pElem);
      if ((pNextElem != 0 && ISFREE (pNextElem)) || 
          (pPrevElem != 0 && ISFREE (pPrevElem))) 
      {
         fprintf (stderr, "Error 11 occurred from %s, line %i\n", file, line);
         _rtxMemCheckReport (pMemBlk, pElem, __FILE__, __LINE__);
         _rtxMemPrintMemElem (pMemBlk, pPrevElem, "pPrevElem");
         _rtxMemPrintMemElem (pMemBlk, pNextElem, "pNextElem");
         DEBUG_BREAK;
      }

      pNextElem = GET_FREE_ELEM (pMemBlk);
      if (pNextElem == 0 || (pNextElem > pElem && 
         (OSOCTET*)pNextElem < pElem_data (pElem) + 
         (((OSUINT32)pElem_nunits (pElem)) * 8u))) 
      {
         fprintf (stderr, "Error 13 occurred from %s, line %i\n", file, line);
         _rtxMemCheckReport (pMemBlk, pElem, __FILE__, __LINE__);
         _rtxMemPrintMemElem (pMemBlk, pNextElem, "pFreeElem");
         DEBUG_BREAK;
      }
   }
   else {
      OSMemElemDescr* pNextElem = GET_FREE_ELEM (pMemBlk);
      if (pNextElem != 0 && 
         (pNextElem == pElem || 
         (pNextElem > pElem && 
         (OSOCTET*)pNextElem < 
          pElem_data (pElem) 
           + (((OSUINT32)pElem_nunits (pElem)) * 8u))))
      {
         fprintf (stderr, "Error 16 occurred from %s, line %i\n", file, line);
         _rtxMemCheckReport (pMemBlk, pElem, __FILE__, __LINE__);
         DEBUG_BREAK;
      }
      if (pElem_beginOff (pElem) != QOFFSETOF (pElem, pMemBlk->data)) {
         fprintf (stderr, "Error 4 occurred from %s, line %i\n", file, line);
         _rtxMemCheckReport (pMemBlk, pElem, __FILE__, __LINE__);
         DEBUG_BREAK;
      }
   }
}

void _rtxMemCheckBlock (OSMemHeap* pMemHeap, OSMemBlk* pMemBlk, 
                       const char* file, int line) 
{
   OSMemElemDescr* pLastElem, *pElem, *pRealLast = 0, *pNextFree = 0;
   int first = 1, found;
   unsigned freeMem = 0;
   OSMemLink* pMemLink;

   pMemLink = pMemHeap->phead;

   /* check, is this pMemBlk inside the specified pMemHeap? */

   for (found = 0; pMemLink != 0; pMemLink = pMemLink->pnext) {
      if (pMemLink->pMemBlk == pMemBlk) 
         found = 1;
   }
   if (found == 0) {
      fprintf (stderr, "Error 22 occurred from %s, line %i\n", file, line);
      _rtxMemCheckReport (pMemBlk, 0, __FILE__, __LINE__);
      DEBUG_BREAK;
   }

   if (pMemBlk->free_x > pMemBlk->nunits || 
       pMemBlk->freeMem >= pMemBlk->nunits) 
   {
      fprintf (stderr, "Error 5 occurred from %s, line %i\n", file, line);
      _rtxMemCheckReport (pMemBlk, 0, __FILE__, __LINE__);
      DEBUG_BREAK;
   }
   
   pLastElem = GET_LAST_ELEM (pMemBlk);
   if (pLastElem == 0) {
      if (pMemBlk->free_x != 0 || pMemBlk->freeMem != 0 ||
          pMemBlk->freeElemOff != 0 || pMemBlk->lastElemOff != 0) 
      {
         /* pLastElem is NULL, but not all other vars are NULL */
         fprintf (stderr, "Error 19 occurred from %s, line %i\n", file, line);
         _rtxMemCheckReport (pMemBlk, 0, __FILE__, __LINE__);
         DEBUG_BREAK;
      }
   }
   else {
      int nsaved = 0;

      if (!ISLAST (pLastElem)) {
         fprintf (stderr, "Error 6 occurred from %s, line %i\n", file, line);
         _rtxMemCheckReport (pMemBlk, pLastElem, __FILE__, __LINE__);
         DEBUG_BREAK;
      }

      pElem = GET_FREE_ELEM (pMemBlk);
      if (pElem != 0) {
         if (!ISFREE (pElem) || ISLAST (pElem)) {
            fprintf (stderr, "Error 17 occurred from %s, line %i\n", file, line);
            _rtxMemCheckReport (pMemBlk, pElem, __FILE__, __LINE__);
            DEBUG_BREAK;
         }
         _rtxMemCheckElement (pMemBlk, pElem, __FILE__, __LINE__);

         for (; pElem != 0; pElem = GET_NEXT_FREE (pElem)) {
            if (!ISFREE (pElem)) {
               fprintf (stderr, "Error 18 occurred from %s, line %i\n", 
                  file, line);
               _rtxMemCheckReport (pMemBlk, pElem, __FILE__, __LINE__);
               DEBUG_BREAK;
            }
            _rtxMemCheckElement (pMemBlk, pElem, __FILE__, __LINE__);
         }
      }

      pElem = (OSMemElemDescr*) pMemBlk->data;
      for (; pElem != 0; pElem = GETNEXT (pElem)) {
         _rtxMemCheckElement (pMemBlk, pElem, file, line);
         pRealLast = pElem;
         if (ISFREE (pElem)) {
            if (first && 
               QOFFSETOF (pElem, pMemBlk->data) != pMemBlk->freeElemOff - 1) 
            {
               fprintf (stderr, "Error 7 occurred from %s, line %i\n", file, line);
               _rtxMemCheckReport (pMemBlk, pElem, __FILE__, __LINE__);
               DEBUG_BREAK;
            }

            if (pNextFree != 0 && pElem != pNextFree) {
               fprintf (stderr, "Error 14 occurred from %s, line %i\n", 
                  file, line);
               _rtxMemCheckReport (pMemBlk, pElem, __FILE__, __LINE__);
               _rtxMemPrintMemElem (pMemBlk, pNextFree, "pNextFree");
               DEBUG_BREAK;
            }

            pNextFree = GET_NEXT_FREE (pElem);
            first = 0;   
            freeMem += pElem_nunits (pElem);
         }
         if (ISSAVED (pElem)) 
            nsaved++;
      }

      if (pRealLast == 0 || ISFREE (pRealLast) || pRealLast != pLastElem)
      {
         fprintf (stderr, "Error 12 occurred from %s, line %i\n", file, line);
         _rtxMemCheckReport (pMemBlk, 0, __FILE__, __LINE__);
         _rtxMemPrintMemElem (pMemBlk, pRealLast, "pRealLast");
         _rtxMemPrintMemElem (pMemBlk, pLastElem, "pLastElem");
         DEBUG_BREAK;
      }

      if (freeMem != (unsigned)pMemBlk->freeMem) {
         fprintf (stderr, "Error 8 occurred from %s, line %i\n", file, line);
         _rtxMemCheckReport (pMemBlk, 0, __FILE__, __LINE__);
         DEBUG_BREAK;
      }

      if (nsaved != pMemBlk->nsaved) {
         fprintf (stderr, "Error 20 occurred from %s, line %i\n", file, line);
         _rtxMemCheckReport (pMemBlk, 0, __FILE__, __LINE__);
         DEBUG_BREAK;
      }
   }
}

void _rtxMemCheckHeap (OSMemHeap* pMemHeap, const char* file, int line) {
   OSMemLink* cur, *prev = 0;

   for (cur = pMemHeap->phead; cur; prev = cur, cur = cur->pnext) {
      if (prev != cur->pprev) {
         fprintf (stderr, "Invalid MemLink!\n");
         fprintf (stderr, "Error 9 occurred from %s, line %i\n", file, line);
         DEBUG_BREAK;
      }

      if (cur->blockType & 
          (OSOCTET)(~(RTMEMSTD | RTMEMRAW | RTMEMMALLOC | RTMEMSAVED | RTMEMLINK)))
      {
         fprintf (stderr, "Invalid MemLink's blockType = %i\n", 
            cur->blockType);
         fprintf (stderr, "Error 10 occurred from %s, line %i\n", file, line);
         DEBUG_BREAK;
      }

      if (!(cur->blockType & RTMEMSTD))
         continue;

      if (((OSMemBlk*)cur->pMemBlk)->nsaved != 0 && 
         !(cur->blockType & RTMEMSAVED))
      {
         fprintf (stderr, "Error 21 occurred from %s, line %i\n", file, line);
         _rtxMemCheckReport (((OSMemBlk*)cur->pMemBlk), 0, 
                            __FILE__, __LINE__);
         DEBUG_BREAK;
      }

      _rtxMemCheckBlock (pMemHeap, (OSMemBlk*)cur->pMemBlk, __FILE__, __LINE__);
   }
}

void rtxMemCheckHeap (OSMemHeap* pMemHeap) 
{
   _rtxMemCheckHeap (pMemHeap, __FILE__, __LINE__);
}

void rtxMemPrintHeap (OSMemHeap* pMemHeap) 
{
   OSMemLink* cur;
   OSMemElemDescr* pElem;

   for (cur = pMemHeap->phead; cur; cur = cur->pnext) {
      OSMemBlk* pMemBlk;

      if (!(cur->blockType & RTMEMSTD)) {
         OSRawMemLink* p = (OSRawMemLink*) cur;
         fprintf (stderr, "Raw mem block, ptr = %p, size = %i\n", 
                  cur->pMemBlk, p->memsize);
      }
      else {
         pMemBlk = (OSMemBlk*)cur->pMemBlk;
         _rtxMemPrintMemBlk (pMemBlk);
         fprintf (stderr, "\n-!-\n");

         pElem = (OSMemElemDescr*) pMemBlk->data;
         for (; pElem != 0; pElem = GETNEXT (pElem)) {
            _rtxMemPrintMemElem (pMemBlk, pElem, "pElem");
            fprintf (stderr, "\n");
         }
      }

      fprintf (stderr, "\n-----\n\n");
   }
}

#else
#define RTMEMDIAG1(msg)
#define RTMEMDIAG2(msg,a)
#define RTMEMDIAG3(msg,a,b)
#define RTMEMDIAG4(msg,a,b,c)

#define RTMEMDIAGSTRM1(msg)
#define RTMEMDIAGSTRM2(msg,a)
#define RTMEMDIAGSTRM3(msg,a,b)
#define RTMEMDIAGSTRM4(msg,a,b,c)

#define FILLFREEMEM(mem,size)
#define FILLNEWMEM(mem,size)
#define CHECKMEMELEM(memblk, elem)
#define CHECKMEMBLOCK(memheap,memblk)
#define CHECKMEMHEAP(memheap)
#define TRACEMEMELEM(memblk, elem, name)
#define TRACEFREE(memlink,name)
#endif /* _MEMDEBUG */

static void setLastElem (OSMemBlk* pMemBlk, OSMemElemDescr* pElem) 
{
   if (pElem == 0) { 
      pMemBlk->freeElemOff = 0; 
      return; 
   }
   else if (ISLAST (pElem)) 
      return; 
   else if (pMemBlk->freeElemOff > QOFFSETOF (pElem, pMemBlk->data) + 1) {
      pElem_nextFreeOff (pElem) = QOFFSETOF (GET_FREE_ELEM (pMemBlk), pElem); 
      FORCE_SET_FREE_ELEM (pMemBlk, pElem); 
   } 
   else if (pMemBlk->freeElemOff == 0) { 
      pElem_nextFreeOff (pElem) = 0;          
      FORCE_SET_FREE_ELEM (pMemBlk, pElem); 
   } 
   else { 
      SET_FREE (pElem); 
      pElem_nextFreeOff (pElem) = 0; 
   }
}

static void* memHeapAlloc 
(void** ppvMemHeap, size_t nbytes, OSMemLink** ppMemLink)
{
   OSMemHeap* pMemHeap;
   OSMemLink* pMemLink;
   OSMemBlk*  pMemBlk = 0;
   void* mem_p = NULL;
   unsigned remUnits;
   OSUINT32 nunits;

   if (ppvMemHeap == 0)
      return 0;

   if (*ppvMemHeap == 0)
      if (rtxMemHeapCreate (ppvMemHeap) != 0)
         return 0;

   RTMEMDIAGSTRM1 ("~D rtxMemHeapAlloc: start\n");

   /* Round number of bytes to nearest 8-byte boundary */

   nunits = (((unsigned)(nbytes + 7)) >> 3);

   pMemHeap = (OSMemHeap*) *ppvMemHeap;

   /* if size is greater than 2**19, then allocate as RAW block */
   if ((pMemHeap->flags & RT_MH_USEATOMBLOCK) || (nunits > (1UL<<16) - 2)) {
      void *data;

      /* allocate raw block */

      data = _g_malloc_func (ppvMemHeap, nbytes);
      if (data == NULL) {
         /* The followed code will never be executed, it is 
          * necessary only to prevent the dropping out the copyright 
          * string by the linker */
         if (copyright [0] != 0) {
            data = mem_p; 
         }
         return NULL;
      }
      pMemLink = *ppMemLink = rtxMemHeapAddBlock 
         (&pMemHeap->phead, data, RTMEMMALLOC | RTMEMRAW);
      if (pMemLink == 0) {
         _g_free_func (ppvMemHeap, data);
         return NULL;
      }
      /* Save size of the RAW memory block behind the pMemLink */
      ((OSRawMemLink*)pMemLink)->memsize = nbytes;

      return data;   
   }
   
   RTMEMDIAGSTRM2 ("~D rtxMemHeapAlloc: adjusted nbytes = %d\n", nbytes);

   /* Try to allocate a slot from an existing block on the list */

   for (pMemLink = pMemHeap->phead; pMemLink != 0; pMemLink = pMemLink->pnext) {
      if (pMemLink->blockType & RTMEMRAW) continue;
      else pMemBlk = (OSMemBlk*) pMemLink->pMemBlk;

      remUnits = pMemBlk->nunits - pMemBlk->free_x;

      if ((unsigned)(nunits + 1) <= remUnits) {
         OSMemElemDescr* pElem = (OSMemElemDescr*)
            &pMemBlk->data [((OSUINT32)pMemBlk->free_x) * 8u];
         OSMemElemDescr* pPrevElem;

         RTMEMDIAGSTRM1 ("~D rtxMemHeapAlloc: found existing slot..\n");

         /* if block is clean, set some vars in heap */
         if (pMemBlk->free_x == 0) {
            pMemHeap->freeUnits -= pMemBlk->nunits;
            pMemHeap->freeBlocks--;
         }

         pElem_flags (pElem) = 0;
         pElem_refcnt (pElem) = 1;
         if (pMemBlk->lastElemOff != 0)
            pElem_prevOff (pElem) = 
               (OSUINT16)(pMemBlk->free_x - pMemBlk->lastElemOff + 1);
         else 
            pElem_prevOff (pElem) = 0;
         
         pPrevElem = GET_LAST_ELEM (pMemBlk);
         if (pPrevElem != 0)
            CLEAR_LAST (pPrevElem);
         
         pElem_nunits (pElem) = (OSUINT16)nunits; 
         pElem_beginOff (pElem) = QOFFSETOF (pElem, pMemBlk->data);
         pMemBlk->lastElemOff = (OSUINT16)(pMemBlk->free_x + 1);

         mem_p = (void*) (pElem_data (pElem));
         
         /* sizeof (OSMemElemDescr) == 1 unit */
         pMemBlk->free_x = (OSUINT16)(pMemBlk->free_x + (nunits + 1));
         
         SET_LAST_ELEM (pMemBlk, pElem);
         
         FILLNEWMEM (mem_p, nunits * 8u);
         TRACEMEMELEM(pMemBlk, pElem, "Allocated");
         CHECKMEMELEM (pMemBlk, pElem);
         CHECKMEMBLOCK (pMemHeap, pMemBlk);
         *ppMemLink = pMemLink;
         break;
      }
   }

   /* If not successful, look for empty elements in existing blocks */

   if (0 == mem_p) {
      for (pMemLink = pMemHeap->phead; 
           pMemLink != 0; pMemLink = pMemLink->pnext) 
      {
         if (pMemLink->blockType & RTMEMRAW) continue;
         
         *ppMemLink = pMemLink;
         pMemBlk = (OSMemBlk*) pMemLink->pMemBlk;

         if (nunits <= (OSUINT32)pMemBlk->freeMem) {
            OSMemElemDescr* pElem = GET_FREE_ELEM(pMemBlk), *pPrevFree = 0;

            RTMEMDIAGSTRM2 
               ("~D rtxMemHeapAlloc: try to reuse empty elems in "
                "pMemBlk = 0x%x...\n", pMemBlk);

            while (pElem != 0) {
               if (ISFREE (pElem)) { 
                  if (nunits <= (OSUINT32)pElem_nunits (pElem)) {
                     RTMEMDIAGSTRM3 
                        ("~I rtxMemHeapAlloc: "
                         "found an exisiting free element 0x%x, size %d\n", 
                         pElem, (pElem_nunits (pElem) * 8u));
                     
                     if (pMemBlk->freeElemOff == 
                         QOFFSETOF (pElem, pMemBlk->data) + 1) 
                     {
                        
                        /* modify the pMemBlk->freeElemOff value if necsry */

                        OSMemElemDescr* nextFree = GET_NEXT_FREE (pElem);
                        FORCE_SET_FREE_ELEM (pMemBlk, nextFree); 
                     }
                     else if (pPrevFree != 0) {
                        OSMemElemDescr* pNextFree = GET_NEXT_FREE (pElem);
                        if (pNextFree != 0)
                           pElem_nextFreeOff (pPrevFree) = 
                              QOFFSETOF (pNextFree, pPrevFree);
                        else
                           pElem_nextFreeOff (pPrevFree) = 0;
                     } 

                     CLEAR_FREE (pElem);
                     pElem_refcnt (pElem) = 1;

                     /* set beginOff value */

                     pElem_beginOff (pElem) = QOFFSETOF (pElem, pMemBlk->data);
                     
                     pMemBlk->freeMem = 
                        (OSUINT16)(pMemBlk->freeMem - (pElem_nunits (pElem)));

                     CHECKMEMELEM (pMemBlk, pElem);
                     CHECKMEMBLOCK (pMemHeap, pMemBlk);
                     
                     mem_p = rtxMemHeapRealloc 
                        (ppvMemHeap, pElem_data (pElem), nunits * 8u);
                     if (mem_p != 0) {
                        FILLNEWMEM (mem_p, nunits * 8u);
                        TRACEMEMELEM(pMemBlk, pElem, "Allocated");
                     }
                     break;
                  }
               }
               pPrevFree = pElem;
               pElem = GET_NEXT_FREE (pElem);
            }
            if (mem_p != 0) break;
         }
      }   
   }

   /* If not successful, malloc a new block and alloc from it */

   if (!mem_p) {
      OSUINT32 allocSize, dataUnits;
      OSOCTET* pmem;
      register OSUINT32 defBlkSize = pMemHeap->defBlkSize;

      RTMEMDIAGSTRM1 ("~D rtxMemHeapAlloc: alloc block..\n");

      allocSize = (OSUINT32) ((((OSUINT32)nunits) * 8u) + 
         sizeof (OSMemBlk) + sizeof_OSMemElemDescr);
      allocSize = (OSUINT32) (allocSize < defBlkSize) ? defBlkSize : 
         ((allocSize + defBlkSize - 1) / defBlkSize * defBlkSize);
      dataUnits = (OSUINT32)((allocSize - sizeof (OSMemBlk)) >> 3u);
      if (dataUnits >= (1ul<<16)) {
         dataUnits = (OSUINT32)((1ul<<16) - 1);
         allocSize = (OSUINT32)
            ((((OSUINT32)dataUnits) * 8u) + sizeof (OSMemBlk));
      }  

      pmem = (OSOCTET*) _g_malloc_func 
         (ppvMemHeap, allocSize + sizeof (OSMemLink));

      if (0 != pmem) {
         OSMemElemDescr* pElem;

         pMemBlk = (OSMemBlk*) (pmem + sizeof (OSMemLink));
         pElem = (OSMemElemDescr*)&pMemBlk->data[0];

         mem_p = (void*) pElem_data (pElem);
         pElem_nunits (pElem) = (OSUINT16)nunits;
         pElem_flags (pElem) = 0;
         pElem_refcnt (pElem) = 1;
         pElem_prevOff (pElem) = 0;
         pElem_beginOff (pElem) = QOFFSETOF (pElem, pMemBlk->data);

         /* sizeof (OSMemElemDescr) == 1 unit */
         pMemBlk->free_x = (OSUINT16)(nunits + 1); 

         pMemBlk->freeMem = 0;
         pMemBlk->nunits = (OSUINT16)dataUnits;
         SET_LAST_ELEM (pMemBlk, pElem);
         pMemBlk->freeElemOff = 0;
         pMemBlk->nsaved = 0;

         *ppMemLink = rtxMemHeapAddBlock 
            (&pMemHeap->phead, pMemBlk, RTMEMSTD | RTMEMLINK);

         if (0 == *ppMemLink) {
            _g_free_func (ppvMemHeap, pmem);
            return NULL;
         }

         /* set vars in heap */
         pMemHeap->usedUnits += dataUnits;
         pMemHeap->usedBlocks++;

         FILLNEWMEM (mem_p, nunits * 8u);
         TRACEMEMELEM(pMemBlk, pElem, "Allocated");
         CHECKMEMELEM (pMemBlk, pElem);
         CHECKMEMBLOCK (pMemHeap, pMemBlk);
      }
      else 
         return NULL;
   }
   RTMEMDIAGSTRM2 ("~D rtxMemHeapAlloc: pMemBlk = 0x%x\n", pMemBlk);
   RTMEMDIAGSTRM2 ("~D rtxMemHeapAlloc: pMemBlk->free_x = %d\n", 
                   pMemBlk->free_x);
   RTMEMDIAGSTRM2 ("~D rtxMemHeapAlloc: pMemBlk->size = %d\n", 
                   pMemBlk->nunits * 8u);
   RTMEMDIAGSTRM2 ("~I rtxMemHeapAlloc: mem_p = 0x%x\n", mem_p);

   RTMEMDIAGSTRM1 ("~D rtxMemHeapAlloc: end\n\n");

   return (mem_p);
}

static OSBOOL isInMemBlock 
(OSMemBlk* pMemBlk, void* mem_p, OSMemElemDescr** ppMemElem)
{
   if (mem_p >= (void*)pMemBlk->data && 
       mem_p <= (void*)(((OSOCTET*)pMemBlk->data) + pMemBlk->nunits * 8u))
   {
      if (0 != ppMemElem) {
         /* Check if the pointer is a correct element in the mem page. 
            If this is the case, ppMemElem will be set. */
         void* curMem_p;
         OSMemElemDescr* pElem = (OSMemElemDescr*) pMemBlk->data;

         *ppMemElem = 0;

         for (; pElem != 0; pElem = GETNEXT (pElem)) {
            curMem_p = (void*) pElem_data (pElem);
            if (curMem_p == mem_p) {
               *ppMemElem = pElem;
               break;
            }
         }
      }
      return TRUE; /* element is in this block */
   }
   return FALSE;
}

EXTRTMETHOD void* rtxMemHeapAlloc (void** ppvMemHeap, size_t nbytes)
{   
   OSMemLink* pMemLink;
   return memHeapAlloc (ppvMemHeap, nbytes, &pMemLink);
}

EXTRTMETHOD int rtxMemHeapAutoPtrUnref (void** ppvMemHeap, void* mem_p) 
{
   OSMemHeap* pMemHeap;
   OSMemLink** ppMemLink;
   OSMemElemDescr* pElem = 0;
   OSMemBlk* pMemBlk;
   OSMemLink* pMemLink, *pPrevMemLink = 0;

   if (mem_p == 0 || ppvMemHeap == 0 || *ppvMemHeap == 0) return RTERR_NULLPTR;

   pMemHeap = *(OSMemHeap**)ppvMemHeap;
   ppMemLink = &pMemHeap->phead;

   /* look for chain of RAW blocks first */

   for (pMemLink = *ppMemLink; pMemLink != 0; pMemLink = pMemLink->pnext) {
      if ((pMemLink->blockType & RTMEMRAW) && pMemLink->pMemBlk == mem_p) {
         if (pMemLink->refcnt == 0) {
            RTMEMDIAGSTRM2 ("~E rtxMemHeapAutoPtrUnref(0x%x): "
                            "raw element has zero refcnt\n", mem_p);
            return RTERR_INVPARAM;   
         }
         
         if (--(pMemLink->refcnt) > 0) {
            RTMEMDIAGSTRM3 ("~I rtxMemHeapAutoPtrUnref(0x%x): "
                            "raw element refcnt decremented to %d\n", 
                            mem_p, pMemLink->refcnt);
            return pMemLink->refcnt;
         }
         if(pMemLink->pnext != 0) {
            pMemLink->pnext->pprev = pMemLink->pprev;
         }
         if(pMemLink->pprev != 0) {
            pMemLink->pprev->pnext = pMemLink->pnext;
         }
         else { /* head */
            *ppMemLink = pMemLink->pnext;
         }
         if (pPrevMemLink != 0)
            pPrevMemLink->pnextRaw = pMemLink->pnextRaw;
         else if (*ppMemLink != 0 && (*ppMemLink)->pnextRaw == 0 && 
            *ppMemLink != pMemLink->pnextRaw)
         {
            (*ppMemLink)->pnextRaw = pMemLink->pnextRaw;
         }
         if ((pMemLink->blockType & RTMEMLINK) && 
             (pMemLink->blockType & RTMEMMALLOC))
         {
            _g_free_func (ppvMemHeap, pMemLink);
         }
         else {
            if (pMemLink->blockType & RTMEMMALLOC)
               _g_free_func (ppvMemHeap, pMemLink->pMemBlk);
            _g_free_func (ppvMemHeap, pMemLink);
         }
         RTMEMDIAGSTRM2 ("~I rtxMemHeapAutoPtrUnref(0x%x): "
                         "raw element freed\n", mem_p);
         return 0;
      }
      else if (isInMemBlock ((OSMemBlk*)pMemLink->pMemBlk, mem_p, &pElem)) {
         break;
      }

      pPrevMemLink = pMemLink;
   }

   if (0 == pElem || 0 == pMemLink) {
      RTMEMDIAGSTRM2 
         ("~E rtxMemHeapAutoPtrUnref(0x%x): invalid pointer\n", mem_p);
      return RTERR_INVPARAM;
   }
   if (ISFREE (pElem)) { /* already freed! */
      RTMEMDIAGSTRM2 
         ("~E rtxMemHeapAutoPtrUnref(0x%x): pointer already freed\n", mem_p);
      return RTERR_INVPARAM;   
   }
   
   if (pElem_refcnt (pElem) == 0) {
      RTMEMDIAGSTRM2 
         ("~E rtxMemHeapAutoPtrUnref(0x%x): pointer has zero refcnt\n", mem_p);
      return RTERR_INVPARAM;   
   }

   pElem_refcnt (pElem)--;

   if (pElem_refcnt (pElem) > 0) {
      RTMEMDIAGSTRM3 
         ("~I rtxMemHeapAutoPtrUnref(0x%x): refcnt decremented to %d\n", 
          mem_p, pElem_refcnt(pElem));

      return pElem_refcnt (pElem);
   }

   pMemBlk = (OSMemBlk*)pMemLink->pMemBlk;

   if (ISSAVED (pElem)) {
      CLEAR_SAVED (pMemBlk, pElem);
      if (pMemBlk->nsaved == 0)
         pMemBlk->plink->blockType &= (OSOCTET)(~RTMEMSAVED);
   }

   TRACEMEMELEM(pMemBlk, pElem, "Freed");
   CHECKMEMELEM (pMemBlk, pElem);
   CHECKMEMBLOCK(pMemHeap, pMemBlk);

   RTMEMDIAGSTRM2 ("~D rtxMemHeapFreePtr: pMemBlk = 0x%x\n", pMemBlk);
   RTMEMDIAGSTRM2 ("~D rtxMemHeapFreePtr: pMemBlk->size = %d\n", 
                    pMemBlk->nunits * 8u);

   if (ISLAST (pElem)) { /* is it the last? */
      OSMemElemDescr* pPrevElem = GETPREV (pElem);
      
      CHECKMEMELEM (pMemBlk, pPrevElem);

      pMemBlk->free_x = 
         (OSUINT16)(pMemBlk->free_x - (pElem_nunits (pElem) + 1));

      FILLFREEMEM (&pMemBlk->data [pMemBlk->free_x * 8u], 
         (pElem_nunits (pElem) + 1) * 8u);

      if (pPrevElem != 0 && ISFREE (pPrevElem)) {
         OSMemElemDescr* pFreeElem;

         pMemBlk->free_x = 
            (OSUINT16)(pMemBlk->free_x - (pElem_nunits (pPrevElem) + 1));
         pMemBlk->freeMem = 
            (OSUINT16)(pMemBlk->freeMem - (pElem_nunits (pPrevElem)));
         SET_LAST_ELEM (pMemBlk, GETPREV (pPrevElem));
         
         /* wasn't it the last elem in block? */
         if (pMemBlk->lastElemOff != 0) { 
            
            /* correct nextFreeOff for previous free element */

            pFreeElem = GET_FREE_ELEM (pMemBlk);
            if (pFreeElem == pPrevElem) {
               pMemBlk->freeElemOff = 0; /* it was the last free elem */
            }
            else if (0 != pFreeElem) {
               OSMemElemDescr* pNextFree = 0;
               
               while (0 != pFreeElem && pFreeElem < pPrevElem) {
                  pNextFree = pFreeElem;
                  pFreeElem = GET_NEXT_FREE (pFreeElem);
               }
               pElem_nextFreeOff (pNextFree) = 0;
            }
         }
      }
      else {
         SET_LAST_ELEM (pMemBlk, pPrevElem);
      }

      RTMEMDIAGSTRM2 ("~D rtxMemHeapFreePtr: pMemBlk->free_x = %d\n", 
                       pMemBlk->free_x);

      /* The question is: do we really want to get rid of the   */
      /* block or should we keep it around for reuse?           */
      if (pMemBlk->lastElemOff == 0) { /* was it the last elem in block? */
         
         if ((pMemHeap->flags & RT_MH_DONTKEEPFREE) ||
             (pMemHeap->keepFreeUnits > 0 && 
              pMemHeap->freeUnits + pMemBlk->nunits > pMemHeap->keepFreeUnits))
         {
            OSOCTET blockType = pMemBlk->plink->blockType;

            /* we may free the block */

            pMemHeap->usedUnits -= pMemBlk->nunits;
            pMemHeap->usedBlocks --;

            if(pMemBlk->plink->pnext != 0) {
               pMemBlk->plink->pnext->pprev = pMemBlk->plink->pprev;
            }
            if(pMemBlk->plink->pprev != 0) {
               pMemBlk->plink->pprev->pnext = pMemBlk->plink->pnext;
            }
            else { /* head */
               if (pMemBlk->plink->pnext != 0 && 
                   !(pMemBlk->plink->pnext->blockType & RTMEMRAW))
               {
                  pMemBlk->plink->pnext->pnextRaw = (*ppMemLink)->pnextRaw;
               }
               *ppMemLink = pMemBlk->plink->pnext;
            }
            FILLFREEMEM (pMemBlk->plink, sizeof (*pMemBlk->plink));
            FILLFREEMEM (pMemBlk->data, (pMemBlk->nunits * 8u));
         
            _g_free_func (ppvMemHeap, pMemBlk->plink);
            
            if (!(blockType & RTMEMLINK)) {
               FILLFREEMEM (pMemBlk, sizeof (*pMemBlk));
               _g_free_func (ppvMemHeap, pMemBlk);
            }
            RTMEMDIAGSTRM2 
               ("~D rtxMemHeapFreePtr: pMemBlk = 0x%x was freed\n", pMemBlk);
         }
         else {
            /* reset pMemBlk for re-usage */
            pMemBlk->free_x = 0;
            pMemBlk->freeElemOff = 0;
            pMemBlk->lastElemOff = 0;
            pMemBlk->freeMem = 0;
            pMemBlk->nsaved = 0;
            pMemHeap->freeUnits += pMemBlk->nunits;
            pMemHeap->freeBlocks ++;
         }
      }
      else {
         SET_LAST (GET_LAST_ELEM (pMemBlk));
         FILLFREEMEM (((char*) &pMemBlk->data[0]) + (pMemBlk->free_x * 8u), 
                      (pMemBlk->nunits - pMemBlk->free_x) * 8u);
         CHECKMEMBLOCK (pMemHeap, pMemBlk);
      }
   }
   else { /* mark as free elem inside the block */
      CHECKMEMBLOCK (pMemHeap, pMemBlk);

      SET_FREE_ELEM(pMemBlk, pElem);

      pMemBlk->freeMem = (OSUINT16)(pMemBlk->freeMem + (pElem_nunits (pElem)));
      RTMEMDIAGSTRM2 
         ("~D rtxMemHeapFreePtr: element 0x%x marked as free.\n", pElem);

      /* try to unite free blocks, if possible */
      if (!ISFIRST (pElem)) {
         if (ISFREE (GETPREV (pElem))) {
            OSMemElemDescr* prevelem_p = GETPREV (pElem);
         
            /* +1 because the OSMemElemDescr has size ONE unit (8 bytes) */
            pElem_nunits (prevelem_p) = (OSUINT16)
               (pElem_nunits (prevelem_p) + (pElem_nunits (pElem) + 1));

            pElem = prevelem_p;
            pMemBlk->freeMem ++; /* sizeof (OSMemElemDescr) == 1 unit */
         }
         else {
            /* look for nearest previous free block to correct nextFreeOff */
         
            OSMemElemDescr* prevelem_p = pElem;
         
            do {
               prevelem_p = GETPREV (prevelem_p);
            }
            while (prevelem_p && !ISFREE (prevelem_p));

            if (prevelem_p != 0) {
               OSMemElemDescr* pNextFree =  GET_NEXT_FREE (prevelem_p);
               if (pNextFree != 0) 
                  pElem_nextFreeOff (pElem) = QOFFSETOF (pNextFree, pElem);
               else
                  pElem_nextFreeOff (pElem) = 0;
               pElem_nextFreeOff (prevelem_p) = QOFFSETOF (pElem, prevelem_p);
         
               CHECKMEMELEM (pMemBlk, prevelem_p);
            }
         }
      }
      if (!ISLAST (pElem) && ISFREE (GETNEXT (pElem))) {
         OSMemElemDescr* nextelem_p = GETNEXT (pElem);
         
         /* +1 because the OSMemElemDescr has size ONE unit (8 bytes) */
         pElem_nunits (pElem) = 
            (OSUINT16)(pElem_nunits (pElem) + (pElem_nunits (nextelem_p) + 1));

         if (pElem_nextFreeOff (nextelem_p) == 0)
            pElem_nextFreeOff (pElem) = 0;
         else
            pElem_nextFreeOff (pElem) = 
               QOFFSETOF (GET_NEXT_FREE (nextelem_p), pElem);
         pMemBlk->freeMem ++;
      }

      /* correct the prevOff field of next element */
      if (!ISLAST (pElem)) {  
         OSMemElemDescr* nextelem_p = GETNEXT (pElem);
         pElem_prevOff (nextelem_p) = QOFFSETOF (nextelem_p, pElem);
      }

      CHECKMEMELEM (pMemBlk, pElem);
      FILLFREEMEM (pElem_data (pElem), (pElem_nunits (pElem) * 8u));
      CHECKMEMELEM (pMemBlk, pElem);
      CHECKMEMBLOCK (pMemHeap, pMemBlk);
   }

   return 0;
} 

EXTRTMETHOD void rtxMemHeapFreePtr (void** ppvMemHeap, void* mem_p) 
{
   RTMEMDIAGSTRM2 ("~D rtxMemHeapFreePtr: try free mem_p = 0x%x\n", mem_p);
   rtxMemHeapAutoPtrUnref (ppvMemHeap, mem_p);
}

static void initNewFreeElement (OSMemBlk* pMemBlk, 
   OSMemElemDescr* pNewElem, OSMemElemDescr* pElem) 
{
   OSMemElemDescr *pNextElem, *pPrevElem = 0;

   /* create new free element on the freed place */

   pElem_flags (pNewElem) = 0;
   pElem_refcnt (pNewElem) = 0;
   SET_FREE (pNewElem);

   pElem_prevOff (pNewElem) = QOFFSETOF (pNewElem, pElem);

   if (pMemBlk->freeElemOff != 0 && 
      pMemBlk->freeElemOff < QOFFSETOF (pElem, pMemBlk->data) + 1)
   {
      /* look for nearest previous free block to correct its nextFreeOff */
      
      pPrevElem = pElem;

      do {
         pPrevElem = GETPREV (pPrevElem);
      }
      while (pPrevElem && !ISFREE (pPrevElem));
   }
   if (pPrevElem != 0) { /* if it is not first free element... */

      /* correct nextFreeOff for prev free element */
      
      pElem_nextFreeOff (pPrevElem) = QOFFSETOF (pNewElem, pPrevElem);
   }
   else {  /* if it is first free element in the block */
      FORCE_SET_FREE_ELEM (pMemBlk, pNewElem);
   }
   
   pNextElem = GETNEXT (pNewElem);
   if (ISFREE (pNextElem)) {
      
      /* if the next elem is free, then unite them together */

      pElem_nunits (pNewElem) = (OSUINT16)
         (pElem_nunits (pNewElem) + (pElem_nunits (pNextElem) + 1));
      if (pElem_nextFreeOff (pNextElem) != 0)
         pElem_nextFreeOff (pNewElem) = QOFFSETOF (GET_NEXT_FREE (pNextElem), 
            pNewElem);
      else
         pElem_nextFreeOff (pNewElem) = 0;
      pMemBlk->freeMem++; /* +1 because space for MemElemDescr is freed now */
      pNextElem = GETNEXT (pNewElem);
   }
   pElem_prevOff (pNextElem) = QOFFSETOF (pNextElem, pNewElem);

   if (pMemBlk->freeElemOff != 0) {

      /* look for the next nearest free elem */

      pNextElem = GETNEXT (pNewElem);
      while (pNextElem != 0 && !ISFREE (pNextElem))
         pNextElem = GETNEXT (pNextElem);

      /* set nextFreeOff for new element */
   
      if (pNextElem != 0)
         pElem_nextFreeOff (pNewElem) = QOFFSETOF (pNextElem, pNewElem);
      else
         pElem_nextFreeOff (pNewElem) = 0;
   }
   else
      pElem_nextFreeOff (pNewElem) = 0;

}

EXTRTMETHOD void* rtxMemHeapRealloc 
(void** ppvMemHeap, void* mem_p, size_t nbytes_)
{
   OSMemHeap* pMemHeap;
   OSMemLink** ppMemLink;
   OSMemBlk* pMemBlk;
   OSMemElemDescr* pElem;
   OSMemLink* pMemLink;
   void *newMem_p;
   OSUINT32 nbytes, nunits;
   OSUINT8  refcnt;

   /* if mem_p == NULL - do rtxMemAlloc */

   if (ppvMemHeap == 0 || *ppvMemHeap == 0) return 0;

   if (mem_p == 0) {
      return rtxMemHeapAlloc (ppvMemHeap, nbytes_);
   }

   pMemHeap = *(OSMemHeap**)ppvMemHeap;
   ppMemLink = &pMemHeap->phead;

   /* look for chain of RAW blocks first */

   for (pMemLink = *ppMemLink; pMemLink != 0; pMemLink = pMemLink->pnextRaw) {
      if ((pMemLink->blockType & RTMEMRAW) &&
           pMemLink->pMemBlk == mem_p) 
      {
         if (pMemLink->blockType & RTMEMMALLOC)
            if (is_realloc_available()) {
               void* newMemBlk;
               RTMEMDIAGSTRM3 
                  ("~I rtxMemHeapRealloc: realloc raw block %x, nbytes = %d\n",
                   pMemLink->pMemBlk, nbytes_);

               newMemBlk = 
                  _g_realloc_func (ppvMemHeap, pMemLink->pMemBlk, nbytes_);

               if (newMemBlk == 0) 
                  return 0;

               pMemLink->pMemBlk = newMemBlk;
            }
            else {
               /* use malloc/OSCRTLMEMCPY/free sequence instead of realloc */
               OSOCTET* newBuf;
               OSRawMemLink* pRawMemLink = (OSRawMemLink*) pMemLink;
               size_t oldSize = pRawMemLink->memsize;
               if (oldSize == (size_t)-1) return 0;

               newBuf = (OSOCTET*)_g_malloc_func (ppvMemHeap, nbytes_);
               if (newBuf == 0) return 0;

               OSCRTLMEMCPY (newBuf, pMemLink->pMemBlk, 
                             OSRTMIN (oldSize, nbytes_));

               _g_free_func (ppvMemHeap, pMemLink->pMemBlk);
               pMemLink->pMemBlk = newBuf;
            }
         else 
            return 0;

         ((OSRawMemLink*)pMemLink)->memsize = nbytes_;

         return pMemLink->pMemBlk;
      }
   }

   /* Round number of bytes to nearest 8-byte boundary */

   nbytes = ((OSUINT32)(nbytes_ + 7)) & (~7u);
   nunits = nbytes >> 3;

   pElem = (OSMemElemDescr*) (((char*)mem_p) - sizeof_OSMemElemDescr);

   RTMEMDIAGSTRM4 
      ("~I rtxMemHeapRealloc: mem_p = 0x%x, old size = %d, new size %d\n",  
       mem_p, pElem_nunits (pElem) * 8u, nbytes);

   if ((OSUINT32)pElem_nunits (pElem) == nunits)
      return mem_p;

   pMemBlk = GET_MEMBLK (pElem);

   CHECKMEMELEM (pMemBlk, pElem);
   CHECKMEMBLOCK(pMemHeap, pMemBlk);

   if ((OSUINT32)pElem_nunits (pElem) < nunits) { /* expanding */
   
      if (nunits - pElem_nunits (pElem) <= (OSUINT32)pMemBlk->nunits) {

         /* Try to expand the existing element in the existing block */

         if (ISLAST (pElem)) { /* if the last element in the block */
         
            /* if the free space in the block is enough */
         
            if ((int)(nunits - pElem_nunits (pElem)) <= 
                (int)(pMemBlk->nunits - pMemBlk->free_x)) 
            { 
               pMemBlk->free_x = (OSUINT16)
                  (pMemBlk->free_x + (nunits - pElem_nunits (pElem)));
               pElem_nunits (pElem) = (OSUINT16)nunits;

               RTMEMDIAGSTRM1 ("~I rtxMemHeapRealloc: "
                               "memory element is expanded.\n");
               
               FILLNEWMEM (&pMemBlk->data [(pMemBlk->free_x - 
                  (nunits - pElem_nunits (pElem))) * 8u], 
                  (nunits - pElem_nunits (pElem)) * 8u);
               
               TRACEMEMELEM (pMemBlk, pElem, "Reallocated");
               CHECKMEMELEM (pMemBlk, pElem);
               CHECKMEMBLOCK (pMemHeap, pMemBlk);

               return (mem_p);
            } 
         }
         else {
            OSMemElemDescr* pNextElem, *pFreeElem; 
            unsigned sumSize = pElem_nunits (pElem), freeMem = 0;
         
            RTMEMDIAGSTRM1 ("~I rtxMemHeapRealloc: look for free element "
                            "after current block.\n");

            /* look for free element after pElem */

            pNextElem = GETNEXT (pElem);
            if (ISFREE (pNextElem)) {
               /* +1 'cos sizeof (OSMemElemDescr) == 1 unit */
               sumSize += pElem_nunits (pNextElem) + 1; 
               freeMem++;
            }
            
            if (sumSize >= nunits) {

               RTMEMDIAGSTRM1 ("~I rtxMemHeapRealloc: reuse free element.\n");

               if (ISFREE (pNextElem)) {
                  pFreeElem = GET_FREE_ELEM (pMemBlk);
                  if (pFreeElem == pNextElem) {
                     FORCE_SET_FREE_ELEM (pMemBlk, GET_NEXT_FREE (pNextElem));
                  }
                  else if (pFreeElem < pElem) {
                     
                     /* look for previous free elem to correct nextFreeOff */

                     for (; pFreeElem != 0 && pFreeElem < pNextElem;) {
                        OSMemElemDescr* pNextFreeElem = 
                           GET_NEXT_FREE (pFreeElem);
                        if (pNextFreeElem == pNextElem) {
                           if (pElem_nextFreeOff (pNextElem) != 0)
                              pElem_nextFreeOff (pFreeElem) = QOFFSETOF 
                                 (GET_NEXT_FREE (pNextElem), pFreeElem);
                           else
                              pElem_nextFreeOff (pFreeElem) = 0;
                           CHECKMEMELEM (pMemBlk, pFreeElem);
                           break;
                        }
                        pFreeElem = pNextFreeElem;
                     }
                  }
               }

               /* reuse empty elements after the pElem */
               
               pMemBlk->freeMem = (OSUINT16)(pMemBlk->freeMem + freeMem);
     
               if (sumSize - nunits > 1) {
                  OSMemElemDescr* pNewElem;
               
                  /* if sumSize is too large, then create new empty element */

                  pNewElem = (OSMemElemDescr*) 
                     (pElem_data (pElem) + nbytes);
                  pElem_nunits (pNewElem) = (OSUINT16)(sumSize - nunits - 1);

                  initNewFreeElement (pMemBlk, pNewElem, pElem);

                  pMemBlk->freeMem--; /* sizeof (OSMemElemDescr) == 1 unit */
                  pMemBlk->freeMem = (OSUINT16)
                     (pMemBlk->freeMem - (nunits - pElem_nunits (pElem)));
                  pElem_nunits (pElem) = (OSUINT16)nunits;
               }
               else {
                  pMemBlk->freeMem = (OSUINT16)
                     (pMemBlk->freeMem - (sumSize - pElem_nunits (pElem)));
                  pElem_nunits (pElem) = (OSUINT16)sumSize;

                  /* modify the prevOff of the next elem */

                  pNextElem = GETNEXT (pElem);
                  if (pNextElem != 0)
                     pElem_prevOff (pNextElem) = QOFFSETOF (pNextElem, pElem);
               }
               
               TRACEMEMELEM (pMemBlk, pElem, "Reallocated");
               CHECKMEMELEM (pMemBlk, pElem);
               CHECKMEMELEM (pMemBlk, (!ISLAST (pElem)) ? GETNEXT (pElem) : 0);
               CHECKMEMBLOCK (pMemHeap, pMemBlk);
               return (mem_p);
            }
         }
      }

      /* If not successful, allocate a new element and move the data into it */

      RTMEMDIAGSTRM2 
         ("~I rtxMemHeapRealloc: allocate new memory (%d bytes)...\n", nbytes);

      CHECKMEMHEAP (pMemHeap);

      newMem_p = memHeapAlloc (ppvMemHeap, nbytes, &pMemLink);
      
      if (newMem_p == 0)
         return 0;

      /* if the old memory block is marked as saved then mark the new block
         as saved as well. */

      if (ISSAVED (pElem)) 
         rtxMemHeapMarkSaved (ppvMemHeap, newMem_p, TRUE);

      CHECKMEMHEAP (pMemHeap);

      { OSUINT32 nbytes2 = (((OSUINT32)pElem_nunits (pElem)) * 8u);
      RTMEMDIAGSTRM2 
         ("~I rtxMemHeapRealloc: copy %d bytes to new memory..\n", nbytes2);
      OSCRTLMEMCPY (newMem_p, mem_p, nbytes2);
      }
      /* free old element */

      RTMEMDIAGSTRM1 ("~D rtxMemHeapRealloc: free old pointer...\n");

      /* correct refcnts */
      refcnt = pElem_refcnt (pElem);
      pElem_refcnt (pElem) = 1;

      /* If raw block, no OSMemElemDescr will be present (ED, 5/1/08) */
      if (! (pMemLink->blockType & RTMEMRAW) ) {
         pElem = (OSMemElemDescr*) (((char*)newMem_p) - sizeof_OSMemElemDescr);
         pElem_refcnt (pElem) = refcnt;
      }

      if (refcnt > 1) {
         /* block with */
         RTMEMDIAGSTRM1 ("~I rtxMemHeapRealloc: "
                         "not single referenced block moved...\n");
      }
      
      rtxMemHeapFreePtr (ppvMemHeap, mem_p);

      CHECKMEMHEAP (pMemHeap);

      return (newMem_p);
   }
   else { /* shrinking */
      RTMEMDIAGSTRM1 ("~I rtxMemHeapRealloc: shrinking ...\n");
      
      /* just free the pointer, if nbytes == 0 */

      if (nbytes == 0) {
         RTMEMDIAGSTRM1 ("~I rtxMemHeapRealloc: free pointer...\n");
         rtxMemHeapFreePtr (ppvMemHeap, mem_p);
         return (NULL);
      }

      /* do not shrink, if size diff is too small */

      /* sizeof (OSMemElemDescr) == 1 unit */
      if (pElem_nunits (pElem) - nunits > 1) { 
         
         /* if it is the last element in the block, then just change the size 
            and free_x. */

         if (ISLAST (pElem)) {
            pMemBlk->free_x = (OSUINT16)
               (pMemBlk->free_x - (pElem_nunits (pElem) - nunits));

            FILLFREEMEM (&pMemBlk->data [pMemBlk->free_x * 8u], 
               (pElem_nunits (pElem) - nunits) * 8u);
         }
         else {
            OSMemElemDescr* pNewElem;

            /* create new free element on the freed place */

            pNewElem = (OSMemElemDescr*) (pElem_data (pElem) + nbytes);

            /* sizeof (OSMemElemDescr) == 1 unit */
            pElem_nunits (pNewElem) = 
               (OSUINT16)(pElem_nunits (pElem) - nunits - 1); 
            
            initNewFreeElement (pMemBlk, pNewElem, pElem);
            
            pMemBlk->freeMem = (OSUINT16)
               (pMemBlk->freeMem + ((pElem_nunits (pElem) - nunits) - 1));
         }
         pElem_nunits (pElem) = (OSUINT16)nunits;
         
         TRACEMEMELEM (pMemBlk, pElem, "Reallocated");
         CHECKMEMELEM (pMemBlk, pElem);
         CHECKMEMELEM (pMemBlk, (!ISLAST (pElem)) ? GETNEXT (pElem) : pElem);
         CHECKMEMBLOCK (pMemHeap, pMemBlk);
      }
      return (mem_p);
   }
}

/* Clears heap memory (frees all memory, reset all heap's variables) */
EXTRTMETHOD void rtxMemHeapFreeAll (void** ppvMemHeap)
{
   OSMemHeap* pMemHeap;
   OSMemLink* pMemLink;
   OSMemLink* pMemLink2;

   if (ppvMemHeap == 0 || *ppvMemHeap == 0) return;
   pMemHeap = *(OSMemHeap**)ppvMemHeap;

   pMemLink = pMemHeap->phead;
   RTMEMDIAGSTRM2 ("~D rtxMemHeapFreeAll: pMemHeap = 0x%x\n", pMemHeap);

   TRACEFREE (pMemHeap, "rtxMemHeapFreeAll\n\n");
   CHECKMEMHEAP (pMemHeap);

   /* Release any dynamic memory blocks that may have been allocated */

   while (pMemLink) {
      pMemLink2 = pMemLink;
      pMemLink  = pMemLink2->pnext;

      RTMEMDIAGSTRM3 ("~D rtxMemHeapFreeAll: pMemLink2 = 0x%x, "
                      "pMemLink = 0x%x\n", pMemLink2, pMemLink);

      if (!(pMemLink2->blockType & RTMEMSAVED)) {
         OSMemBlk* pMemBlk = (OSMemBlk*) pMemLink2->pMemBlk;

         /* unlink block first */

         if(pMemLink2->pnext != 0) {
            pMemLink2->pnext->pprev = pMemLink2->pprev;
         }
         if(pMemLink2->pprev != 0) {
            pMemLink2->pprev->pnext = pMemLink2->pnext;
         }
         else { /* head */
            pMemHeap->phead = pMemLink2->pnext;
         }

         /* correct heap's variables */

         pMemHeap->usedUnits -= pMemBlk->nunits;

         if (pMemBlk->free_x == 0)
            pMemHeap->freeBlocks --;
         else
            pMemHeap->usedBlocks --;

         /* free link and block */

         if (((pMemLink2->blockType & RTMEMSTD) || 
              (pMemLink2->blockType & RTMEMMALLOC)) &&
              !(pMemLink2->blockType & RTMEMLINK)) {
            OSMemBlk* pMemBlk = (OSMemBlk*) pMemLink2->pMemBlk;
#ifdef _MEMDEBUG
            if (pMemLink2->blockType & RTMEMRAW) {
               FILLFREEMEM (pMemBlk, ((OSRawMemLink*)pMemLink2)->memsize);
            } else {
               FILLFREEMEM (pMemBlk->data, (pMemBlk->nunits * 8u));
               FILLFREEMEM (pMemBlk, sizeof (*pMemBlk));
            }
#endif
            _g_free_func (ppvMemHeap, pMemBlk);
         }
#ifdef _MEMDEBUG
         FILLFREEMEM (pMemLink2, sizeof (*pMemLink2));
#endif
         _g_free_func (ppvMemHeap, pMemLink2);
      }
   }
}

/* increments internal refCnt. use rtxMemHeapRelease to decrement and release */
EXTRTMETHOD void rtxMemHeapAddRef (void** ppvMemHeap)
{
   OSMemHeap* pMemHeap;

   if (ppvMemHeap == 0 || *ppvMemHeap == 0) return;
   pMemHeap = *(OSMemHeap**)ppvMemHeap;
   pMemHeap->refCnt++;
}

/* Frees all memory and heap structure as well (if was allocated) */
EXTRTMETHOD void rtxMemHeapRelease (void** ppvMemHeap)
{
   OSMemHeap** ppMemHeap = (OSMemHeap**)ppvMemHeap;

   if (ppMemHeap != 0 && *ppMemHeap != 0 && --(*ppMemHeap)->refCnt == 0) {
      OSMemLink* pMemLink, *pMemLink2;

      rtxMemHeapFreeAll (ppvMemHeap);

      /* if there are RTMEMSAVED blocks - release memory for links only */

      pMemLink = (*ppMemHeap)->phead;
      while (pMemLink) {
         pMemLink2 = pMemLink;
         pMemLink  = pMemLink2->pnext;

         _g_free_func (ppvMemHeap, pMemLink2);
      }

      if ((*ppMemHeap)->flags & RT_MH_FREEHEAPDESC)
         _g_free_func (ppvMemHeap, *ppMemHeap);
      *ppMemHeap = 0;
   }
}

/* This function is used for marking memory block as "saved". It means
 * that the memory block containing the specified memory pointer won't be
 * freed after calls to rtxMemHeapFreeAll/rtxMemHeapReset. User is 
 * responsible to free the marked memory block by call to rtxMemFreeBlock */

EXTRTMETHOD void* rtxMemHeapMarkSaved 
(void** ppvMemHeap, const void* mem_p, OSBOOL saved) 
{
   OSMemHeap* pMemHeap;
   OSMemLink* pMemLink;
   OSUINT32 nsaved = 1;

   RTMEMDIAGSTRM2 ("~D rtxMemHeapMarkSaved: for mem_p = 0x%x\n", mem_p);

   if (ppvMemHeap == 0 || *ppvMemHeap == 0 || mem_p == 0) 
      return 0;

   pMemHeap = *(OSMemHeap**)ppvMemHeap;
   pMemLink = pMemHeap->phead;

   /* look for chain of RAW blocks first */

   for (; pMemLink != 0; pMemLink = pMemLink->pnextRaw) {
      if ((pMemLink->blockType & RTMEMRAW) &&
           pMemLink->pMemBlk == mem_p) 
      {
         break;
      }
   }
   if (pMemLink == 0) {
      OSMemElemDescr* pElem;
      OSMemBlk* pMemBlk;

      /* gain the MemLink from pointer */

      pElem = (OSMemElemDescr*) (((char*)mem_p) - sizeof_OSMemElemDescr);

      if (ISFREE (pElem)) { /* already freed! */
         RTMEMDIAGSTRM2 ("~E rtxMemHeapMarkSaved: the element 0x%x is "
                         "already free!\n", pElem);
         return 0;   
      }

      if ((ISSAVED (pElem) && !saved) || (!ISSAVED (pElem) && saved)) {

         pMemBlk = GET_MEMBLK (pElem);

         CHECKMEMELEM (pMemBlk, pElem);
         CHECKMEMBLOCK(pMemHeap, pMemBlk);

         pMemLink = pMemBlk->plink;

         if (saved) 
            SET_SAVED (pMemBlk, pElem);
         else
            CLEAR_SAVED (pMemBlk, pElem);
         nsaved = pMemBlk->nsaved;
      }
      else
         return 0;
   }
   if (saved && nsaved > 0) 
      pMemLink->blockType |= RTMEMSAVED;
   else if (nsaved == 0)
      pMemLink->blockType &= (OSOCTET)(~RTMEMSAVED);
   return pMemLink->pMemBlk;
}

/* This function will set the free index in all blocks to zero thereby  */
/* allowing the blocks to be reused (ED, 3/17/2002)..                   */

EXTRTMETHOD void rtxMemHeapReset (void** ppvMemHeap)
{
   OSMemHeap* pMemHeap;
   OSMemLink *pMemLink, *pNextMemLink;

   if (ppvMemHeap == 0 || *ppvMemHeap == 0) return;
   pMemHeap = *(OSMemHeap**)ppvMemHeap;

   pMemLink = pMemHeap->phead;
   TRACEFREE (pMemHeap, "rtxMemHeapReset\n\n");
   while (pMemLink) {
      pNextMemLink = pMemLink->pnext;
      if (!(pMemLink->blockType & RTMEMSAVED)) {
         if (pMemLink->blockType & RTMEMSTD) {
            OSMemBlk* pMemBlk = (OSMemBlk*) pMemLink->pMemBlk;
            if (pMemBlk->free_x != 0) {
               pMemHeap->freeUnits += pMemBlk->nunits;
               pMemHeap->freeBlocks ++;
            }
            pMemBlk->free_x = 0;
            pMemBlk->freeElemOff = 0;
            pMemBlk->lastElemOff = 0;
            pMemBlk->freeMem = 0;
            FILLFREEMEM (pMemBlk->data, pMemBlk->nunits * 8u);
         }
         else if (pMemLink->blockType & RTMEMRAW) {
            /* if RAW block - free it */
            rtxMemHeapFreePtr (ppvMemHeap, pMemLink->pMemBlk);
         }
      }
      pMemLink = pNextMemLink;
   }
}

/* add memory block to list */

static OSMemLink* rtxMemHeapAddBlock (OSMemLink** ppMemLink, 
                                      void* pMemBlk, int blockType)
{
   OSMemLink* pMemLink;

   /* if pMemBlk has RTMEMLINK flags it means that it is allocated 
    * cooperatively with OSMemLink, and we don't need to do additional
    * allocations for it. Just use pointer's arithemtic. */

   if (blockType & RTMEMLINK) 
      pMemLink = (OSMemLink*) (((OSOCTET*)pMemBlk) - sizeof (OSMemLink));
   else {
      pMemLink = (OSMemLink*) 
         _g_malloc_func (ppvMemHeap, sizeof(OSRawMemLink));

      if (pMemLink != 0) {
         /* An extra integer is necessary to save size of a RAW memory block
            to perform rtxMemRealloc through malloc/OSCRTLMEMCPY/free */
         ((OSRawMemLink*)pMemLink)->memsize = (size_t)-1;
      }
   }
   if (pMemLink == NULL) 
      return NULL;

   pMemLink->blockType = (OSUINT8)blockType;
   pMemLink->refcnt = 1;
   pMemLink->pMemBlk = pMemBlk;
   pMemLink->pprev = 0;
   pMemLink->pnext = *ppMemLink;

   if (*ppMemLink != 0) {
      if ((*ppMemLink)->blockType & RTMEMRAW)
         pMemLink->pnextRaw = *ppMemLink;
      else {
         pMemLink->pnextRaw = (*ppMemLink)->pnextRaw;
         (*ppMemLink)->pnextRaw = 0;
      }
   }
   else {
      pMemLink->pnextRaw = 0;
   }

   *ppMemLink = pMemLink; 

   if (pMemLink->pnext != 0)
      pMemLink->pnext->pprev = pMemLink;

   ((OSMemBlk*)pMemBlk)->plink = pMemLink;

   RTMEMDIAGSTRM2 ("~I rtxMemHeapAddBlock: pMemLink = 0x%x\n", pMemLink);
   RTMEMDIAGSTRM2 ("~I rtxMemHeapAddBlock: pMemLink->pnext = 0x%x\n", 
                    pMemLink->pnext);
   RTMEMDIAGSTRM2 ("~I rtxMemHeapAddBlock: pMemLink->pprev = 0x%x\n", 
                    pMemLink->pprev);

   return pMemLink;
}

EXTRTMETHOD int rtxMemHeapCheckPtr (void** ppvMemHeap, void* mem_p)
{
   OSMemHeap* pMemHeap;
   OSMemLink* pMemLink;

   RTMEMDIAGSTRM2 ("~D rtxMemHeapCheckPtr: for mem_p = 0x%x\n", mem_p);

   if (ppvMemHeap == 0 || *ppvMemHeap == 0 || mem_p == 0) 
      return 0;
   pMemHeap = *(OSMemHeap**)ppvMemHeap;

   pMemLink = pMemHeap->phead;

   for (; pMemLink != 0; pMemLink = pMemLink->pnext) {
      if (pMemLink->blockType & RTMEMRAW) {
         
         /* if RAW block, the pointer should be stored in pMemBlk */

         if (pMemLink->pMemBlk == mem_p) 
            return 1;
      }
      else {
         OSMemElemDescr* pElem = 0;
         if (isInMemBlock ((OSMemBlk*)pMemLink->pMemBlk, mem_p, &pElem)) {
            if (0 != pElem && !ISFREE (pElem)) {
               return 1;
            }
            else break;
         }
      }
   }
   return 0;
}

void* rtxMemHeapAutoPtrRef (void** ppvMemHeap, void* mem_p)
{
   OSMemHeap* pMemHeap;
   OSMemLink** ppMemLink;
   OSMemElemDescr* pElem = 0;
   OSMemLink* pMemLink /*, *pPrevMemLink = 0 */;

   if (mem_p == 0 || ppvMemHeap == 0 || *ppvMemHeap == 0) return 0;

   pMemHeap = *(OSMemHeap**)ppvMemHeap;
   ppMemLink = &pMemHeap->phead;

   for (pMemLink = *ppMemLink; pMemLink != 0; pMemLink = pMemLink->pnext) {
      if ((pMemLink->blockType & RTMEMRAW) && pMemLink->pMemBlk == mem_p) {
         if (pMemLink->refcnt == 255) {
            RTMEMDIAGSTRM2 ("~E rtxMemHeapAutoPtrRef(0x%x): "
                            "element has maximum refcnt\n", mem_p);
            return 0;
         }
         ++(pMemLink->refcnt);
         RTMEMDIAGSTRM3 ("~I rtxMemHeapAutoPtrRef(0x%x): refcnt "
                         "incremented to %d\n", mem_p, pMemLink->refcnt);
         return mem_p;
      }
      else if (isInMemBlock ((OSMemBlk*)pMemLink->pMemBlk, mem_p, &pElem)) {
         break;
      }

      /* pPrevMemLink = pMemLink; */
   }

   if (0 == pElem) {
      RTMEMDIAGSTRM2 
         ("~E rtxMemHeapAutoPtrRef(0x%x): invalid pointer\n", mem_p);
      return 0;
   }
   if (ISFREE (pElem)) { /* already freed! */
      RTMEMDIAGSTRM2 
         ("~E rtxMemHeapAutoPtrRef(0x%x): element already freed!\n", mem_p);
      return 0;
   }
   
   if (pElem_refcnt (pElem) == 255) {
      RTMEMDIAGSTRM2 ("~I rtxMemHeapAutoPtrRef(0x%x): "
                      "element has maximum refcnt\n", mem_p);
      return 0;
   }

   pElem_refcnt (pElem)++;

   RTMEMDIAGSTRM3 ("~I rtxMemHeapAutoPtrRef(0x%x): refcnt "
                   "incremented to %d\n", mem_p, pMemLink->refcnt);

   return mem_p;
}

int rtxMemHeapAutoPtrGetRefCount (void** ppvMemHeap, void* mem_p)
{
   OSMemHeap* pMemHeap;
   OSMemLink** ppMemLink;
   OSMemElemDescr* pElem = 0;
   OSMemLink* pMemLink /*, *pPrevMemLink = 0 */;

   if (mem_p == 0 || ppvMemHeap == 0 || *ppvMemHeap == 0) return RTERR_NULLPTR;

   pMemHeap = *(OSMemHeap**)ppvMemHeap;
   ppMemLink = &pMemHeap->phead;

   /* look for chain of RAW blocks first */

   for (pMemLink = *ppMemLink; pMemLink != 0; pMemLink = pMemLink->pnext) {
      if ((pMemLink->blockType & RTMEMRAW) && pMemLink->pMemBlk == mem_p) {
         RTMEMDIAGSTRM3 ("~I rtxMemHeapAutoPtrGetRefCount(0x%x): refcnt "
                         "is %d\n", mem_p, pMemLink->refcnt);

         return (pMemLink->refcnt);
      }
      else if (isInMemBlock ((OSMemBlk*)pMemLink->pMemBlk, mem_p, &pElem)) {
         break;
      }
      /* pPrevMemLink = pMemLink; */
   }

   if (0 != pElem) {
      RTMEMDIAGSTRM3 ("~I rtxMemHeapAutoPtrGetRefCount(0x%x): refcnt "
                      "is %d\n", mem_p, pElem_refcnt(pElem));

      return pElem_refcnt(pElem);
   }
   else {
      RTMEMDIAGSTRM2 
         ("~E rtxMemHeapAutoPtrGetRefCount(0x%x): invalid pointer\n", mem_p);

      return RTERR_NULLPTR;
   }
}
