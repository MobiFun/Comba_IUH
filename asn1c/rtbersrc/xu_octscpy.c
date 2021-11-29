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
 * Function name:  xu_octscpy_s, xu_octscpy_d, xu_octmcpy_s, xu_octmcpy_d
 *
 * Description:	These ASN.1 utility functions copy a standard null
 *		terminated C string into the structure expected by 
 *		the ASN.1 low level encode routine for octet strings.  
 *		This structure consists of a length field for the size 
 *		of the string and a data field for the actual string 
 *		contents.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  numocts	int*	Number of octets (bytes) in string.
 *  data	char**	Buffer in which to store string contents.
 *  cstring	char*	C string from which to copy data.
 *  zterm	char	Flag indicating whether or not null terminator
 *			should be copied.
 *
 *  Outputs:
 *
 *  None
 *
 **********************************************************************/
                       
/* Copy into static OCTET STRING  */

void xu_octscpy_s (ASN1UINT *nocts_p, 
                   ASN1OCTET *data_p, char *cstring, char zterm)
{
   *nocts_p = (ASN1UINT)strlen (cstring);
   if (zterm) (*nocts_p)++;
   strncpy ((char*)data_p, cstring, *nocts_p);
}

void xu_octscpy_ss (ASN1OctStr *octStr_p, char *cstring, char zterm)
{
   xu_octscpy_s (&octStr_p->numocts, octStr_p->data, cstring, zterm);
}

/* Copy into dynamic OCTET STRING  */

void xu_octscpy_d (ASN1CTXT* ctxt_p, ASN1UINT* nocts_p, 
                   ASN1ConstOctetPtr* data_p2, char* cstring, char zterm)
{
   char* pstr;
   *nocts_p = (ASN1UINT)strlen (cstring);
   if (zterm) (*nocts_p)++;
   pstr = (char*) ASN1MALLOC (ctxt_p, *nocts_p);
   *data_p2 = (ASN1ConstOctetPtr) pstr;
   if (pstr == NULL) return;
   strncpy (pstr, cstring, *nocts_p);
}

void xu_octscpy_ds (ASN1CTXT* ctxt_p, ASN1DynOctStr *octStr_p, 
                    char *cstring, char zterm)
{
   xu_octscpy_d (ctxt_p, &octStr_p->numocts, &octStr_p->data, 
      cstring, zterm);
}

/* Memcpy into static OCTET STRING  */

void xu_octmcpy_s (ASN1OctStr *octStr_p, void* data_p, int datalen)
{
   octStr_p->numocts = datalen;
   memcpy ((char*) octStr_p->data, (char*) data_p, datalen);
}

/* Memcpy into dynamic OCTET STRING  */

void xu_octmcpy_d (ASN1CTXT* ctxt_p, ASN1DynOctStr *octStr_p, void* data_p, 
   int datalen)
{
   octStr_p->numocts = datalen;
   octStr_p->data  = (ASN1OCTET*) ASN1MALLOC (ctxt_p, datalen);
   if (octStr_p->data == NULL) return;
   memcpy ((char*) octStr_p->data, (char*) data_p, datalen);
}
