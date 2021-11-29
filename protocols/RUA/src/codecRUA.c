/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/RUA/tags/RUA-1.3.0/src/codecRUA.c $
$Author: roger $
$Date: 2012-07-17 11:46:23 +0200 (Tue, 17 Jul 2012) $
$Rev: 53206 $
----------------------------------------------------------------
Description : RUA SIGNALS ENCODING/DECODING
--------------------------------------------------------------*/

/*............................................................*/

#include "codecRUA.h"
#include "tstmRUA.h"
#include "defs.h"
#include "encRUA.h"
#include "decRUA.h"
#include <tcl.h>
#include "tm_compat.h"

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
    tmWsnTypedef( #name, tstmRUA_FMAT_##name )

        /*N.B. sapi is an ushort*/
#define WSN_SIG( name, sapi ) \
    WSN_SID( name, sapi, tstmRUA_TYPE_##name ); WSN_TYPE( name )

/*	static variables	*/
static uint ruaSapi;
static OSOCTET Pdu[defsPduMAX_SIZE_BUF];



CALLBACKOBJ(RUASigToPdu)
{
	Tcl_Obj *ResultPtr;
	int PduLen = 0;
	uchar *SigVarName;
	uint type;

	if(argc!=2) EARGC_OBJ;

	if( (SigVarName = Tcl_GetStringFromObj(argv[1], NULL)) == NULL )
		return tmTclErrObj(itp,"RUASigToPdu: Tcl_GetStringFromObj error\n");

	ENC_START_OBJ(itp, SigVarName);

	/* Get 0th field of the signal (signal name), needed to convert
	 * in the sid to obtain the type */

	type = tmSidId(ENC_STRING_OBJ(itp, 0, "")) & 0x0000ffff;
	if( codecRUAEnc( type, Pdu, &PduLen ) != TCL_OK )
		tmAbort("RUASigToPdu: encoding RUA signal aborted");
	ResultPtr = Tcl_GetObjResult(itp);

	Tcl_SetByteArrayObj(ResultPtr,Pdu,PduLen);

	return TCL_OK;
}


/*	encoding RUA messages	*/
 int codecRUAEnc( uint type, OSOCTET *buf_out, uint *len_outP)
{
	// Check PDU type
    switch( type )
	{
		case tstmRUA_TYPE_RUA_CONNECT:
			if( encRUAConnect (buf_out, len_outP) ) {
				return TCL_ERROR;
			}
			break;
		case tstmRUA_TYPE_RUA_DIRECTTRANSFER:
		  	if( encRUADirectTransfer(buf_out, len_outP)) {
				return TCL_ERROR;
			}
		  	break;
		case tstmRUA_TYPE_RUA_DISCONNECT:
		  	if( encRUADisconnect(buf_out, len_outP)) {
				return TCL_ERROR;
			}
		  	break;
		case tstmRUA_TYPE_RUA_CONNECTIONLESSTRANSFER:	  
		  	if( encRUAConnectionlessTransfer(buf_out, len_outP)) {
				return TCL_ERROR;
			}
		  	break;
		case tstmRUA_TYPE_RUA_ERRORINDICATION:
		  	if( encRUAErrorIndication(buf_out, len_outP)) {
				return TCL_ERROR;
			}
		 	break;
		case tstmRUA_TYPE_RUA_PRIVATEMESSAGE:
		  	if( encRUAPrivateMessage(buf_out, len_outP)) {
				return TCL_ERROR;
			}
		  	break;
		default:
			tmAbort( "codecRUAEnc: type %u not managed",type );
	}

	return TCL_OK;
}


CALLBACKOBJ(RUAPduToSig)
{
	Tcl_Obj *PduObj;
    uchar *PduPtr;
    int PduLen;

    if(argc!=2) EARGC_OBJ;

    if( (PduObj = Tcl_ObjGetVar2(itp, argv[1], NULL, 0)) == NULL )
        return tmTclErrObj(itp,"RUAPduToSig: 2nd arg Tcl_ObjGetVar2 error\n");
    if((PduPtr = Tcl_GetByteArrayFromObj(PduObj,&PduLen))==NULL)
        return tmTclErrObj(itp,"RUAPduToSig: Tcl_GetByteArrayFromObj error\n");

    return codecRUADec(PduPtr, PduLen);
}


/*	decoding RUA messages	*/
int codecRUADec( uchar *PduPtr, uint PduLen )
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
		if( decRUAPdu( &t_proc, &t_code, PduPtr, PduLen, out_pdu, &len_out ) )
			return TCL_ERROR;
	}

	// Set type
	type = (t_proc << 8 ) + t_code;

	DEC_START_OBJ();

	if ( PduLen == 0 ) {

		DEC_NOTPRESENT_OBJ(tm_compatITP());

	} else {

		DEC_TYPE_OBJ( tm_compatITP(), tstmRUA_SAPI_TYPE2SID(ruaSapi, type));

		switch( type )
		{
			case tstmRUA_TYPE_RUA_CONNECT:
				decRUAConnect (out_pdu, len_out);
				break;
			case tstmRUA_TYPE_RUA_DIRECTTRANSFER:
			  	decRUADirectTransfer(out_pdu, len_out);
			  	break;
			case tstmRUA_TYPE_RUA_DISCONNECT:
			  	decRUADisconnect(out_pdu, len_out);
			  	break;
			case tstmRUA_TYPE_RUA_CONNECTIONLESSTRANSFER:
			  	decRUAConnectionlessTransfer(out_pdu, len_out);
			  	break;
			case tstmRUA_TYPE_RUA_ERRORINDICATION:
			  	decRUAErrorIndication(out_pdu, len_out);
			  	break;
			case tstmRUA_TYPE_RUA_PRIVATEMESSAGE:
			  	decRUAPrivateMessage(out_pdu, len_out);
			  	break;
			default:
				tmAbort( "codecRUADec: unexpected type %u\t(t_proc=%d\tt_code=%d)",type,t_proc,t_code );
		}
	}

	DEC_SET_VAR_OBJ( tm_compatITP(), "_sigpdu" );

	return TCL_OK;
}


/*	initialization	*/
int codecRUAInit(tmITPt* itp, ushort rua_sapi)
{

	tmTclCmdNewObj(itp, "RUASigToPdu", RUASigToPdu);
	tmTclCmdNewObj(itp, "RUAPduToSig", RUAPduToSig);

	ruaSapi = rua_sapi;

	/*	inter-layer communication	*/
	/*	OM	*/
	/*
	tstmRUA_WSN_SIG( RUA_OM_CFG,			rua_om_sapi );
	tstmRUA_WSN_SIG( RUA_OM_CFG_ACK,		rua_om_sapi );
	*/

	/*	RUA IEs	*/

	tstmRUA_WSN_FMAT(CAUSE);
	tstmRUA_WSN_FMAT(CRITICALITY_DIAGNOSTICS_IE_ITEM);
	tstmRUA_WSN_FMAT(CRITICALITY_DIAGNOSTICS);

	/*	RUA procedures	*/
	tstmRUA_WSN_SIG(RUA_CONNECT                 ,rua_sapi );
	tstmRUA_WSN_SIG(RUA_DIRECTTRANSFER          ,rua_sapi );
	tstmRUA_WSN_SIG(RUA_DISCONNECT              ,rua_sapi );
	tstmRUA_WSN_SIG(RUA_CONNECTIONLESSTRANSFER  ,rua_sapi );
	tstmRUA_WSN_SIG(RUA_ERRORINDICATION         ,rua_sapi );
	tstmRUA_WSN_SIG(RUA_PRIVATEMESSAGE          ,rua_sapi );
	

	return 0;
}
