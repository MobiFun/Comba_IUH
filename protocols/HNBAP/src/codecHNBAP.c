/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/HNBAP/tags/HNBAP-1.3.0/src/codecHNBAP.c $
$Author: roger $
$Date: 2012-07-17 14:51:24 +0200 (Tue, 17 Jul 2012) $
$Rev: 53209 $
----------------------------------------------------------------
Description : HNBAP SIGNALS ENCODING/DECODING
--------------------------------------------------------------*/

/*............................................................*/

#include "codecHNBAP.h"
#include "defs.h"
#include "encHNBAP.h"
#include "decHNBAP.h"
#include <tcl.h>


#define CALLBACKOBJ(name) \
    int name(ClientData cd, tmITPt *itp, int argc, Tcl_Obj *CONST argv[])

#define EARGC_OBJ \
    {tmAbort("wrong number of arguments given to %s",Tcl_GetStringFromObj(argv[0],NULL)); \
    return TCL_ERROR;}

        /*N.B. sapi is an ushort*/
#define SAPI_TYPE2SID( sapi, type )		( (sapi<<16) | (type) )

        /*N.B. sapi is an ushort*/
#define WSN_SID( name, sapi, type ) \
        tmSidStatic( SAPI_TYPE2SID( sapi, type ), #name )

#define WSN_TYPE( name ) \
    tmWsnTypedef( #name, tstmHNBAP_FMAT_##name )

        /*N.B. sapi is an ushort*/
#define WSN_SIG( name, sapi ) \
    WSN_SID( name, sapi, tstmHNBAP_TYPE_##name ); WSN_TYPE( name )

/*	static variables	*/
static uint hnbapSapi;
static OSOCTET Pdu[defsPduMAX_SIZE_BUF];

/*	prototypes	*/
/*
tatic int codecHNBAPEnc( uint type, OSOCTET *buf_out, uint *len_out);
int codecHNBAPDec( uchar *PduPtr, uint PduLen );
*/

CALLBACKOBJ(HNBAPSigToPdu)
{
	Tcl_Obj *ResultPtr;
	int PduLen = 0;
	uchar *SigVarName;
	uint type;

	if(argc!=2) EARGC_OBJ;

	if( (SigVarName = Tcl_GetStringFromObj(argv[1], NULL)) == NULL )
		return tmTclErrObj(itp,"HNBAPSigToPdu: Tcl_GetStringFromObj error\n");

	ENC_START_OBJ(itp, SigVarName);

	/* Get 0th field of the signal (signal name), needed to convert
	 * in the sid to obtain the type */

	type = tmSidId(ENC_STRING_OBJ(itp, 0, "")) & 0x0000ffff;
	if( codecHNBAPEnc( type, Pdu, &PduLen ) != TCL_OK )
		tmAbort("HNBAPSigToPdu: encoding HNBAP signal aborted");
	ResultPtr = Tcl_GetObjResult(itp);

	Tcl_SetByteArrayObj(ResultPtr,Pdu,PduLen);

	return TCL_OK;
}


/*	encoding HNBAP messages	*/
 int codecHNBAPEnc( uint type, OSOCTET *buf_out, uint *len_outP)
{
	// Check PDU type
    switch( type )
	{
		case tstmHNBAP_TYPE_HNB_REGISTER:
			if( encHNBAPRegister (buf_out, len_outP) ) {
				return TCL_ERROR;
			}
			break;
		case tstmHNBAP_TYPE_HNB_REGISTERACC:
		 	if( encHNBAPHNBRegisterAccept(buf_out, len_outP) ){
				return TCL_ERROR;
			}
		  	break;
		case tstmHNBAP_TYPE_HNB_REGISTERREJ:
			if( encHNBAPHNBRegisterReject(buf_out, len_outP) ){
				return TCL_ERROR;
			}
		  	break;
		case tstmHNBAP_TYPE_HNB_DEREGISTER:
		  	if( encHNBAPHNBDeRegister(buf_out, len_outP) ){
				return TCL_ERROR;
			}
		  	break;
		case tstmHNBAP_TYPE_HNB_UEREGISTER:
		  	if( encHNBAPUERegisterRequest(buf_out, len_outP) ){
				return TCL_ERROR;
			}
		  	break;
		case tstmHNBAP_TYPE_HNB_UEREGISTERACC:
		  	if( encHNBAPUERegisterAccept(buf_out, len_outP) ){
				return TCL_ERROR;
			}
		  	break;
		case tstmHNBAP_TYPE_HNB_UEREGISTERREJ:
			if( encHNBAPUERegisterReject(buf_out, len_outP) ){
				return TCL_ERROR;
			}
		  	break;
		case tstmHNBAP_TYPE_HNB_UEDEREGISTER:
		  	if( encHNBAPUEDeRegister(buf_out, len_outP) ){
				return TCL_ERROR;
			}
		  	break;
		case tstmHNBAP_TYPE_HNB_ERRORINDICATION:
		 	if( encHNBAPErrorIndication(buf_out, len_outP) ){
				return TCL_ERROR;
			}
		  	break;
		case tstmHNBAP_TYPE_HNB_PRIVATEMESSAGE:
			if( encHNBAPPrivateMessage(buf_out, len_outP) ){
				return TCL_ERROR;
			}
		  	break;
		default:
			tmAbort( "codecHNBAPEnc: type %u not managed",type );
	}

	return TCL_OK;
}


CALLBACKOBJ(HNBAPPduToSig)
{
	Tcl_Obj *PduObj;
    uchar *PduPtr;
    int PduLen;

    if(argc!=2) EARGC_OBJ;

    if( (PduObj = Tcl_ObjGetVar2(itp, argv[1], NULL, 0)) == NULL )
        return tmTclErrObj(itp,"HNBAPPduToSig: 2nd arg Tcl_ObjGetVar2 error\n");
    if((PduPtr = Tcl_GetByteArrayFromObj(PduObj,&PduLen))==NULL)
        return tmTclErrObj(itp,"HNBAPPduToSig: Tcl_GetByteArrayFromObj error\n");

    return codecHNBAPDec(PduPtr, PduLen);
}


/*	decoding HNBAP messages	*/
int codecHNBAPDec( uchar *PduPtr, uint PduLen )
{
	uint t_proc = 0;
    uint t_code = 0;
	uint len_out = 0;
    uint type;
	//OSOCTET buf_in[defsPduMAX_SIZE_BUF];
	OSOCTET out_pdu[defsPduMAX_SIZE_BUF];

	// Store the content of PduPtr into buf_in
	//memcpy(buf_in, PduPtr, PduLen );
	//Init output memory
	memset(out_pdu, 0, sizeof(out_pdu) );

	if( PduLen > 0 ) {

		// Call decoding function
		if( decHNBAPPdu( &t_proc, &t_code, PduPtr, out_pdu, &len_out ) )
			return TCL_ERROR;
	}

	// Set type
	type = (t_proc << 8 ) + t_code;

	DEC_START_OBJ();

	if ( PduLen == 0 ) {

		DEC_NOTPRESENT_OBJ(tm_compatITP());

	} else {

		DEC_TYPE_OBJ( tm_compatITP(), tstmHNBAP_SAPI_TYPE2SID(hnbapSapi, type));

		switch( type )
		{
			case tstmHNBAP_TYPE_HNB_REGISTER:
				decHNBAPRegister (out_pdu,  len_out);
				break;
			case tstmHNBAP_TYPE_HNB_REGISTERACC:
			  	decHNBAPHNBRegisterAccept(out_pdu, len_out);
			  	break;
			case tstmHNBAP_TYPE_HNB_REGISTERREJ:
			  	decHNBAPHNBRegisterReject(out_pdu, len_out);
			  	break;
			case tstmHNBAP_TYPE_HNB_DEREGISTER:
			  	decHNBAPHNBDeRegister(out_pdu, len_out);
			  	break;
			case tstmHNBAP_TYPE_HNB_UEREGISTER:
			 	decHNBAPUERegisterRequest(out_pdu, len_out);
			  	break;
			case tstmHNBAP_TYPE_HNB_UEREGISTERACC:
			  	decHNBAPUERegisterAccept(out_pdu, len_out);
			  	break;
			case tstmHNBAP_TYPE_HNB_UEREGISTERREJ:
			  	decHNBAPUERegisterReject(out_pdu, len_out);
			  	break;
			case tstmHNBAP_TYPE_HNB_UEDEREGISTER:
			  	decHNBAPUEDeRegister(out_pdu, len_out);
			  	break;
			case tstmHNBAP_TYPE_HNB_ERRORINDICATION:
			  	decHNBAPErrorIndication(out_pdu, len_out);
			  	break;
			case tstmHNBAP_TYPE_HNB_PRIVATEMESSAGE:
			  	decHNBAPPrivateMessage(out_pdu, len_out);
			  	break;
			default:
				tmAbort( "codecHNBAPDec: unexpected type %u\t(t_proc=%d\tt_code=%d)",type,t_proc,t_code );
		}
	}

	DEC_SET_VAR_OBJ( tm_compatITP(), "_sigpdu" );

	return TCL_OK;
}


/*	initialization	*/
int codecHNBAPInit(tmITPt* itp, ushort hnbap_sapi)
{

	tmTclCmdNewObj(itp, "HNBAPSigToPdu", HNBAPSigToPdu);
	tmTclCmdNewObj(itp, "HNBAPPduToSig", HNBAPPduToSig);

	hnbapSapi = hnbap_sapi;

	/*	inter-layer communication	*/
	/*	OM	
	tstmHNBAP_WSN_SIG( HNBAP_OM_CFG,			hnbap_om_sapi );
	tstmHNBAP_WSN_SIG( HNBAP_OM_CFG_ACK,		hnbap_om_sapi );
	*/

	/*	HNBAP IEs	*/
	tstmHNBAP_WSN_FMAT(GEOGRAPHICAL_COORDINATES);
	tstmHNBAP_WSN_FMAT(ALTITUDE_AND_DIRECTION);
	tstmHNBAP_WSN_FMAT(GEOGRAPHICAL_LOC);
	tstmHNBAP_WSN_FMAT(CGI);
	tstmHNBAP_WSN_FMAT(UTRAN_CELLID);
	tstmHNBAP_WSN_FMAT(MACRO_COVERAGE_INFO);
	tstmHNBAP_WSN_FMAT(HNB_LOC_INFO);

	tstmHNBAP_WSN_FMAT(CAUSE);
	tstmHNBAP_WSN_FMAT(LAI);
	tstmHNBAP_WSN_FMAT(TMSILAI);
	tstmHNBAP_WSN_FMAT(RAI);
	tstmHNBAP_WSN_FMAT(PTMSIRAI);
	tstmHNBAP_WSN_FMAT(UE_ID);
	tstmHNBAP_WSN_FMAT(IMSIESN);
	tstmHNBAP_WSN_FMAT(UE_CAP);
	tstmHNBAP_WSN_FMAT(CRITICALITY_DIAGNOSTICS_IE_ITEM);
	tstmHNBAP_WSN_FMAT(CRITICALITY_DIAGNOSTICS);

	/*	HNBAP procedures	*/
	tstmHNBAP_WSN_SIG(HNB_REGISTER            ,hnbap_sapi );
	tstmHNBAP_WSN_SIG(HNB_REGISTERACC         ,hnbap_sapi );
	tstmHNBAP_WSN_SIG(HNB_REGISTERREJ         ,hnbap_sapi );
	tstmHNBAP_WSN_SIG(HNB_DEREGISTER          ,hnbap_sapi );
	tstmHNBAP_WSN_SIG(HNB_UEREGISTER          ,hnbap_sapi );
	tstmHNBAP_WSN_SIG(HNB_UEREGISTERACC       ,hnbap_sapi );
	tstmHNBAP_WSN_SIG(HNB_UEREGISTERREJ       ,hnbap_sapi );
	tstmHNBAP_WSN_SIG(HNB_UEDEREGISTER        ,hnbap_sapi );
	tstmHNBAP_WSN_SIG(HNB_ERRORINDICATION     ,hnbap_sapi );
	tstmHNBAP_WSN_SIG(HNB_PRIVATEMESSAGE      ,hnbap_sapi );

	return 0;
}
