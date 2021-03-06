/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.1.4, Date: 09-Jul-2012.
 */
#include "RUA-IEs.h"
#include "RUA-Constants.h"
#include "rtsrc/rtPrint.h"
#include "rtxsrc/rtxCommon.h"

void asn1Print_RUA_CN_DomainIndicator
   (const char* name, RUA_CN_DomainIndicator* pvalue)
{
   rtPrintIndent ();
   printf ("%s = ", name);
   switch (*pvalue) {
      case 0: printf ("cs-domain\n"); break;
      case 1: printf ("ps-domain\n"); break;
      default: printf ("???\n");
   }
}

void asn1Print_RUA_Establishment_Cause
   (const char* name, RUA_Establishment_Cause* pvalue)
{
   rtPrintIndent ();
   printf ("%s = ", name);
   switch (*pvalue) {
      case 0: printf ("emergency-call\n"); break;
      case 1: printf ("normal-call\n"); break;
      default: printf ("%u\n", *pvalue);
   }
}

void asn1Print_RUA_Context_ID
   (const char* name, RUA_Context_ID* pvalue)
{
   rtPrintIndent ();
   rtPrintBitStrBraceText (name, pvalue->numbits, pvalue->data);
}

void asn1Print_RUA_Ansi_41_IDNNS
   (const char* name, RUA_Ansi_41_IDNNS* pvalue)
{
   rtPrintIndent ();
   rtPrintBitStrBraceText (name, pvalue->numbits, pvalue->data);
}

void asn1Print_RUA_RANAP_Message
   (const char* name, RUA_RANAP_Message* pvalue)
{
   rtPrintIndent ();
   rtPrintHexStr (name, pvalue->numocts, pvalue->data);
}

void asn1Print_RUA_RoutingParameter
   (const char* name, RUA_RoutingParameter* pvalue)
{
   rtPrintIndent ();
   rtPrintBitStrBraceText (name, pvalue->numbits, pvalue->data);
}

void asn1Print_RUA_CauseRadioNetwork
   (const char* name, RUA_CauseRadioNetwork* pvalue)
{
   rtPrintIndent ();
   printf ("%s = ", name);
   switch (*pvalue) {
      case 0: printf ("normal\n"); break;
      case 1: printf ("connect-failed\n"); break;
      case 2: printf ("network-release\n"); break;
      case 3: printf ("unspecified\n"); break;
      default: printf ("%u\n", *pvalue);
   }
}

void asn1Print_RUA_CauseTransport
   (const char* name, RUA_CauseTransport* pvalue)
{
   rtPrintIndent ();
   printf ("%s = ", name);
   switch (*pvalue) {
      case 0: printf ("transport-resource-unavailable\n"); break;
      case 1: printf ("unspecified\n"); break;
      default: printf ("%u\n", *pvalue);
   }
}

void asn1Print_RUA_CauseProtocol
   (const char* name, RUA_CauseProtocol* pvalue)
{
   rtPrintIndent ();
   printf ("%s = ", name);
   switch (*pvalue) {
      case 0: printf ("transfer-syntax-error\n"); break;
      case 1: printf ("abstract-syntax-error-reject\n"); break;
      case 2: printf ("abstract-syntax-error-ignore-and-notify\n"); break;
      case 3: printf ("message-not-compatible-with-receiver-state\n"); break;
      case 4: printf ("semantic-error\n"); break;
      case 5: printf ("unspecified\n"); break;
      case 6: printf ("abstract-syntax-error-falsely-constructed-message\n"); break;
      default: printf ("%u\n", *pvalue);
   }
}

void asn1Print_RUA_CauseMisc
   (const char* name, RUA_CauseMisc* pvalue)
{
   rtPrintIndent ();
   printf ("%s = ", name);
   switch (*pvalue) {
      case 0: printf ("processing-overload\n"); break;
      case 1: printf ("hardware-failure\n"); break;
      case 2: printf ("o-and-m-intervention\n"); break;
      case 3: printf ("unspecified\n"); break;
      default: printf ("%u\n", *pvalue);
   }
}

void asn1Print_RUA_TypeOfError
   (const char* name, RUA_TypeOfError* pvalue)
{
   rtPrintIndent ();
   printf ("%s = ", name);
   switch (*pvalue) {
      case 0: printf ("not-understood\n"); break;
      case 1: printf ("missing\n"); break;
      default: printf ("%u\n", *pvalue);
   }
}

void asn1Print_RUA_IntraDomainNasNodeSelector_version_later_futurecoding
   (const char* name, RUA_IntraDomainNasNodeSelector_version_later_futurecoding* pvalue)
{
   rtPrintIndent ();
   rtPrintBitStrBraceText (name, pvalue->numbits, pvalue->data);
}

void asn1Print_RUA_Gsm_map_IDNNS_routingbasis_localPTMSI
   (const char* name, RUA_Gsm_map_IDNNS_routingbasis_localPTMSI* pvalue)
{
   rtPrintOpenBrace (name);

   asn1Print_RUA_RoutingParameter ("routingparameter",
      &pvalue->routingparameter);

   rtPrintCloseBrace ();
}

void asn1Print_RUA_Gsm_map_IDNNS_routingbasis_tMSIofsamePLMN
   (const char* name, RUA_Gsm_map_IDNNS_routingbasis_tMSIofsamePLMN* pvalue)
{
   rtPrintOpenBrace (name);

   asn1Print_RUA_RoutingParameter ("routingparameter",
      &pvalue->routingparameter);

   rtPrintCloseBrace ();
}

void asn1Print_RUA_Gsm_map_IDNNS_routingbasis_tMSIofdifferentPLMN
   (const char* name, RUA_Gsm_map_IDNNS_routingbasis_tMSIofdifferentPLMN* pvalue)
{
   rtPrintOpenBrace (name);

   asn1Print_RUA_RoutingParameter ("routingparameter",
      &pvalue->routingparameter);

   rtPrintCloseBrace ();
}

void asn1Print_RUA_Gsm_map_IDNNS_routingbasis_iMSIresponsetopaging
   (const char* name, RUA_Gsm_map_IDNNS_routingbasis_iMSIresponsetopaging* pvalue)
{
   rtPrintOpenBrace (name);

   asn1Print_RUA_RoutingParameter ("routingparameter",
      &pvalue->routingparameter);

   rtPrintCloseBrace ();
}

void asn1Print_RUA_Gsm_map_IDNNS_routingbasis_iMSIcauseUEinitiatedEvent
   (const char* name, RUA_Gsm_map_IDNNS_routingbasis_iMSIcauseUEinitiatedEvent* pvalue)
{
   rtPrintOpenBrace (name);

   asn1Print_RUA_RoutingParameter ("routingparameter",
      &pvalue->routingparameter);

   rtPrintCloseBrace ();
}

void asn1Print_RUA_Gsm_map_IDNNS_routingbasis_iMEI
   (const char* name, RUA_Gsm_map_IDNNS_routingbasis_iMEI* pvalue)
{
   rtPrintOpenBrace (name);

   asn1Print_RUA_RoutingParameter ("routingparameter",
      &pvalue->routingparameter);

   rtPrintCloseBrace ();
}

void asn1Print_RUA_Gsm_map_IDNNS_routingbasis_spare2
   (const char* name, RUA_Gsm_map_IDNNS_routingbasis_spare2* pvalue)
{
   rtPrintOpenBrace (name);

   asn1Print_RUA_RoutingParameter ("routingparameter",
      &pvalue->routingparameter);

   rtPrintCloseBrace ();
}

void asn1Print_RUA_Gsm_map_IDNNS_routingbasis_spare1
   (const char* name, RUA_Gsm_map_IDNNS_routingbasis_spare1* pvalue)
{
   rtPrintOpenBrace (name);

   asn1Print_RUA_RoutingParameter ("routingparameter",
      &pvalue->routingparameter);

   rtPrintCloseBrace ();
}

void asn1Print_RUA_Gsm_map_IDNNS_routingbasis
   (const char* name, RUA_Gsm_map_IDNNS_routingbasis* pvalue)
{
   rtPrintOpenBrace (name);

   switch (pvalue->t) {
      case 1: {
         asn1Print_RUA_Gsm_map_IDNNS_routingbasis_localPTMSI ("localPTMSI",
            pvalue->u.localPTMSI);
         break;
      }
      case 2: {
         asn1Print_RUA_Gsm_map_IDNNS_routingbasis_tMSIofsamePLMN ("tMSIofsamePLMN",
            pvalue->u.tMSIofsamePLMN);
         break;
      }
      case 3: {
         asn1Print_RUA_Gsm_map_IDNNS_routingbasis_tMSIofdifferentPLMN ("tMSIofdifferentPLMN",
            pvalue->u.tMSIofdifferentPLMN);
         break;
      }
      case 4: {
         asn1Print_RUA_Gsm_map_IDNNS_routingbasis_iMSIresponsetopaging ("iMSIresponsetopaging",
            pvalue->u.iMSIresponsetopaging);
         break;
      }
      case 5: {
         asn1Print_RUA_Gsm_map_IDNNS_routingbasis_iMSIcauseUEinitiatedEvent ("iMSIcauseUEinitiatedEvent",
            pvalue->u.iMSIcauseUEinitiatedEvent);
         break;
      }
      case 6: {
         asn1Print_RUA_Gsm_map_IDNNS_routingbasis_iMEI ("iMEI",
            pvalue->u.iMEI);
         break;
      }
      case 7: {
         asn1Print_RUA_Gsm_map_IDNNS_routingbasis_spare2 ("spare2",
            pvalue->u.spare2);
         break;
      }
      case 8: {
         asn1Print_RUA_Gsm_map_IDNNS_routingbasis_spare1 ("spare1",
            pvalue->u.spare1);
         break;
      }
      default:;
   }

   rtPrintCloseBrace ();
}

void asn1Print_RUA_Gsm_map_IDNNS
   (const char* name, RUA_Gsm_map_IDNNS* pvalue)
{
   rtPrintOpenBrace (name);

   asn1Print_RUA_Gsm_map_IDNNS_routingbasis ("routingbasis",
      &pvalue->routingbasis);

   rtPrintIndent ();
   rtPrintBoolean ("dummy", pvalue->dummy);

   rtPrintCloseBrace ();
}

void asn1Print_RUA_IntraDomainNasNodeSelector_version_release99_cn_Type
   (const char* name, RUA_IntraDomainNasNodeSelector_version_release99_cn_Type* pvalue)
{
   rtPrintOpenBrace (name);

   switch (pvalue->t) {
      case 1: {
         asn1Print_RUA_Gsm_map_IDNNS ("gsm_Map_IDNNS",
            pvalue->u.gsm_Map_IDNNS);
         break;
      }
      case 2: {
         asn1Print_RUA_Ansi_41_IDNNS ("ansi_41_IDNNS",
            pvalue->u.ansi_41_IDNNS);
         break;
      }
      default:;
   }

   rtPrintCloseBrace ();
}

void asn1Print_RUA_IntraDomainNasNodeSelector_version_release99
   (const char* name, RUA_IntraDomainNasNodeSelector_version_release99* pvalue)
{
   rtPrintOpenBrace (name);

   asn1Print_RUA_IntraDomainNasNodeSelector_version_release99_cn_Type ("cn_Type",
      &pvalue->cn_Type);

   rtPrintCloseBrace ();
}

void asn1Print_RUA_IntraDomainNasNodeSelector_version_later
   (const char* name, RUA_IntraDomainNasNodeSelector_version_later* pvalue)
{
   rtPrintOpenBrace (name);

   asn1Print_RUA_IntraDomainNasNodeSelector_version_later_futurecoding ("futurecoding",
      &pvalue->futurecoding);

   rtPrintCloseBrace ();
}

void asn1Print_RUA_IntraDomainNasNodeSelector_version
   (const char* name, RUA_IntraDomainNasNodeSelector_version* pvalue)
{
   rtPrintOpenBrace (name);

   switch (pvalue->t) {
      case 1: {
         asn1Print_RUA_IntraDomainNasNodeSelector_version_release99 ("release99",
            pvalue->u.release99);
         break;
      }
      case 2: {
         asn1Print_RUA_IntraDomainNasNodeSelector_version_later ("later",
            pvalue->u.later);
         break;
      }
      default:;
   }

   rtPrintCloseBrace ();
}

void asn1Print_RUA_IntraDomainNasNodeSelector
   (const char* name, RUA_IntraDomainNasNodeSelector* pvalue)
{
   rtPrintOpenBrace (name);

   asn1Print_RUA_IntraDomainNasNodeSelector_version ("version",
      &pvalue->version);

   rtPrintCloseBrace ();
}

void asn1Print_RUA_Cause
   (const char* name, RUA_Cause* pvalue)
{
   rtPrintOpenBrace (name);

   switch (pvalue->t) {
      case 1: {
         asn1Print_RUA_CauseRadioNetwork ("radioNetwork",
            &pvalue->u.radioNetwork);
         break;
      }
      case 2: {
         asn1Print_RUA_CauseTransport ("transport",
            &pvalue->u.transport);
         break;
      }
      case 3: {
         asn1Print_RUA_CauseProtocol ("protocol",
            &pvalue->u.protocol);
         break;
      }
      case 4: {
         asn1Print_RUA_CauseMisc ("misc",
            &pvalue->u.misc);
         break;
      }
      case 5: {
         rtPrintIndent ();
         rtPrintHexStr ("extElem1",
            pvalue->u.extElem1->numocts,
            pvalue->u.extElem1->data);
         break;
      }
      default:;
   }

   rtPrintCloseBrace ();
}

void asn1Print_RUA_CriticalityDiagnostics_IE_List_element
   (const char* name, RUA_CriticalityDiagnostics_IE_List_element* pvalue)
{
   rtPrintOpenBrace (name);

   asn1Print_RUA_Criticality ("iECriticality",
      &pvalue->iECriticality);

   asn1Print_RUA_ProtocolIE_ID ("iE_ID",
      &pvalue->iE_ID);

   asn1Print_RUA_TypeOfError ("typeOfError",
      &pvalue->typeOfError);

   if (pvalue->m.iE_ExtensionsPresent) {
      asn1Print_RUA_ProtocolExtensionContainer ("iE_Extensions",
         &pvalue->iE_Extensions);
   }

   rtPrintOpenTypeExtBraceText ("extElem1", &pvalue->extElem1);

   rtPrintCloseBrace ();
}

void asn1Print_RUA_CriticalityDiagnostics_IE_List
   (const char* name, RUA_CriticalityDiagnostics_IE_List* pvalue)
{
   RUA_CriticalityDiagnostics_IE_List_element* pdata0;
   OSRTDListNode* pnode;
   char namebuf[512];
   OSUINT32 xx1;

   pnode = pvalue->head;
   for (xx1 = 0; xx1 < pvalue->count; xx1++) {
      pdata0 = (RUA_CriticalityDiagnostics_IE_List_element*) pnode->data;
      os_snprintf (namebuf, 512, "%s[%d]", name, xx1);
      asn1Print_RUA_CriticalityDiagnostics_IE_List_element (namebuf,
         pdata0);
      pnode = pnode->next;
   }
}

void asn1Print_RUA_CriticalityDiagnostics
   (const char* name, RUA_CriticalityDiagnostics* pvalue)
{
   rtPrintOpenBrace (name);

   if (pvalue->m.procedureCodePresent) {
      asn1Print_RUA_ProcedureCode ("procedureCode",
         &pvalue->procedureCode);
   }

   if (pvalue->m.triggeringMessagePresent) {
      asn1Print_RUA_TriggeringMessage ("triggeringMessage",
         &pvalue->triggeringMessage);
   }

   if (pvalue->m.procedureCriticalityPresent) {
      asn1Print_RUA_Criticality ("procedureCriticality",
         &pvalue->procedureCriticality);
   }

   if (pvalue->m.iEsCriticalityDiagnosticsPresent) {
      asn1Print_RUA_CriticalityDiagnostics_IE_List ("iEsCriticalityDiagnostics",
         &pvalue->iEsCriticalityDiagnostics);
   }

   if (pvalue->m.iE_ExtensionsPresent) {
      asn1Print_RUA_ProtocolExtensionContainer ("iE_Extensions",
         &pvalue->iE_Extensions);
   }

   rtPrintOpenTypeExtBraceText ("extElem1", &pvalue->extElem1);

   rtPrintCloseBrace ();
}

