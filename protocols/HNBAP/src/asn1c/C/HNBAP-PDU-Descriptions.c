/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.1.4, Date: 06-Jul-2012.
 */
#include "HNBAP-PDU-Descriptions.h"
#include "HNBAP-Constants.h"
#include "rtxsrc/rtxCommon.h"

void asn1Init_HnbInitiatingMessage (HnbInitiatingMessage* pvalue)
{
   if (0 == pvalue) return;
   pvalue->value.numocts = 0;
   pvalue->value.data = 0;
}

void asn1Init_HnbSuccessfulOutcome (HnbSuccessfulOutcome* pvalue)
{
   if (0 == pvalue) return;
   pvalue->value.numocts = 0;
   pvalue->value.data = 0;
}

void asn1Init_HnbUnsuccessfulOutcome (HnbUnsuccessfulOutcome* pvalue)
{
   if (0 == pvalue) return;
   pvalue->value.numocts = 0;
   pvalue->value.data = 0;
}

void asn1Init_HnbHNBAP_PDU (HnbHNBAP_PDU* pvalue)
{
   if (0 == pvalue) return;
   pvalue->t = 0;
   OSCRTLMEMSET (&pvalue->u, 0, sizeof(pvalue->u));
}

