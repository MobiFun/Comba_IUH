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

#define _ASN1INTL_H_ /* prevent including of asn1intl.h */

#include "xu_common.hh"

/***********************************************************************
 *
 *  Routine name: Error functions
 *
 *  Description:  These functions handle error logging and printing
 *                for run-time errors.
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

int xu_error (ASN1CTXT* ctxt_p, int status, char* module, int lineno)
{
#ifndef _COMPACT
   return rtErrSetData (&ctxt_p->errInfo, status, module, lineno);
#else
   ctxt_p->errInfo.status = status;
   return status;
#endif
}

int xu_addErrParm (ASN1CTXT* ctxt_p, char* errprm_p)
{
#ifndef _COMPACT
   return rtErrAddStrParm (&ctxt_p->errInfo, errprm_p);
#else
   return TRUE;
#endif
}

int xu_addIntErrParm (ASN1CTXT* ctxt_p, int errParm)
{
#ifndef _COMPACT
   return rtErrAddIntParm (&ctxt_p->errInfo, errParm);
#else
   return TRUE;
#endif
}

int xu_addUnsignedErrParm (ASN1CTXT* ctxt_p, unsigned int errParm)
{
#ifndef _COMPACT
   return rtErrAddUIntParm (&ctxt_p->errInfo, errParm);
#else
   return TRUE;
#endif
}

int xu_addTagErrParm (ASN1CTXT* ctxt_p, ASN1TAG errParm)
{
#ifndef _COMPACT
   return rtErrAddTagParm (&ctxt_p->errInfo, errParm);
#else
   return TRUE;
#endif
}

void xu_freeErrParms (ASN1CTXT* ctxt_p)
{
#ifndef _COMPACT
   rtErrFreeParms (&ctxt_p->errInfo);
#endif
}

void xu_perror (ASN1CTXT* ctxt_p)
{
#ifndef _COMPACT
   rtErrPrint (&ctxt_p->errInfo);
#else
   printf ("err: %d\n", ctxt_p->errInfo.status);
#endif
}

void xu_log_error (ASN1CTXT* ctxt_p, ASN1DumpCbFunc cb, void* cbArg_p)
{
#ifndef _COMPACT
   rtErrLogUsingCB (&ctxt_p->errInfo, cb, cbArg_p);
#endif
}

char *xu_fmtErrMsg (ASN1CTXT* ctxt_p, char* bufp)
{
#ifndef _COMPACT
   return rtErrFmtMsg (&ctxt_p->errInfo, bufp);
#else
   return "";
#endif
}

