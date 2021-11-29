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

#include "rtpersrc/pd_common.hh"

/***********************************************************************
 *
 *  Routine name: pd_OctetString
 *
 *  Description:  The following function decodes an octet string value
 *                into a static buffer.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  ctxt        struct* pointer to PER context block structure
 *  numocts     int*    pointer to variable to receive decoded number of octets
 *  buffer      octet*  pointer to buffer to receive decoded octet string data
 *  bufsiz      int     size of the data buffer
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat        int     completion status of operation
 *
 **********************************************************************/

EXTPERMETHOD int pd_OctetString (OSCTXT* pctxt, OSUINT32* pnumocts, 
                    OSOCTET* buffer, OSUINT32 bufsiz)
{
   OSUINT32 octcnt;
   int lstat, octidx = 0, stat;
   Asn1SizeCnst* pSizeList = ACINFO(pctxt)->pSizeConstraint;

   for (*pnumocts = 0;;) {
      lstat = pd_Length (pctxt, &octcnt);
      if (lstat < 0) return LOG_RTERR (pctxt, lstat);

      PU_NEWFIELD (pctxt, "octets");

      if (octcnt > 0) {
         *pnumocts += octcnt;

         if (pctxt->buffer.aligned) {
            OSBOOL doAlign;

            stat = pu_BitAndOctetStringAlignmentTest (pSizeList, octcnt, 
                                                      FALSE, &doAlign);
            if (stat != 0) return LOG_RTERR (pctxt, stat);

            if (doAlign) {
               stat = PD_BYTE_ALIGN (pctxt);
               if (stat != 0) return LOG_RTERR (pctxt, stat);
            }
         }

         stat = pd_octets (pctxt, &buffer[octidx], 
                           bufsiz - octidx, (octcnt * 8));

         if (stat != 0) return LOG_RTERR (pctxt, stat);
      }

      PU_SETBITCOUNT (pctxt);

      if (lstat == RT_OK_FRAG) {
         octidx += octcnt;
      }
      else break;
   }

   LCHECKPER (pctxt);

   return 0;
}
