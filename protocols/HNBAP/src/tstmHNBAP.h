/*
 * tstmHNBAP.h
 *
 *  Created on: 2012-7-8
 *      Author: Leon
 */
 
#ifndef TSTMHNBAP_H_
#define TSTMHNBAP_H_

#define tstmHNBAP_WSN_SIG(name,sapi) \
    tstmHNBAP_WSN_TYPE(name,sapi); tstmHNBAP_WSN_FMAT(name)

#define tstmHNBAP_WSN_TYPE(name,sapi) \
    tmSidStatic(tstmHNBAP_SAPI_TYPE2SID(sapi,tstmHNBAP_TYPE_##name),#name)

#define tstmHNBAP_WSN_FMAT(name) \
    tmWsnTypedef(#name,tstmHNBAP_FMAT_##name)

#define tstmHNBAP_SAPI_TYPE2SID(sapi,type) \
	((sapi<<16)|type)

/**********************************************************
*
*       HNBAP message type (internal to Tstm)
*
***********************************************************/
/*****	OM	*****/
#define tstmHNBAP_TYPE_HNBAP_OM_CFG                    0x0001
#define tstmHNBAP_TYPE_HNBAP_OM_CFG_ACK                0x0002

/*****HNBAP Primitives***/
#define tstmHNBAP_TYPE_HNB_REGISTER                    0x0101
#define tstmHNBAP_TYPE_HNB_REGISTERACC                 0x0201
#define tstmHNBAP_TYPE_HNB_REGISTERREJ                 0x0301

#define tstmHNBAP_TYPE_HNB_DEREGISTER                  0x0102

#define tstmHNBAP_TYPE_HNB_UEREGISTER                  0x0103
#define tstmHNBAP_TYPE_HNB_UEREGISTERACC               0x0203
#define tstmHNBAP_TYPE_HNB_UEREGISTERREJ               0x0303

#define tstmHNBAP_TYPE_HNB_UEDEREGISTER                0x0104

#define tstmHNBAP_TYPE_HNB_ERRORINDICATION             0x0105

#define tstmHNBAP_TYPE_HNB_PRIVATEMESSAGE              0x0106



/**********************************************************
*
*       HNBAP general  FORMAT
*
***********************************************************/

#define tstmHNBAP_FMAT_HNBAP_OM_CFG "VOID"

#define tstmHNBAP_FMAT_HNBAP_OM_CFG_ACK "VOID"

#define tstmHNBAP_FMAT_GEOGRAPHICAL_COORDINATES \
	"STRUCT "\
	"{UINT LatitudeSign} "\
    "{UINT Latitude} "\
    "{INT Longitude}"

#define tstmHNBAP_FMAT_ALTITUDE_AND_DIRECTION \
	"STRUCT "\
	"{UINT DirectionOfAltitude} "\
    "{USHORT Altitude}"

#define tstmHNBAP_FMAT_GEOGRAPHICAL_LOC \
	"STRUCT "\
	"{GEOGRAPHICAL_COORDINATES GeographicalCoordinates} "\
    "{ALTITUDE_AND_DIRECTION AltitudeAndDirection}"

#define tstmHNBAP_FMAT_CGI \
	"STRUCT "\
	"{HEXSTR PLMNidentity} "\
	"{HEXSTR LAC} "\
	"{HEXSTR CI}"


#define tstmHNBAP_FMAT_UTRAN_CELLID \
	"STRUCT "\
	"{HEXSTR LAC} "\
	"{HEXSTR RAC} "\
	"{HEXSTR PLMNidentity} " \
	"{UINT CellID}"



#define tstmHNBAP_FMAT_MACRO_COVERAGE_INFO \
	"STRUCT "\
	"{INT Tag} "\
	"{HEXSTR Value}"  /*it can be UTRAN_CELLID or CGI */ \



#define tstmHNBAP_FMAT_HNB_LOC_INFO \
	"STRUCT "\
	"{STRUCTURE MACRO_COVERAGE_INFO MacroCoverageInformation} "\
	"{STRUCTURE GEOGRAPHICAL_LOC   GeographicalLocation}"

#define tstmHNBAP_FMAT_CAUSE \
	"STRUCT "\
	"{INT Tag} "\
	"{UINT Value}"

#define tstmHNBAP_FMAT_UE_ID \
	"STRUCT "\
	"{INT  Tag} "\
	"{HEXSTR Value}"

#define tstmHNBAP_FMAT_LAI \
	"STRUCT "\
	"{HEXSTR PLMNidentity} "\
	"{HEXSTR LAC}"

#define tstmHNBAP_FMAT_TMSILAI \
	"STRUCT "\
	"{HEXSTR Tmsi} "\
	"{LAI Lai}"

#define tstmHNBAP_FMAT_RAI \
  "STRUCT "\
  "{LAI LAI}  "\
  "{HEXSTR RAC}"

#define tstmHNBAP_FMAT_PTMSIRAI \
	"STRUCT "\
	"{HEXSTR Ptmsi} "\
	"{RAI Rai}"

#define tstmHNBAP_FMAT_IMSIESN \
	"STRUCT "\
	"{HEXSTR IMSIDS41} "\
	"{HEXSTR ESN}"

#define tstmHNBAP_FMAT_UE_CAP \
	"STRUCT "\
	"{UINT AS_Rel_Indicator} "\
	"{UINT CSG_Indicator}"


#define tstmHNBAP_FMAT_CRITICALITY_DIAGNOSTICS_IE_ITEM \
	"STRUCT "\
	"{UINT	IECriticality} "\
	"{USHORT IE_ID} "\
	"{UINT TypeOfError}"

#define tstmHNBAP_FMAT_CRITICALITY_DIAGNOSTICS \
	"STRUCT "\
	"{UCHAR	ProcedureCode} "\
	"{UINT 	TriggeringMessage} "\
	"{UINT	ProcedureCriticality} "\
	"{LIST_OF CRITICALITY_DIAGNOSTICS_IE_ITEM IEsCriticalityDiagnostics}"

#define tstmHNBAP_FMAT_HNB_REGISTER \
    "STRUCT "\
	"{HEXSTR HnbapId} "\
	"{STRUCTURE HNB_LOC_INFO HnbapLocInfo} "\
	"{HEXSTR PlmnId} "\
	"{UINT CellId} "\
	"{HEXSTR LAC} "\
	"{HEXSTR RAC} "\
	"{HEXSTR SAC} "\
	"{HEXSTR CsgId}"

// number of fields of tstmHNBAP_FMAT_HNB_REGISTER
#define tstmHNBAP_PDU_N_IES_REGISTER		8

#define tstmHNBAP_FMAT_HNB_REGISTERACC \
	"STRUCT "\
	"{USHORT RncId}"

#define tstmHNBAP_FMAT_HNB_REGISTERREJ \
	"STRUCT "\
	"{STRUCTURE CAUSE Cause} "\
	"{STRUCTURE CRITICALITY_DIAGNOSTICS CriticalDiag} "\
	"{UINT BackOffTimer}"

#define tstmHNBAP_FMAT_HNB_DEREGISTER \
	"STRUCT "\
	"{STRUCTURE CAUSE Cause} "\
	"{UINT BackOffTimer}"

// HNBAP UE REG procedure
#define tstmHNBAP_FMAT_HNB_UEREGISTER \
	" STRUCT "\
	"{STRUCTURE UE_ID UeId} "\
	"{UINT  RegCause} "\
	"{STRUCTURE UE_CAP UE_Cap}"

#define tstmHNBAP_FMAT_HNB_UEREGISTERACC \
	"STRUCT "\
	"{STRUCTURE UE_ID UeId} "\
	"{UINT ContextId}"

#define tstmHNBAP_FMAT_HNB_UEREGISTERREJ \
	"STRUCT "\
	"{STRUCTURE UE_ID UeId} "\
	"{STRUCTURE CAUSE Cause} "\
	"{STRUCTURE CRITICALITY_DIAGNOSTICS CriticalDiag}"

#define tstmHNBAP_FMAT_HNB_UEDEREGISTER \
	"STRUCT "\
	"{HEXSTR ContextId} "\
    "{STRUCTURE CAUSE Cause}"

#define tstmHNBAP_FMAT_HNB_ERRORINDICATION \
	"STRUCT "\
    "{STRUCTURE CAUSE Cause} "\
	"{STRUCTURE CRITICALITY_DIAGNOSTICS CriticalDiag}"


#define tstmHNBAP_FMAT_HNB_PRIVATEMESSAGE "VOID"
#endif

