/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.1.4, Date: 09-Jul-2012.
 */
#include "RUA-IEs.h"
#include "RUA-Constants.h"
#include "rtxsrc/rtxCommon.h"

EXTERN int asn1PE_RUA_CN_DomainIndicator (OSCTXT* pctxt, RUA_CN_DomainIndicator value)
{
   int stat = 0;
   OSUINT32 ui;

   switch (value) {
      case RUA_cs_domain: ui = 0; break;
      case RUA_ps_domain: ui = 1; break;
      default: rtxErrAddUIntParm (pctxt, value);
      return LOG_RTERR (pctxt, RTERR_INVENUM);
   }

   stat = pe_ConsUnsigned (pctxt, ui, 0, OSUINTCONST(1));
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return (stat);
}

EXTERN int asn1PE_RUA_Establishment_Cause (OSCTXT* pctxt, RUA_Establishment_Cause value)
{
   int stat = 0;
   OSUINT32 ui;
   OSBOOL extbit = FALSE;

   extbit = 0;

   switch (value) {
      case RUA_emergency_call: ui = 0; break;
      case RUA_normal_call: ui = 1; break;
      default: ui = value; extbit = 1;
   }

   /* extension bit */

   stat = pe_bit (pctxt, extbit);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   if (extbit) {
      stat = pe_SmallNonNegWholeNumber (pctxt, ui);
   }
   else {
      stat = pe_ConsUnsigned (pctxt, ui, 0, OSUINTCONST(1));
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }

   return (stat);
}

EXTERN int asn1PE_RUA_Context_ID (OSCTXT* pctxt, RUA_Context_ID* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, OSUINTCONST(24), OSUINTCONST(24), 0 };
   int stat = 0;

   stat = pu_addSizeConstraint (pctxt, &lsize1);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   stat = pe_BitString (pctxt, pvalue->numbits, pvalue->data);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return (stat);
}

EXTERN int asn1PE_RUA_Ansi_41_IDNNS (OSCTXT* pctxt, RUA_Ansi_41_IDNNS* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, OSUINTCONST(14), OSUINTCONST(14), 0 };
   int stat = 0;

   stat = pu_addSizeConstraint (pctxt, &lsize1);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   stat = pe_BitString (pctxt, pvalue->numbits, pvalue->data);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return (stat);
}

EXTERN int asn1PE_RUA_RANAP_Message (OSCTXT* pctxt, RUA_RANAP_Message value)
{
   int stat = 0;

   stat = pe_OctetString (pctxt, value.numocts, value.data);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return (stat);
}

EXTERN int asn1PE_RUA_RoutingParameter (OSCTXT* pctxt, RUA_RoutingParameter* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, OSUINTCONST(10), OSUINTCONST(10), 0 };
   int stat = 0;

   stat = pu_addSizeConstraint (pctxt, &lsize1);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   stat = pe_BitString (pctxt, pvalue->numbits, pvalue->data);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return (stat);
}

EXTERN int asn1PE_RUA_CauseRadioNetwork (OSCTXT* pctxt, RUA_CauseRadioNetwork value)
{
   int stat = 0;
   OSUINT32 ui;
   OSBOOL extbit = FALSE;

   extbit = 0;

   switch (value) {
      case RUA_normal: ui = 0; break;
      case RUA_connect_failed: ui = 1; break;
      case RUA_network_release: ui = 2; break;
      case RUA_unspecified: ui = 3; break;
      default: ui = value; extbit = 1;
   }

   /* extension bit */

   stat = pe_bit (pctxt, extbit);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   if (extbit) {
      stat = pe_SmallNonNegWholeNumber (pctxt, ui);
   }
   else {
      stat = pe_ConsUnsigned (pctxt, ui, 0, OSUINTCONST(3));
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }

   return (stat);
}

EXTERN int asn1PE_RUA_CauseTransport (OSCTXT* pctxt, RUA_CauseTransport value)
{
   int stat = 0;
   OSUINT32 ui;
   OSBOOL extbit = FALSE;

   extbit = 0;

   switch (value) {
      case RUA_transport_resource_unavailable: ui = 0; break;
      case RUA_unspecified_1: ui = 1; break;
      default: ui = value; extbit = 1;
   }

   /* extension bit */

   stat = pe_bit (pctxt, extbit);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   if (extbit) {
      stat = pe_SmallNonNegWholeNumber (pctxt, ui);
   }
   else {
      stat = pe_ConsUnsigned (pctxt, ui, 0, OSUINTCONST(1));
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }

   return (stat);
}

EXTERN int asn1PE_RUA_CauseProtocol (OSCTXT* pctxt, RUA_CauseProtocol value)
{
   int stat = 0;
   OSUINT32 ui;
   OSBOOL extbit = FALSE;

   extbit = 0;

   switch (value) {
      case RUA_transfer_syntax_error: ui = 0; break;
      case RUA_abstract_syntax_error_reject: ui = 1; break;
      case RUA_abstract_syntax_error_ignore_and_notify: ui = 2; break;
      case RUA_message_not_compatible_with_receiver_state: ui = 3; break;
      case RUA_semantic_error: ui = 4; break;
      case RUA_unspecified_2: ui = 5; break;
      case RUA_abstract_syntax_error_falsely_constructed_message: ui = 6; break;
      default: ui = value; extbit = 1;
   }

   /* extension bit */

   stat = pe_bit (pctxt, extbit);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   if (extbit) {
      stat = pe_SmallNonNegWholeNumber (pctxt, ui);
   }
   else {
      stat = pe_ConsUnsigned (pctxt, ui, 0, OSUINTCONST(6));
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }

   return (stat);
}

EXTERN int asn1PE_RUA_CauseMisc (OSCTXT* pctxt, RUA_CauseMisc value)
{
   int stat = 0;
   OSUINT32 ui;
   OSBOOL extbit = FALSE;

   extbit = 0;

   switch (value) {
      case RUA_processing_overload: ui = 0; break;
      case RUA_hardware_failure: ui = 1; break;
      case RUA_o_and_m_intervention: ui = 2; break;
      case RUA_unspecified_3: ui = 3; break;
      default: ui = value; extbit = 1;
   }

   /* extension bit */

   stat = pe_bit (pctxt, extbit);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   if (extbit) {
      stat = pe_SmallNonNegWholeNumber (pctxt, ui);
   }
   else {
      stat = pe_ConsUnsigned (pctxt, ui, 0, OSUINTCONST(3));
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }

   return (stat);
}

EXTERN int asn1PE_RUA_TypeOfError (OSCTXT* pctxt, RUA_TypeOfError value)
{
   int stat = 0;
   OSUINT32 ui;
   OSBOOL extbit = FALSE;

   extbit = 0;

   switch (value) {
      case RUA_not_understood: ui = 0; break;
      case RUA_missing: ui = 1; break;
      default: ui = value; extbit = 1;
   }

   /* extension bit */

   stat = pe_bit (pctxt, extbit);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   if (extbit) {
      stat = pe_SmallNonNegWholeNumber (pctxt, ui);
   }
   else {
      stat = pe_ConsUnsigned (pctxt, ui, 0, OSUINTCONST(1));
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }

   return (stat);
}

EXTERN int asn1PE_RUA_IntraDomainNasNodeSelector_version_later_futurecoding (OSCTXT* pctxt, RUA_IntraDomainNasNodeSelector_version_later_futurecoding* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, OSUINTCONST(15), OSUINTCONST(15), 0 };
   int stat = 0;

   stat = pu_addSizeConstraint (pctxt, &lsize1);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   stat = pe_BitString (pctxt, pvalue->numbits, pvalue->data);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return (stat);
}

EXTERN int asn1PE_RUA_Gsm_map_IDNNS_routingbasis_localPTMSI (OSCTXT* pctxt, RUA_Gsm_map_IDNNS_routingbasis_localPTMSI* pvalue)
{
   int stat = 0;

   /* encode routingparameter */

   stat = asn1PE_RUA_RoutingParameter (pctxt, &pvalue->routingparameter);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return (stat);
}

EXTERN int asn1PE_RUA_Gsm_map_IDNNS_routingbasis_tMSIofsamePLMN (OSCTXT* pctxt, RUA_Gsm_map_IDNNS_routingbasis_tMSIofsamePLMN* pvalue)
{
   int stat = 0;

   /* encode routingparameter */

   stat = asn1PE_RUA_RoutingParameter (pctxt, &pvalue->routingparameter);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return (stat);
}

EXTERN int asn1PE_RUA_Gsm_map_IDNNS_routingbasis_tMSIofdifferentPLMN (OSCTXT* pctxt, RUA_Gsm_map_IDNNS_routingbasis_tMSIofdifferentPLMN* pvalue)
{
   int stat = 0;

   /* encode routingparameter */

   stat = asn1PE_RUA_RoutingParameter (pctxt, &pvalue->routingparameter);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return (stat);
}

EXTERN int asn1PE_RUA_Gsm_map_IDNNS_routingbasis_iMSIresponsetopaging (OSCTXT* pctxt, RUA_Gsm_map_IDNNS_routingbasis_iMSIresponsetopaging* pvalue)
{
   int stat = 0;

   /* encode routingparameter */

   stat = asn1PE_RUA_RoutingParameter (pctxt, &pvalue->routingparameter);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return (stat);
}

EXTERN int asn1PE_RUA_Gsm_map_IDNNS_routingbasis_iMSIcauseUEinitiatedEvent (OSCTXT* pctxt, RUA_Gsm_map_IDNNS_routingbasis_iMSIcauseUEinitiatedEvent* pvalue)
{
   int stat = 0;

   /* encode routingparameter */

   stat = asn1PE_RUA_RoutingParameter (pctxt, &pvalue->routingparameter);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return (stat);
}

EXTERN int asn1PE_RUA_Gsm_map_IDNNS_routingbasis_iMEI (OSCTXT* pctxt, RUA_Gsm_map_IDNNS_routingbasis_iMEI* pvalue)
{
   int stat = 0;

   /* encode routingparameter */

   stat = asn1PE_RUA_RoutingParameter (pctxt, &pvalue->routingparameter);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return (stat);
}

EXTERN int asn1PE_RUA_Gsm_map_IDNNS_routingbasis_spare2 (OSCTXT* pctxt, RUA_Gsm_map_IDNNS_routingbasis_spare2* pvalue)
{
   int stat = 0;

   /* encode routingparameter */

   stat = asn1PE_RUA_RoutingParameter (pctxt, &pvalue->routingparameter);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return (stat);
}

EXTERN int asn1PE_RUA_Gsm_map_IDNNS_routingbasis_spare1 (OSCTXT* pctxt, RUA_Gsm_map_IDNNS_routingbasis_spare1* pvalue)
{
   int stat = 0;

   /* encode routingparameter */

   stat = asn1PE_RUA_RoutingParameter (pctxt, &pvalue->routingparameter);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return (stat);
}

EXTERN int asn1PE_RUA_Gsm_map_IDNNS_routingbasis (OSCTXT* pctxt, RUA_Gsm_map_IDNNS_routingbasis* pvalue)
{
   int stat = 0;

   /* Encode choice index value */

   stat = pe_ConsUnsigned (pctxt, pvalue->t - 1, 0, 7);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   /* Encode root element data value */

   switch (pvalue->t)
   {
      /* localPTMSI */
      case 1:
         stat = asn1PE_RUA_Gsm_map_IDNNS_routingbasis_localPTMSI (pctxt, pvalue->u.localPTMSI);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
         break;

      /* tMSIofsamePLMN */
      case 2:
         stat = asn1PE_RUA_Gsm_map_IDNNS_routingbasis_tMSIofsamePLMN (pctxt, pvalue->u.tMSIofsamePLMN);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
         break;

      /* tMSIofdifferentPLMN */
      case 3:
         stat = asn1PE_RUA_Gsm_map_IDNNS_routingbasis_tMSIofdifferentPLMN (pctxt, pvalue->u.tMSIofdifferentPLMN);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
         break;

      /* iMSIresponsetopaging */
      case 4:
         stat = asn1PE_RUA_Gsm_map_IDNNS_routingbasis_iMSIresponsetopaging (pctxt, pvalue->u.iMSIresponsetopaging);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
         break;

      /* iMSIcauseUEinitiatedEvent */
      case 5:
         stat = asn1PE_RUA_Gsm_map_IDNNS_routingbasis_iMSIcauseUEinitiatedEvent (pctxt, pvalue->u.iMSIcauseUEinitiatedEvent);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
         break;

      /* iMEI */
      case 6:
         stat = asn1PE_RUA_Gsm_map_IDNNS_routingbasis_iMEI (pctxt, pvalue->u.iMEI);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
         break;

      /* spare2 */
      case 7:
         stat = asn1PE_RUA_Gsm_map_IDNNS_routingbasis_spare2 (pctxt, pvalue->u.spare2);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
         break;

      /* spare1 */
      case 8:
         stat = asn1PE_RUA_Gsm_map_IDNNS_routingbasis_spare1 (pctxt, pvalue->u.spare1);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
         break;

      default:
         return LOG_RTERR (pctxt, RTERR_INVOPT);
   }

   return (stat);
}

EXTERN int asn1PE_RUA_Gsm_map_IDNNS (OSCTXT* pctxt, RUA_Gsm_map_IDNNS* pvalue)
{
   int stat = 0;

   /* encode routingbasis */

   stat = asn1PE_RUA_Gsm_map_IDNNS_routingbasis (pctxt, &pvalue->routingbasis);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   /* encode dummy */

   stat = pe_bit (pctxt, (OSBOOL)pvalue->dummy);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return (stat);
}

EXTERN int asn1PE_RUA_IntraDomainNasNodeSelector_version_release99_cn_Type (OSCTXT* pctxt, RUA_IntraDomainNasNodeSelector_version_release99_cn_Type* pvalue)
{
   int stat = 0;

   /* Encode choice index value */

   stat = pe_ConsUnsigned (pctxt, pvalue->t - 1, 0, 1);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   /* Encode root element data value */

   switch (pvalue->t)
   {
      /* gsm_Map_IDNNS */
      case 1:
         stat = asn1PE_RUA_Gsm_map_IDNNS (pctxt, pvalue->u.gsm_Map_IDNNS);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
         break;

      /* ansi_41_IDNNS */
      case 2:
         stat = asn1PE_RUA_Ansi_41_IDNNS (pctxt, pvalue->u.ansi_41_IDNNS);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
         break;

      default:
         return LOG_RTERR (pctxt, RTERR_INVOPT);
   }

   return (stat);
}

EXTERN int asn1PE_RUA_IntraDomainNasNodeSelector_version_release99 (OSCTXT* pctxt, RUA_IntraDomainNasNodeSelector_version_release99* pvalue)
{
   int stat = 0;

   /* encode cn_Type */

   stat = asn1PE_RUA_IntraDomainNasNodeSelector_version_release99_cn_Type (pctxt, &pvalue->cn_Type);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return (stat);
}

EXTERN int asn1PE_RUA_IntraDomainNasNodeSelector_version_later (OSCTXT* pctxt, RUA_IntraDomainNasNodeSelector_version_later* pvalue)
{
   int stat = 0;

   /* encode futurecoding */

   stat = asn1PE_RUA_IntraDomainNasNodeSelector_version_later_futurecoding (pctxt, &pvalue->futurecoding);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return (stat);
}

EXTERN int asn1PE_RUA_IntraDomainNasNodeSelector_version (OSCTXT* pctxt, RUA_IntraDomainNasNodeSelector_version* pvalue)
{
   int stat = 0;

   /* Encode choice index value */

   stat = pe_ConsUnsigned (pctxt, pvalue->t - 1, 0, 1);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   /* Encode root element data value */

   switch (pvalue->t)
   {
      /* release99 */
      case 1:
         stat = asn1PE_RUA_IntraDomainNasNodeSelector_version_release99 (pctxt, pvalue->u.release99);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
         break;

      /* later */
      case 2:
         stat = asn1PE_RUA_IntraDomainNasNodeSelector_version_later (pctxt, pvalue->u.later);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
         break;

      default:
         return LOG_RTERR (pctxt, RTERR_INVOPT);
   }

   return (stat);
}

EXTERN int asn1PE_RUA_IntraDomainNasNodeSelector (OSCTXT* pctxt, RUA_IntraDomainNasNodeSelector* pvalue)
{
   int stat = 0;

   /* encode version */

   stat = asn1PE_RUA_IntraDomainNasNodeSelector_version (pctxt, &pvalue->version);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return (stat);
}

EXTERN int asn1PE_RUA_Cause (OSCTXT* pctxt, RUA_Cause* pvalue)
{
   int stat = 0;
   OSBOOL extbit = FALSE;

   /* extension bit */

   extbit = (OSBOOL)(pvalue->t > 4);

   stat = pe_bit (pctxt, extbit);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = pe_ConsUnsigned (pctxt, pvalue->t - 1, 0, 3);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* radioNetwork */
         case 1:
            stat = asn1PE_RUA_CauseRadioNetwork (pctxt, pvalue->u.radioNetwork);
            if (stat != 0) return LOG_RTERR (pctxt, stat);
            break;

         /* transport */
         case 2:
            stat = asn1PE_RUA_CauseTransport (pctxt, pvalue->u.transport);
            if (stat != 0) return LOG_RTERR (pctxt, stat);
            break;

         /* protocol */
         case 3:
            stat = asn1PE_RUA_CauseProtocol (pctxt, pvalue->u.protocol);
            if (stat != 0) return LOG_RTERR (pctxt, stat);
            break;

         /* misc */
         case 4:
            stat = asn1PE_RUA_CauseMisc (pctxt, pvalue->u.misc);
            if (stat != 0) return LOG_RTERR (pctxt, stat);
            break;

         default:
            return LOG_RTERR (pctxt, RTERR_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = pe_SmallNonNegWholeNumber (pctxt, pvalue->t - 5);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      /* Encode extension element data value */

      stat = pe_OpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }

   return (stat);
}

EXTERN int asn1PE_RUA_CriticalityDiagnostics_IE_List_element (OSCTXT* pctxt, RUA_CriticalityDiagnostics_IE_List_element* pvalue)
{
   int stat = 0;
   OSBOOL extbit = FALSE;

   /* extension bit */

   extbit = (OSBOOL)(pvalue->extElem1.count > 0);

   stat = pe_bit (pctxt, extbit);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   stat = pe_bit (pctxt, (OSBOOL)pvalue->m.iE_ExtensionsPresent);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   /* encode iECriticality */

   stat = asn1PE_RUA_Criticality (pctxt, pvalue->iECriticality);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   /* encode iE_ID */

   stat = asn1PE_RUA_ProtocolIE_ID (pctxt, pvalue->iE_ID);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   /* encode typeOfError */

   stat = asn1PE_RUA_TypeOfError (pctxt, pvalue->typeOfError);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   /* encode iE_Extensions */

   if (pvalue->m.iE_ExtensionsPresent) {
      stat = asn1PE_RUA_ProtocolExtensionContainer (pctxt, &pvalue->iE_Extensions);
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = pe_SmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      /* encode optional bits */

      stat = pe_OpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = pe_OpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
      }
   }

   return (stat);
}

EXTERN int asn1PE_RUA_CriticalityDiagnostics_IE_List (OSCTXT* pctxt, RUA_CriticalityDiagnostics_IE_List* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, OSUINTCONST(1), OSUINTCONST(256), 0 };
   int stat = 0;
   OSRTDListNode* pnode;
   OSUINT32 xx1;

   /* encode length determinant */

   stat = pu_addSizeConstraint (pctxt, &lsize1);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   stat = pe_Length (pctxt, pvalue->count);
   if (stat < 0) return LOG_RTERR (pctxt, stat);

   /* encode elements */
   pnode = pvalue->head;

   for (xx1 = 0; xx1 < pvalue->count; xx1++) {
      stat = asn1PE_RUA_CriticalityDiagnostics_IE_List_element (pctxt, ((RUA_CriticalityDiagnostics_IE_List_element*)pnode->data));
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      pnode = pnode->next;
   }

   return (stat);
}

EXTERN int asn1PE_RUA_CriticalityDiagnostics (OSCTXT* pctxt, RUA_CriticalityDiagnostics* pvalue)
{
   int stat = 0;
   OSBOOL extbit = FALSE;

   /* extension bit */

   extbit = (OSBOOL)(pvalue->extElem1.count > 0);

   stat = pe_bit (pctxt, extbit);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   stat = pe_bit (pctxt, (OSBOOL)pvalue->m.procedureCodePresent);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   stat = pe_bit (pctxt, (OSBOOL)pvalue->m.triggeringMessagePresent);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   stat = pe_bit (pctxt, (OSBOOL)pvalue->m.procedureCriticalityPresent);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   stat = pe_bit (pctxt, (OSBOOL)pvalue->m.iEsCriticalityDiagnosticsPresent);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   stat = pe_bit (pctxt, (OSBOOL)pvalue->m.iE_ExtensionsPresent);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   /* encode procedureCode */

   if (pvalue->m.procedureCodePresent) {
      stat = asn1PE_RUA_ProcedureCode (pctxt, pvalue->procedureCode);
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }

   /* encode triggeringMessage */

   if (pvalue->m.triggeringMessagePresent) {
      stat = asn1PE_RUA_TriggeringMessage (pctxt, pvalue->triggeringMessage);
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }

   /* encode procedureCriticality */

   if (pvalue->m.procedureCriticalityPresent) {
      stat = asn1PE_RUA_Criticality (pctxt, pvalue->procedureCriticality);
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }

   /* encode iEsCriticalityDiagnostics */

   if (pvalue->m.iEsCriticalityDiagnosticsPresent) {
      stat = asn1PE_RUA_CriticalityDiagnostics_IE_List (pctxt, &pvalue->iEsCriticalityDiagnostics);
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }

   /* encode iE_Extensions */

   if (pvalue->m.iE_ExtensionsPresent) {
      stat = asn1PE_RUA_ProtocolExtensionContainer (pctxt, &pvalue->iE_Extensions);
      if (stat != 0) return LOG_RTERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = pe_SmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      /* encode optional bits */

      stat = pe_OpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = pe_OpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != 0) return LOG_RTERR (pctxt, stat);
      }
   }

   return (stat);
}

