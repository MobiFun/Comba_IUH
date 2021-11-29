/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.1.4, Date: 06-Jul-2012.
 */
#include "HNBAP-Containers.h"
#include "rtsrc/rtPrint.h"
#include "rtxsrc/rtxCommon.h"

void asn1Print_ProtocolIE_Field
   (const char* name, ProtocolIE_Field* pvalue)
{
   rtPrintOpenBrace (name);

   asn1Print_ProtocolIE_ID ("id",
      &pvalue->id);

   asn1Print_Criticality ("criticality",
      &pvalue->criticality);

   rtPrintIndent ();
   rtPrintHexStr ("value",
      pvalue->value.numocts,
      pvalue->value.data);

   rtPrintCloseBrace ();
}

void asn1Print_ProtocolIE_Container
   (const char* name, ProtocolIE_Container* pvalue)
{
   ProtocolIE_Field* pdata0;
   OSRTDListNode* pnode;
   char namebuf[512];
   OSUINT32 xx1;

   pnode = pvalue->head;
   for (xx1 = 0; xx1 < pvalue->count; xx1++) {
      pdata0 = (ProtocolIE_Field*) pnode->data;
      os_snprintf (namebuf, 512, "%s[%d]", name, xx1);
      asn1Print_ProtocolIE_Field (namebuf,
         pdata0);
      pnode = pnode->next;
   }
}

void asn1Print_ProtocolExtensionField
   (const char* name, ProtocolExtensionField* pvalue)
{
   rtPrintOpenBrace (name);

   asn1Print_ProtocolIE_ID ("id",
      &pvalue->id);

   asn1Print_Criticality ("criticality",
      &pvalue->criticality);

   rtPrintIndent ();
   rtPrintHexStr ("extensionValue",
      pvalue->extensionValue.numocts,
      pvalue->extensionValue.data);

   rtPrintCloseBrace ();
}

void asn1Print_ProtocolExtensionContainer
   (const char* name, ProtocolExtensionContainer* pvalue)
{
   ProtocolExtensionField* pdata0;
   OSRTDListNode* pnode;
   char namebuf[512];
   OSUINT32 xx1;

   pnode = pvalue->head;
   for (xx1 = 0; xx1 < pvalue->count; xx1++) {
      pdata0 = (ProtocolExtensionField*) pnode->data;
      os_snprintf (namebuf, 512, "%s[%d]", name, xx1);
      asn1Print_ProtocolExtensionField (namebuf,
         pdata0);
      pnode = pnode->next;
   }
}

void asn1Print_PrivateIE_Field
   (const char* name, PrivateIE_Field* pvalue)
{
   rtPrintOpenBrace (name);

   asn1Print_PrivateIE_ID ("id",
      &pvalue->id);

   asn1Print_Criticality ("criticality",
      &pvalue->criticality);

   rtPrintIndent ();
   rtPrintHexStr ("value",
      pvalue->value.numocts,
      pvalue->value.data);

   rtPrintCloseBrace ();
}

void asn1Print_PrivateIE_Container
   (const char* name, PrivateIE_Container* pvalue)
{
   PrivateIE_Field* pdata0;
   OSRTDListNode* pnode;
   char namebuf[512];
   OSUINT32 xx1;

   pnode = pvalue->head;
   for (xx1 = 0; xx1 < pvalue->count; xx1++) {
      pdata0 = (PrivateIE_Field*) pnode->data;
      os_snprintf (namebuf, 512, "%s[%d]", name, xx1);
      asn1Print_PrivateIE_Field (namebuf,
         pdata0);
      pnode = pnode->next;
   }
}

void asn1Print_ProtocolIE_Single_Container
   (const char* name, ProtocolIE_Single_Container* pvalue)
{
   asn1Print_ProtocolIE_Field (name,
      pvalue);
}
