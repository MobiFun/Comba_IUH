/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.1.4, Date: 09-Jul-2012.
 */
#include "RUA-PDU-Descriptions.h"
#include "RUA-Constants.h"
#include "rtxsrc/rtxCommon.h"

void asn1Init_RUA_InitiatingMessage (RUA_InitiatingMessage* pvalue)
{
   if (0 == pvalue) return;
   pvalue->value.numocts = 0;
   pvalue->value.data = 0;
}

void asn1Init_RUA_SuccessfulOutcome (RUA_SuccessfulOutcome* pvalue)
{
   if (0 == pvalue) return;
   pvalue->value.numocts = 0;
   pvalue->value.data = 0;
}

void asn1Init_RUA_UnsuccessfulOutcome (RUA_UnsuccessfulOutcome* pvalue)
{
   if (0 == pvalue) return;
   pvalue->value.numocts = 0;
   pvalue->value.data = 0;
}

void asn1Init_RUA_RUA_PDU (RUA_RUA_PDU* pvalue)
{
   if (0 == pvalue) return;
   pvalue->t = 0;
   OSCRTLMEMSET (&pvalue->u, 0, sizeof(pvalue->u));
}
