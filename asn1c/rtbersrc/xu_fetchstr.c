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
 *  Routine name: xu_fetchstr
 *
 *  Description:  This ASN.1 utility routine converts an ASN octet string
 *                into a null terminated text string.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  numocts	int 	Number of octets (bytes) in string.
 *  data	char *	Buffer holding ASN octet string contents.
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  cstring     char *  Pointer to resultant null terminated string.
 *                      Returned as function result.
 *
 **********************************************************************/

char *xu_fetchstr (int numocts, char *data)
{
   static char buf[80];

   if (numocts > sizeof(buf)) return (NULL);
   strncpy (buf, data, numocts);
   buf[numocts] = '\0';
   return (buf);
}

