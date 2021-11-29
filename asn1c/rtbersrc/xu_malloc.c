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
 *  Routine name: xu_malloc
 *
 *  Description:  This ASN.1 memory management service routine provides a
 *                front-end to the C malloc function.  It allocates memory
 *                in larger chunks to improve encode/decode performance.
 *
 *  Inputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  memsiz	int	Amount of dynamic memory, in bytes, to be 
 *                      allocated
 *
 *  Outputs:
 *
 *  Name        Type    Description
 *  ----        ----    -----------
 *  ptr		void *  Allocated pointer.  Returned as function result.
 *
 **********************************************************************/

void* xu_malloc (ASN1CTXT* ctxt_p, int nbytes)
{
   /* call common function */
   return ASN1MALLOC (ctxt_p, nbytes);
}

/* xu_alloc_array: convenience function to allocate a dynamic array	*/
/* using the xu_malloc function..					*/

void xu_alloc_array (ASN1CTXT* ctxt_p, ASN1SeqOf* seqOf_p, int recSize,
   int recCount)
{
   seqOf_p->n = recCount;
   seqOf_p->elem = xu_malloc (ctxt_p, recSize * recCount);
}

/***********************************************************************
 *
 *  Routine name: xu_freeall
 *
 *  Description:  This ASN.1 memory management service routine frees all
 *                of the dynamic memory previously allocated for a 
 *                given context using the xu_malloc routine.
 *
 *  Inputs:
 *
 *  None
 *
 *  Outputs:
 *
 *  None
 *
 **********************************************************************/

void xu_freeall (ASN1CTXT* ctxt_p)
{
   rtFreeContext (ctxt_p);
}

