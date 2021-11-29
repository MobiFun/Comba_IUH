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
 *  Routine name: xu_hexstrcpy
 *
 *  Description:  This utility routine copies a hex string value
 *                into a string C structure variable.  The string
 *                is passed as a standard null terminated C string
 *                containing ascii hex digits (0 through F) .
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  numbytes	int	length of string
 *  hstring	char *	hex C string from which to copy data.
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  stat	int	Completion status.  Returned as function result.
 *  data	char *	Output buffer to hold converted string.
 *
 **********************************************************************/

int xu_hexstrcpy (char *data, char *hstring)
{
   register int	stat = ASN_OK; 
   register size_t numbytes = strlen (hstring);
   int		hexval;
   char		buf[3];
   ASN1BOOL	first_pass = TRUE;

   while (*hstring)
      if (
      (*hstring >= '0' && *hstring <= '9') ||
      (*hstring >= 'A' && *hstring <= 'F') ||
      (*hstring >= 'a' && *hstring <= 'f'))
      {
         if ((numbytes & 1) && first_pass)
         {
            buf[0] = '0';
            first_pass = FALSE;
         }
         else
            buf[0] = *hstring++;

         buf[1] = *hstring++;
         buf[2] = '\0';
         sscanf (buf, "%x", &hexval);
         *data++ = (char) hexval;
      }
      else
      {
         stat = ASN_E_INVHEXS;
         break;
      }

   return (stat);
}

