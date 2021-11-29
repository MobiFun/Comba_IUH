/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.1.4, Date: 09-Jul-2012.
 */
#include "RUA-CommonDataTypes.h"
#include "rtsrc/rtPrint.h"
#include "rtxsrc/rtxCommon.h"

void asn1Print_RUA_ProcedureCode
   (const char* name, RUA_ProcedureCode* pvalue)
{
   rtPrintIndent ();
   rtPrintUnsigned (name, *pvalue);
}

void asn1Print_RUA_Criticality
   (const char* name, RUA_Criticality* pvalue)
{
   rtPrintIndent ();
   printf ("%s = ", name);
   switch (*pvalue) {
      case 0: printf ("reject\n"); break;
      case 1: printf ("ignore\n"); break;
      case 2: printf ("notify\n"); break;
      default: printf ("???\n");
   }
}

void asn1Print_RUA_ProtocolIE_ID
   (const char* name, RUA_ProtocolIE_ID* pvalue)
{
   rtPrintIndent ();
   rtPrintUnsigned (name, *pvalue);
}

void asn1Print_RUA_PrivateIE_ID
   (const char* name, RUA_PrivateIE_ID* pvalue)
{
   rtPrintOpenBrace (name);

   switch (pvalue->t) {
      case 1: {
         rtPrintIndent ();
         rtPrintUnsigned ("local", pvalue->u.local);
         break;
      }
      case 2: {
         rtPrintIndent ();
         rtPrintOID ("global", pvalue->u.global);
         break;
      }
      default:;
   }

   rtPrintCloseBrace ();
}

void asn1Print_RUA_TriggeringMessage
   (const char* name, RUA_TriggeringMessage* pvalue)
{
   rtPrintIndent ();
   printf ("%s = ", name);
   switch (*pvalue) {
      case 0: printf ("initiating-message\n"); break;
      case 1: printf ("successful-outcome\n"); break;
      case 2: printf ("unsuccessful-outcome\n"); break;
      default: printf ("???\n");
   }
}

void asn1Print_RUA_Presence
   (const char* name, RUA_Presence* pvalue)
{
   rtPrintIndent ();
   printf ("%s = ", name);
   switch (*pvalue) {
      case 0: printf ("optional\n"); break;
      case 1: printf ("conditional\n"); break;
      case 2: printf ("mandatory\n"); break;
      default: printf ("???\n");
   }
}

