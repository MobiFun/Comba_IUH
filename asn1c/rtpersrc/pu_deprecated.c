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

/***********************************************************************
 *
 *  Routine name: pu_getBitOffset
 *
 *  Description:  This routine calculates the relative bit offset
 *                to the current buffer position.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  ctxt        struct  PER context structure
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  offset      int     Bit offset (starting at 0) to buffer position
 *
 **********************************************************************/

EXTPERMETHOD int pu_getBitOffset (OSCTXT* pctxt)
{
   /* bit offset = (byte index * 8) + rel bit offset in current byte */
   int relBitOffset = 8 - pctxt->buffer.bitOffset;
   return (int)((pctxt->buffer.byteIndex * 8) + relBitOffset);
}

/* Set the bit offset to the given value within the context */

EXTPERMETHOD void pu_setBitOffset (OSCTXT* pctxt, int bitOffset)
{
   pctxt->buffer.byteIndex = (bitOffset / 8);
   pctxt->buffer.bitOffset = (OSUINT16)(8 - (bitOffset % 8));
}
