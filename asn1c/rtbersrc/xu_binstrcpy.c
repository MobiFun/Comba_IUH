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

#include "xu_common.hh"

/***********************************************************************
 *
 *  Routine name: xu_binstrcpy
 *
 *  Description:  This utility routine copies a binary string value
 *                into a string C structure variable.  The string
 *                is passed as a standard null terminated C string
 *                containing ascii binary digits (1's and 0's).
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  numbytes	int	length of string
 *  bstring	char *	binary C string from which to copy data.
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat	int	Completion status.  Returned as function result.
 *  data	char *	Output buffer to hold converted string.
 *
 **********************************************************************/

int xu_binstrcpy (char *data, char *bstring)
{
   register int i, stat = ASN_OK;
   ASN1OCTET b;

   while (*bstring && stat == ASN_OK)
   {
      b = 0;

      for (i = 0; i < 8; i++)
         if (*bstring)
         {
            if (*bstring >= '0' && *bstring <= '1')
               b = (ASN1OCTET) ((b * 2) + (*bstring++ - '0'));
            else
            {
               stat = ASN_E_INVBINS;
               break;
            }
         }
         else
            b = (ASN1OCTET) (b * 2);

      *data++ = b;
   }

   return (stat);
}

