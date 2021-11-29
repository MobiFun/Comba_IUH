/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.1.4, Date: 06-Jul-2012.
 */
#include "HNBAP-Containers.h"
#include "rtxsrc/rtxCommon.h"

void asn1Init_ProtocolIE_Field (ProtocolIE_Field* pvalue)
{
   if (0 == pvalue) return;
   pvalue->value.numocts = 0;
   pvalue->value.data = 0;
}

void asn1Init_ProtocolIE_Container (ProtocolIE_Container* pvalue)
{
   if (0 == pvalue) return;
   rtxDListFastInit (pvalue);
}

void asn1Init_ProtocolExtensionField (ProtocolExtensionField* pvalue)
{
   if (0 == pvalue) return;
   pvalue->extensionValue.numocts = 0;
   pvalue->extensionValue.data = 0;
}

void asn1Init_ProtocolExtensionContainer (ProtocolExtensionContainer* pvalue)
{
   if (0 == pvalue) return;
   rtxDListFastInit (pvalue);
}

void asn1Init_PrivateIE_Field (PrivateIE_Field* pvalue)
{
   if (0 == pvalue) return;
   asn1Init_PrivateIE_ID (&pvalue->id);
   pvalue->value.numocts = 0;
   pvalue->value.data = 0;
}

void asn1Init_PrivateIE_Container (PrivateIE_Container* pvalue)
{
   if (0 == pvalue) return;
   rtxDListFastInit (pvalue);
}

void asn1Init_ProtocolIE_Single_Container (ProtocolIE_Single_Container* pvalue)
{
   if (0 == pvalue) return;
   asn1Init_ProtocolIE_Field (pvalue);
}
