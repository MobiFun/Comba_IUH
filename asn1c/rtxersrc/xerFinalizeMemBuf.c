#include "asn1xer.h"
#include "rtsrc/asn1intl.h"

int xerFinalizeMemBuf (OSRTMEMBUF* pMemBuf) 
{
   int len, stat;
   OSOCTET* data;
   
   /* Ensure capacity for data */
   stat = rtxMemBufPreAllocate (pMemBuf, sizeof (XMLCHAR));
   if (stat != 0) return LOG_RTERR (pMemBuf->pctxt, stat);

   /* Set termination null */
   memset (&pMemBuf->buffer[pMemBuf->usedcnt], 0, sizeof (XMLCHAR));
   pMemBuf->usedcnt += sizeof (XMLCHAR);

   data = pMemBuf->buffer + pMemBuf->startidx;
   len = pMemBuf->usedcnt - pMemBuf->startidx;

   pMemBuf->pctxt->buffer.data = data;
   pMemBuf->pctxt->buffer.size = len - sizeof (XMLCHAR);
   pMemBuf->pctxt->buffer.dynamic = FALSE;
   pMemBuf->pctxt->buffer.byteIndex = 0;
   pMemBuf->pctxt->buffer.bitOffset = 8;
   
   return 0;
}

