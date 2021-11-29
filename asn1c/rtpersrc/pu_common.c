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

#include "rtpersrc/pu_common.hh"
#include "rtsrc/rt_common.hh"

/***********************************************************************
 *
 *  COMMON UTILITY FUNCTIONS
 *
 **********************************************************************/

/***********************************************************************
 *
 *  Routine name: pu_getMsgLen
 *
 *  Description:  This routine returns the length of the encoded PER
 *                message.  For decoding, this function must be called 
 *                after the decode function is complete to get the 
 *                message length.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct* Pointer to ASN.1 PER context structure
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  length      int     Length of encoded message
 *
 *
 **********************************************************************/

EXTPERMETHOD size_t pu_getMsgLen (OSCTXT* pctxt)
{
   return (pctxt->buffer.bitOffset == 8) ?
      pctxt->buffer.byteIndex : pctxt->buffer.byteIndex + 1;
}

/***********************************************************************
 *
 *  Routine name: pu_setp
 *
 *  Description:  This routine sets up pointers to a user specified buffer
 *                for subsequent low level ASN.1 routine calls.  
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct* Pointer to PER context block structure
 *  bufaddr     uchar*  Pointer to start address of static buffer or
 *                      encoded message
 *  bufsiz      uint    Size of static encode buffer or 
 *                      encoded message length
 *  aligned     bool    PER aligned encoding flag
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat        int     Status of operation
 *
 *
 **********************************************************************/

/* This function turns tracing on or off for the context */

EXTPERMETHOD OSBOOL pu_setTrace (OSCTXT* pCtxt, OSBOOL value)
{
   OSBOOL bTrace = (pCtxt->flags & ASN1TRACE) ? TRUE : FALSE;

   pCtxt->flags = (value) ?
      pCtxt->flags | ASN1TRACE : pCtxt->flags & (OSUINT16)(~ASN1TRACE);

   return bTrace;
}

EXTPERMETHOD int pu_setBuffer (OSCTXT* pctxt,
                  OSOCTET* bufaddr, size_t bufsiz, OSBOOL aligned)
{
   int stat = rtxInitContextBuffer (pctxt, bufaddr, bufsiz);
   if(stat != 0) return LOG_RTERR (pctxt, stat);

   pctxt->buffer.aligned = aligned;
   return 0;
}

EXTPERMETHOD int pe_setp (OSCTXT* pctxt,
             OSOCTET* bufaddr, size_t bufsiz, OSBOOL aligned)
{
   int stat = rtxInitContextBuffer (pctxt, bufaddr, bufsiz);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   pctxt->buffer.aligned = aligned;

   return 0;
}

/* This function initializes a context and sets its buffer to point     */
/* at the same data as the given context..                              */

EXTPERMETHOD int pu_initContextBuffer (OSCTXT* pTarget, OSCTXT* pSource)
{
   int stat = pu_setBuffer (pTarget, 
                            pSource->buffer.data,
                            pSource->buffer.size, 
                            pSource->buffer.aligned);

   if (0 == stat) {
      pTarget->buffer.byteIndex = pSource->buffer.byteIndex;
      pTarget->buffer.bitOffset = pSource->buffer.bitOffset;
   }
   else return LOG_RTERR (pTarget, stat);

   return 0;
}

/***********************************************************************
 *
 *  Routine name: pu_freeContext
 *
 *  Description:  This routine frees a context block structure
 *                including all internally allocated dynamic memory.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct* Pointer to context structure to free.
 *
 *  Outputs:
 *
 *  None
 *
 *
 **********************************************************************/

EXTPERMETHOD void pu_freeContext (OSCTXT* pctxt)
{
   rtFreeContext (pctxt);
}

/***********************************************************************
 *
 *  Routine name: pu_bitcnt
 *
 *  Description:  This routine counts the number of bits required
 *                to hold the given unsigned integer value.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  value       uint    Unsigned integer value
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  nbits       uint    Number of bits required to hold the value
 *
 **********************************************************************/

#define UINTBITS (sizeof(OSUINT32)*8)

EXTPERMETHOD OSUINT32 pu_bitcnt (OSUINT32 value)
{ 
   /* Binary search - decision tree (5 tests, rarely 6) */
   return
      ((value < 1UL<<15) ?
       ((value < 1UL<<7) ?
        ((value < 1UL<<3) ?
         ((value < 1UL<<1) ? ((value < 1UL<<0) ? 0 : 1) : ((value < 1UL<<2) ? 2 : 3)) :
         ((value < 1UL<<5) ? ((value < 1UL<<4) ? 4 : 5) : ((value < 1UL<<6) ? 6 : 7))) :
        ((value < 1UL<<11) ?
         ((value < 1UL<<9) ? ((value < 1UL<<8) ? 8 : 9) : ((value < 1UL<<10) ? 10 : 11)) :
         ((value < 1UL<<13) ? ((value < 1UL<<12) ? 12 : 13) : ((value < 1UL<<14) ? 14 : 15)))) :
       ((value < 1UL<<23) ?
        ((value < 1UL<<19) ?
         ((value < 1UL<<17) ? ((value < 1UL<<16) ? 16 : 17) : ((value < 1UL<<18) ? 18 : 19)) :
         ((value < 1UL<<21) ? ((value < 1UL<<20) ? 20 : 21) : ((value < 1UL<<22) ? 22 : 23))) :
        ((value < 1UL<<27) ?
         ((value < 1UL<<25) ? ((value < 1UL<<24) ? 24 : 25) : ((value < 1UL<<26) ? 26 : 27)) :
         ((value < 1UL<<29) ? ((value < 1UL<<28) ? 28 : 29) : ((value < 1UL<<30) ? 30 : 
         ((value < 1UL<<31) ? 31 : 32))))));

   /* !AB 09/23/02, the optimized version used (see above).
    * It is faster in 4-14 times than version below (depends on
    * number of bits being tested) *
   OSUINT32 nbits = 0;

   while (nbits < UINTBITS && value >= (OSUINT32)(OSINTCONST(1) << nbits))
      nbits++;

   return nbits; */
}


EXTPERMETHOD size_t pu_getMaskAndIndex (size_t bitOffset, unsigned char* pMask)
{
   int relBitOffset = 7 - (int)(bitOffset % 8);
   *pMask = (unsigned char)(OSUINTCONST(1) << relBitOffset);
   return (bitOffset / 8);  /* byte index */
}

/***********************************************************************
 *
 *  Routine name: pu_getSizeConstraint
 *
 *  Description:  This routine returns a pointer to a size constraint
 *                matching the given extendable attribute.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt      struct* ASN.1 context block structure
 *  extbit      bool    Value of extension bit
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  sizeCnst    struct* Pointer to matching constraint structure
 *
 *
 **********************************************************************/

EXTPERMETHOD Asn1SizeCnst* pu_getSizeConstraint (OSCTXT* pctxt, OSBOOL extbit)
{
   Asn1SizeCnst* lpSize = ACINFO(pctxt)->pSizeConstraint;

   while (lpSize) {
      if (lpSize->extended == extbit)
         return lpSize;
      else
         lpSize = lpSize->next;
   }

   return NULL;
}
