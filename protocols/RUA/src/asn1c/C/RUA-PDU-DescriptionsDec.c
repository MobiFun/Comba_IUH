/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.1.4, Date: 09-Jul-2012.
 */
#include "RUA-PDU-Descriptions.h"
#include "RUA-Constants.h"
#include "rtxsrc/rtxCommon.h"

EXTERN int asn1PD_RUA_InitiatingMessage (OSCTXT* pctxt, RUA_InitiatingMessage* pvalue)
{
   int stat = 0;

   /* decode procedureCode */

   stat = asn1PD_RUA_ProcedureCode (pctxt, &pvalue->procedureCode);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   /* decode criticality */

   stat = asn1PD_RUA_Criticality (pctxt, &pvalue->criticality);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   /* decode value */

   stat = pd_OpenType (pctxt, &pvalue->value.data, &pvalue->value.numocts);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return (stat);
}

EXTERN int asn1PD_RUA_SuccessfulOutcome (OSCTXT* pctxt, RUA_SuccessfulOutcome* pvalue)
{
   int stat = 0;

   /* decode procedureCode */

   stat = asn1PD_RUA_ProcedureCode (pctxt, &pvalue->procedureCode);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   /* decode criticality */

   stat = asn1PD_RUA_Criticality (pctxt, &pvalue->criticality);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   /* decode value */

   stat = pd_OpenType (pctxt, &pvalue->value.data, &pvalue->value.numocts);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return (stat);
}

EXTERN int asn1PD_RUA_UnsuccessfulOutcome (OSCTXT* pctxt, RUA_UnsuccessfulOutcome* pvalue)
{
   int stat = 0;

   /* decode procedureCode */

   stat = asn1PD_RUA_ProcedureCode (pctxt, &pvalue->procedureCode);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   /* decode criticality */

   stat = asn1PD_RUA_Criticality (pctxt, &pvalue->criticality);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   /* decode value */

   stat = pd_OpenType (pctxt, &pvalue->value.data, &pvalue->value.numocts);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   return (stat);
}

EXTERN int asn1PD_RUA_RUA_PDU (OSCTXT* pctxt, RUA_RUA_PDU* pvalue)
{
   int stat = 0;
   OSUINT32 ui;
   ASN1OpenType openType;
   OSBOOL extbit = FALSE;

   /* extension bit */

   stat = PD_BIT (pctxt, &extbit);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   if (!extbit) {
      stat = pd_ConsUnsigned (pctxt, &ui, 0, OSUINTCONST(2));
      if (stat != 0) return LOG_RTERR (pctxt, stat);
      else pvalue->t = ui + 1;

      switch (ui) {
         /* initiatingMessage */
         case 0:
            pvalue->u.initiatingMessage = rtxMemAllocType (pctxt, 
               RUA_InitiatingMessage);

            if (pvalue->u.initiatingMessage == NULL)
               return LOG_RTERR (pctxt, RTERR_NOMEM);

            asn1Init_RUA_InitiatingMessage (pvalue->u.initiatingMessage);

            asn1Init_RUA_InitiatingMessage (pvalue->u.initiatingMessage);

            stat = asn1PD_RUA_InitiatingMessage (pctxt, pvalue->u.initiatingMessage);
            if (stat != 0) return LOG_RTERR (pctxt, stat);

            break;

         /* successfulOutcome */
         case 1:
            pvalue->u.successfulOutcome = rtxMemAllocType (pctxt, 
               RUA_SuccessfulOutcome);

            if (pvalue->u.successfulOutcome == NULL)
               return LOG_RTERR (pctxt, RTERR_NOMEM);

            asn1Init_RUA_SuccessfulOutcome (pvalue->u.successfulOutcome);

            asn1Init_RUA_SuccessfulOutcome (pvalue->u.successfulOutcome);

            stat = asn1PD_RUA_SuccessfulOutcome (pctxt, pvalue->u.successfulOutcome);
            if (stat != 0) return LOG_RTERR (pctxt, stat);

            break;

         /* unsuccessfulOutcome */
         case 2:
            pvalue->u.unsuccessfulOutcome = rtxMemAllocType (pctxt, 
               RUA_UnsuccessfulOutcome);

            if (pvalue->u.unsuccessfulOutcome == NULL)
               return LOG_RTERR (pctxt, RTERR_NOMEM);

            asn1Init_RUA_UnsuccessfulOutcome (pvalue->u.unsuccessfulOutcome);

            asn1Init_RUA_UnsuccessfulOutcome (pvalue->u.unsuccessfulOutcome);

            stat = asn1PD_RUA_UnsuccessfulOutcome (pctxt, pvalue->u.unsuccessfulOutcome);
            if (stat != 0) return LOG_RTERR (pctxt, stat);

            break;

         default:
            return LOG_RTERR (pctxt, RTERR_INVOPT);
      }
   }
   else {
      stat = pd_SmallNonNegWholeNumber (pctxt, &ui);
      if (stat != 0) return LOG_RTERR (pctxt, stat);
      else pvalue->t = ui + 4;

      if (pvalue->t < 4) return LOG_RTERR (pctxt, RTERR_INVOPT);
      stat = PD_BYTE_ALIGN (pctxt);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      stat = pd_OpenType (pctxt, &openType.data, &openType.numocts);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      pvalue->u.extElem1 = rtxMemAllocType (pctxt, ASN1OpenType);
      if (pvalue->u.extElem1 == NULL)
         return LOG_RTERR (pctxt, RTERR_NOMEM);
      pvalue->t = 4;

      pvalue->u.extElem1->data = openType.data;
      pvalue->u.extElem1->numocts = openType.numocts;

   }

   return (stat);
}
