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
 *  Routine name: ASN.1 file read functions
 *
 *  Description:  These functions support the reading and writing
 *                of ASN.1 encoded message components to and from
 *                binary files.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *
 **********************************************************************/

/* xu_fread: this function reads an encoded message component from the	*/
/* given file into the given buffer..					*/

int xu_fread (FILE* fp, ASN1OCTET* bufp, int bufsiz)
{
  ASN1CTXT	ctxt;
  ASN1TAG	tag;
  int 		len, nbr, stat;

  /* Read up to six bytes to get initial tag/length */

  if (bufsiz < 6) {
    return (ASN_E_BUFOVFLW);
  }

  if ((nbr = (int)fread (bufp, 1, 6, fp)) > 0) {
    /* Call xd_setp to get encoded message component tag and length */

    if ((stat = rtInitContext2 (&ctxt)) != ASN_OK)
      return (stat);

    if ((stat = xd_setp (&ctxt, bufp, 0, &tag, &len)) == ASN_OK) {

      /* Read remaining message bytes into the buffer */

      if (len > nbr) {
	if (len <= bufsiz) {
	  nbr += (int)fread (&bufp[nbr], 1, (len - nbr), fp);
	}
	else {   /* provided buffer is too small */
	  stat = ASN_E_BUFOVFLW;
	}
      }

      /* If length equals number read, success */

      if (stat == ASN_OK)
         stat = ((len == nbr) ? len : ASN_E_ENDOFBUF);
    }
    rtFreeContext (&ctxt);
    return stat;
  }
  else {
    return (nbr);
  }

}

