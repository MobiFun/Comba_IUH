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

#include <string.h>
#include "rtxsrc/rtxBuffer.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxContext.hh"
#include "rtxsrc/rtxStreamDirectBuf.hh"

EXTRTMETHOD int rtxWriteBytes 
(OSCTXT* pctxt, const OSOCTET* pdata, size_t nocts)
{
   if (nocts > 0) {
      if (!OSRTISSTREAM (pctxt)) {
         int stat = rtxCheckBuffer (pctxt, nocts);
         if (0 == stat) {
            OSCRTLMEMCPY (&pctxt->buffer.data[pctxt->buffer.byteIndex], 
                    pdata, nocts);

            pctxt->buffer.byteIndex += nocts;
         }
         else return LOG_RTERR (pctxt, stat);
      } 
#ifndef _NO_STREAM
      else {
         if (OSRTSTREAM_ID (pctxt) != OSRTSTRMID_DIRECTBUF && 
             !(OSRTSTREAM_FLAGS (pctxt) & OSRTSTRMF_UNBUFFERED)) 
         {
            int stat = rtxStreamDirectBufCreate (pctxt);
            if (stat != 0) return LOG_RTERR (pctxt, stat);
         }
         return rtxStreamWrite (pctxt, pdata, nocts);
      }
#endif
   }
   LCHECKX (pctxt);
   return 0;
}

