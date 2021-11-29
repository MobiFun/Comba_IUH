/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/RUA/tags/RUA-1.3.0/src/tstmRUA.h $
$Author: roger $
$Date: 2012-07-24 15:28:50 +0200 (Tue, 24 Jul 2012) $
$Rev: 53422 $
--------------------------------------------------------------*/
#ifndef TSTMRUA_H_
#define TSTMRUA_H_

#define tstmRUA_WSN_SIG(name,sapi) \
    tstmRUA_WSN_TYPE(name,sapi); tstmRUA_WSN_FMAT(name)

#define tstmRUA_WSN_TYPE(name,sapi) \
    tmSidStatic(tstmRUA_SAPI_TYPE2SID(sapi,tstmRUA_TYPE_##name),#name)

#define tstmRUA_WSN_FMAT(name) \
    tmWsnTypedef(#name,tstmRUA_FMAT_##name)

#define tstmRUA_SAPI_TYPE2SID(sapi,type) \
	((sapi<<16)|type)


/**********************************************************
*
*       RUA message type (internal to Tstm)
*
***********************************************************/

/*****	OM	*****/
#define tstmRUA_TYPE_RUA_OM_CFG                    0x0001
#define tstmRUA_TYPE_RUA_OM_CFG_ACK                0x0002

/*****RUA Primitives***/
#define tstmRUA_TYPE_RUA_CONNECT                   0x0101
#define tstmRUA_TYPE_RUA_DIRECTTRANSFER            0x0102
#define tstmRUA_TYPE_RUA_DISCONNECT                0x0103
#define tstmRUA_TYPE_RUA_CONNECTIONLESSTRANSFER    0x0104
#define tstmRUA_TYPE_RUA_ERRORINDICATION           0x0105
#define tstmRUA_TYPE_RUA_PRIVATEMESSAGE            0x0106

/**********************************************************
*
*       RUA general  FORMAT
*
***********************************************************/
#define tstmRUA_FMAT_RUA_OM_CFG "VOID"
#define tstmRUA_FMAT_RUA_OM_CFG_ACK "VOID"

#define tstmRUA_FMAT_INTRADOMAIN_NASNODE_SELECTOR \
	"STRUCT "\
	"{INT    Tag} "\
	"{HEXSTR Value}"

#define tstmRUA_FMAT_CRITICALITY_DIAGNOSTICS_IE_ITEM \
	"STRUCT "\
	"{UINT				    IECriticality} "\
	"{USHORT				IE_ID} "\
	"{UINT				    TypeOfError}"

#define tstmRUA_FMAT_CRITICALITY_DIAGNOSTICS \
	"STRUCT "\
	"{UCHAR											ProcedureCode} "\
	"{UINT 										    TriggeringMessage} " \
	"{UINT										    ProcedureCriticality} " \
	"{LIST_OF	CRITICALITY_DIAGNOSTICS_IE_ITEM		IEsCriticalityDiagnostics}"

#define tstmRUA_FMAT_CAUSE \
	"STRUCT "\
	"{INT 			Tag} "\
	"{UINT 			Value}"

#define tstmRUA_FMAT_RUA_CONNECT \
    "STRUCT  "\
	"{UINT CnDomain} "\
	"{UINT ContextId} "\
	"{STRUCTURE INTRADOMAIN_NASNODE_SELECTOR IntraDomainNasNodeSelector} "\
	"{UINT EstCause} "\
	"{BINSTR RanapMsg} "\
	"{STRING ApId}"

// number of fields of tstmRUA_FMAT_RUA_CONNECT
#define tstmRUA_PDU_N_IES_CONNECT			6

#define tstmRUA_FMAT_RUA_DIRECTTRANSFER \
    "STRUCT "\
    "{UINT CnDomain} "\
    "{UINT ContextId} "\
    "{BINSTR RanapMsg} "\
    "{STRING ApId}"


#define tstmRUA_FMAT_RUA_DISCONNECT \
    "STRUCT "\
	"{UINT CnDomain} "\
	"{UINT ContextId} "\
	"{STRUCTURE CAUSE Cause} "\
	"{BINSTR RanapMsg} "\
	"{STRING ApId}"

#define tstmRUA_FMAT_RUA_CONNECTIONLESSTRANSFER \
     "STRUCT "\
	 "{BINSTR RanapMsg} "\
	 "{STRING ApId}"

#define tstmRUA_FMAT_RUA_ERRORINDICATION \
	"STRUCT "\
    "{STRUCTURE CAUSE Cause} "\
	"{STRUCTURE CRITICALITY_DIAGNOSTICS CriticalDiag} "\
	"{STRING ApId}"

#define tstmRUA_FMAT_RUA_PRIVATEMESSAGE "VOID"
#endif
