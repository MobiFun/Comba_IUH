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

/***********************************************************************
 *
 *  Routine name: rtCheckBuffer
 *
 *  Description:  This routine checks to see if the encode buffer
 *                contains enough free space to hold the given 
 *                number of bytes.  If it does not and the buffer 
 *                is dynamic, it is expanded.  If not dynamic, an 
 *                'RTERR_BUFOVFLW' error is returned.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  pctxt       struct* Pointer to context structure
 *  nbytes      uint    Number of bytes of additional space required
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat        int     Status of operation
 *
 **********************************************************************/

#include <stdlib.h>
#include "rtxsrc/rtxBuffer.h"
#include "rtxsrc/rtxCommonDefs.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxMemory.h"
#include "rtxsrc/rtxStreamDirectBuf.hh"

int rtxCheckBuffer (OSCTXT* pctxt, size_t nbytes)
{
   if ( ( pctxt->buffer.byteIndex + nbytes ) > pctxt->buffer.size ) {
#ifndef _NO_STREAM
      if (OSRTISSTREAM (pctxt)) {
         int stat;
         
         stat = rtxStreamDirectBufCheck (pctxt);
         if (stat != 0) return LOG_RTERR (pctxt, stat);

         stat = rtxStreamFlush (pctxt); 
         if (stat != 0) return LOG_RTERR (pctxt, stat);

         if ( ( pctxt->buffer.byteIndex + nbytes ) <= pctxt->buffer.size )
            return 0;
      }
#endif
      if (pctxt->buffer.dynamic) {

         /* If dynamic encoding enabled, expand the current buffer 	*/
         /* to allow encoding to continue.                              */

         pctxt->buffer.size += OSRTMAX (OSRTENCBUFSIZ, nbytes);

         pctxt->buffer.data = rtxMemReallocArray 
            (pctxt, pctxt->buffer.data, pctxt->buffer.size, OSOCTET);

         if (!pctxt->buffer.data) 
            return LOG_RTERRNEW (pctxt, RTERR_NOMEM);
      }
      else {
         return LOG_RTERRNEW (pctxt, RTERR_BUFOVFLW);
      }
   }

   return 0;
}

