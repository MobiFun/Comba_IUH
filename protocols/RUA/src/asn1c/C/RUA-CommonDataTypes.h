/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.1.4, Date: 09-Jul-2012.
 */
#ifndef RUA_COMMONDATATYPES_H
#define RUA_COMMONDATATYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include "rtkey.h"
#include "rtpersrc/asn1per.h"

/**
 * Header file for ASN.1 module RUA-CommonDataTypes
 */
/**************************************************************/
/*                                                            */
/*  ProcedureCode                                             */
/*                                                            */
/**************************************************************/

typedef OSUINT8 RUA_ProcedureCode;

EXTERN int asn1PE_RUA_ProcedureCode (OSCTXT* pctxt, RUA_ProcedureCode value);

EXTERN int asn1PD_RUA_ProcedureCode (OSCTXT* pctxt, RUA_ProcedureCode* pvalue);

EXTERN void asn1Print_RUA_ProcedureCode
   (const char* name, RUA_ProcedureCode* pvalue);

/**************************************************************/
/*                                                            */
/*  Criticality                                               */
/*                                                            */
/**************************************************************/

typedef enum {
   RUA_reject = 0,
   RUA_ignore = 1,
   RUA_notify = 2
} RUA_Criticality_Root;

typedef OSUINT32 RUA_Criticality;

EXTERN int asn1PE_RUA_Criticality (OSCTXT* pctxt, RUA_Criticality value);

EXTERN int asn1PD_RUA_Criticality (OSCTXT* pctxt, RUA_Criticality* pvalue);

EXTERN void asn1Print_RUA_Criticality
   (const char* name, RUA_Criticality* pvalue);

EXTERN const OSUTF8CHAR* RUA_Criticality_ToString (OSINT32 value);

EXTERN int RUA_Criticality_ToEnum (OSCTXT* pctxt,
   const OSUTF8CHAR* value, RUA_Criticality* pvalue);

/**************************************************************/
/*                                                            */
/*  ProtocolIE_ID                                             */
/*                                                            */
/**************************************************************/

typedef OSUINT16 RUA_ProtocolIE_ID;

EXTERN int asn1PE_RUA_ProtocolIE_ID (OSCTXT* pctxt, RUA_ProtocolIE_ID value);

EXTERN int asn1PD_RUA_ProtocolIE_ID (OSCTXT* pctxt, RUA_ProtocolIE_ID* pvalue);

EXTERN void asn1Print_RUA_ProtocolIE_ID
   (const char* name, RUA_ProtocolIE_ID* pvalue);

/**************************************************************/
/*                                                            */
/*  PrivateIE_ID                                              */
/*                                                            */
/**************************************************************/

/* Choice tag constants */

#define T_RUA_PrivateIE_ID_local        1
#define T_RUA_PrivateIE_ID_global       2

typedef struct EXTERN RUA_PrivateIE_ID {
   int t;
   union {
      /* t = 1 */
      OSUINT16 local;
      /* t = 2 */
      ASN1OBJID *global;
   } u;
} RUA_PrivateIE_ID;

EXTERN int asn1PE_RUA_PrivateIE_ID (OSCTXT* pctxt, RUA_PrivateIE_ID* pvalue);

EXTERN int asn1PD_RUA_PrivateIE_ID (OSCTXT* pctxt, RUA_PrivateIE_ID* pvalue);

EXTERN void asn1Print_RUA_PrivateIE_ID
   (const char* name, RUA_PrivateIE_ID* pvalue);

EXTERN void asn1Init_RUA_PrivateIE_ID (RUA_PrivateIE_ID* pvalue);

/**************************************************************/
/*                                                            */
/*  TriggeringMessage                                         */
/*                                                            */
/**************************************************************/

typedef enum {
   RUA_initiating_message = 0,
   RUA_successful_outcome = 1,
   RUA_unsuccessful_outcome = 2
} RUA_TriggeringMessage_Root;

typedef OSUINT32 RUA_TriggeringMessage;

EXTERN int asn1PE_RUA_TriggeringMessage (OSCTXT* pctxt, RUA_TriggeringMessage value);

EXTERN int asn1PD_RUA_TriggeringMessage (OSCTXT* pctxt, RUA_TriggeringMessage* pvalue);

EXTERN void asn1Print_RUA_TriggeringMessage
   (const char* name, RUA_TriggeringMessage* pvalue);

EXTERN const OSUTF8CHAR* RUA_TriggeringMessage_ToString (OSINT32 value);

EXTERN int RUA_TriggeringMessage_ToEnum (OSCTXT* pctxt,
   const OSUTF8CHAR* value, RUA_TriggeringMessage* pvalue);

/**************************************************************/
/*                                                            */
/*  Presence                                                  */
/*                                                            */
/**************************************************************/

typedef enum {
   RUA_optional = 0,
   RUA_conditional = 1,
   RUA_mandatory = 2
} RUA_Presence_Root;

typedef OSUINT32 RUA_Presence;

EXTERN int asn1PE_RUA_Presence (OSCTXT* pctxt, RUA_Presence value);

EXTERN int asn1PD_RUA_Presence (OSCTXT* pctxt, RUA_Presence* pvalue);

EXTERN void asn1Print_RUA_Presence
   (const char* name, RUA_Presence* pvalue);

EXTERN const OSUTF8CHAR* RUA_Presence_ToString (OSINT32 value);

EXTERN int RUA_Presence_ToEnum (OSCTXT* pctxt,
   const OSUTF8CHAR* value, RUA_Presence* pvalue);

/* Value definitions */

#define ASN1V_RUA_maxPrivateIEs 65535
#define ASN1V_RUA_maxProtocolExtensions 65535
#define ASN1V_RUA_maxProtocolIEs 65535

#ifdef __cplusplus
}
#endif

#endif
