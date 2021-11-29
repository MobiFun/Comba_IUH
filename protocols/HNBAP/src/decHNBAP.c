/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/HNBAP/tags/HNBAP-1.3.0/src/decHNBAP.c $
$Author: roger $
$Date: 2012-07-27 15:55:36 +0200 (Fri, 27 Jul 2012) $
$Rev: 53537 $
----------------------------------------------------------------
Description : HNBAP SIGNALS DECODING
--------------------------------------------------------------*/

/*............................................................*/
/*  Includes    */
#include "decHNBAP.h"
#include "decIeHNBAP.h"
#include "tstmHNBAP.h"
#include "tm_compat.h"

/* ---------------------------------------------------------------------------------------- */
int decHNBAPPdu( uint *t_proc, uint *t_code, uchar *buf_in, OSOCTET *buf_out, uint *len_out )
{
	OSCTXT			ctxt;
	OSBOOL			aligned = TRUE;
	HnbHNBAP_PDU	pdu;
	int				stat;
	
	// Initialize decoding context block
	ASN1_INIT_CTXT( ctxt )
	
	// Define buffer for decoded message
	ASN1_SET_BUFFER( ctxt, buf_in, defsPduMAX_SIZE_BUF, aligned )
	
	// Call decoding function
	stat = asn1PD_HnbHNBAP_PDU (&ctxt, &pdu);
	CHECK_DECODING( stat, ctxt )
	
	// Set type and procedure code
	*t_proc = pdu.t;
	switch( pdu.t )
	{
		case T_HnbHNBAP_PDU_initiatingMessage:
			*t_code 	= pdu.u.initiatingMessage->procedureCode;
			*len_out	= pdu.u.initiatingMessage->value.numocts;
			memcpy( buf_out, pdu.u.initiatingMessage->value.data, *len_out);
			break;
		case T_HnbHNBAP_PDU_successfulOutcome:
			*t_code 	= pdu.u.successfulOutcome->procedureCode;
			*len_out	= pdu.u.successfulOutcome->value.numocts;
			memcpy( buf_out, pdu.u.successfulOutcome->value.data, *len_out);
			break;
		case T_HnbHNBAP_PDU_unsuccessfulOutcome:
			*t_code 	= pdu.u.unsuccessfulOutcome->procedureCode;
			*len_out	= pdu.u.unsuccessfulOutcome->value.numocts;
			memcpy( buf_out, pdu.u.unsuccessfulOutcome->value.data, *len_out);
			break;
		case T_HnbHNBAP_PDU_extElem1:
			break;
		default:
			tmLogscr("decHNBAPPdu: unexpected pdu.t = %d\n");
			break;
	}
	
	// Free allocated memory
	ASN1_FREE( ctxt )
	
	return 0;
}

/********************************************
        Decoding functions for HNBAP PDUs
*********************************************/
/*  Register    ( spec. reference )   */
int decHNBAPRegister( OSOCTET *buf_in, uint len )
{
#define PDU_NAME    HnbHNBRegisterRequest // from HNBAP-PDU-Contents.h
#define	PDU_N_IE	tstmHNBAP_PDU_N_IES_REGISTER // from tstmHNBAP.h

	OSCTXT				ctxt;
	OSBOOL				aligned = TRUE;
	OSRTDListNode		*p_node = NULL;
	ProtocolIE_Field	*p_protIEfield;
	PDU_NAME			pdu;
	int					stat, idx = 1, fill = 0, missing_opt_field; 
	uint				n = 0;

	// Initialize decoding context block
	ASN1_INIT_CTXT( ctxt )

	// Define buffer for decoded message
	ASN1_SET_BUFFER( ctxt, buf_in, defsPduMAX_SIZE_BUF, aligned )

	// Call decoding function
	stat = asn1PD_HnbHNBRegisterRequest( &ctxt, &pdu ); // from HNBAP-PDU-ContentsDec.c
	CHECK_DECODING( stat, ctxt )

	// tmLog ("IE number: %u", pdu.protocolIEs.count);
	if (pdu.protocolIEs.count != 0)
	{
		// Search IEs into the list of Protocols IE
		p_node = pdu.protocolIEs.head;

		do {
			missing_opt_field = 0;
			p_protIEfield = (ProtocolIE_Field *)p_node->data;

			switch( idx )
			{
			case 1:
				//HnbapId
				if( p_protIEfield->id != ASN1V_id_HNB_Identity )
					ERR_DEC_MND( HnbapId );
				decHNBAP_HNB_Identity( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			case 2:
				//HnbapLocInfo
				if( p_protIEfield->id != ASN1V_id_HNB_Location_Information )
					ERR_DEC_MND( HnbapLocInfo );
				decHNBAP_HNB_Location_Information( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			case 3:
				//PlmnId
				if( p_protIEfield->id != ASN1V_id_PLMNidentity )
					ERR_DEC_MND( PlmnId );
				decHNBAP_PLMNidentity( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			case 4:
				//CellId
				if( p_protIEfield->id != ASN1V_id_CellIdentity )
					ERR_DEC_MND( CellId );
				decHNBAP_CellIdentity( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			case 5:
				//LAC
				if( p_protIEfield->id != ASN1V_id_LAC )
					ERR_DEC_MND( LAC );
				decHNBAP_LAC( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			case 6:
				//RAC
				if( p_protIEfield->id != ASN1V_id_RAC )
					ERR_DEC_MND( RAC );
				decHNBAP_RAC( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			case 7:
				//SAC
				if( p_protIEfield->id != ASN1V_id_SAC )
					ERR_DEC_MND( SAC );
				decHNBAP_SAC( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			case 8:
				//CsgId
				if( p_protIEfield->id != ASN1V_id_CSG_ID ) {
					missing_opt_field = 1;
					DEC_NOTPRESENT_OBJ( tmITP );
				} else
					decHNBAP_CSG_ID( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			default:
                printf("Protocol ID not found\n");
                return -1;
			}

			idx++;
			// in case an optional field wasn't found, p_node is reconsidered
			// also in next step of "do".
			if ( !missing_opt_field )
				p_node = p_node->next;
		} while ( (p_node != NULL) && (n <= pdu.protocolIEs.count) );
	}

	// Fill missing optional IE fields at the end of the Message
	for( fill = idx; fill <= PDU_N_IE; fill++ )
	{
		DEC_NOTPRESENT_OBJ( tmITP );
	}

	// Free context
	ASN1_FREE( ctxt )

#undef PDU_NAME
#undef PDU_N_IE

	return 0;
}

int decHNBAPHNBRegisterAccept( OSOCTET *buf_in, uint len )
{
#define PDU_NAME    HnbHNBRegisterAccept
#define	PDU_N_IE	hnbapPduNIEs_HNB_REGISTERACC   /* 1 */

    OSCTXT                    ctxt;
    OSBOOL                    aligned = TRUE;
    OSRTDListNode             *p_node = NULL;
    ProtocolIE_Field            *p_protIEfield;
    PDU_NAME                    pdu;
    int                         stat;
    int                         idx = 1;
	int							fill = 0;
    int                         missing_opt_field;

	// Initialize decoding context block
    ASN1_INIT_CTXT( ctxt )

	// Define buffer for decoded message
	ASN1_SET_BUFFER( ctxt, buf_in, defsPduMAX_SIZE_BUF, aligned )

	// Call decoding function
    stat = asn1PD_HnbHNBRegisterAccept( &ctxt, &pdu );
    CHECK_DECODING( stat, ctxt )

	// Search IEs into the list of Protocols IE
	p_node = pdu.protocolIEs.head;

	do {
		missing_opt_field = 0;
		p_protIEfield = (ProtocolIE_Field *)p_node->data;

		switch( idx )
		{
			case 1:
				//RNC-ID
				if( p_protIEfield->id != ASN1V_id_RNC_ID )
					ERR_DEC_MND( RncId );
				decHNBAP_RNC_ID( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			default:
                printf("Protocol ID not found\n");
                return -1;
		}

		idx++;
		if ( !missing_opt_field )
			p_node = p_node->next;
	} while ( p_node != pdu.protocolIEs.tail->next );

	// Fill missing optional IE fields at the end of the Message
	for( fill = idx; fill <= PDU_N_IE; fill++ )
	{
		DEC_NOTPRESENT_OBJ( tmITP );
	}

	// Free context
	ASN1_FREE( ctxt )

#undef PDU_NAME
#undef PDU_N_IE

	return ASN_OK;
}


int decHNBAPHNBRegisterReject( OSOCTET *buf_in, uint len )
{
#define PDU_NAME    HnbHNBRegisterReject
#define	PDU_N_IE	hnbapPduNIEs_HNB_REGISTERREJ   /* 3 */

    OSCTXT                    ctxt;
    OSBOOL                    aligned = TRUE;
    OSRTDListNode             *p_node = NULL;
    ProtocolIE_Field            *p_protIEfield;
    PDU_NAME                    pdu;
    int                         stat;
    int                         idx = 1;
	int							fill = 0;
    int                         missing_opt_field;

	// Initialize decoding context block
    ASN1_INIT_CTXT( ctxt )

	// Define buffer for decoded message
	ASN1_SET_BUFFER( ctxt, buf_in, defsPduMAX_SIZE_BUF, aligned )

	// Call decoding function
    stat = asn1PD_HnbHNBRegisterReject( &ctxt, &pdu );
    CHECK_DECODING( stat, ctxt )

	// Search IEs into the list of Protocols IE
	p_node = pdu.protocolIEs.head;

	do {
		missing_opt_field = 0;
		p_protIEfield = (ProtocolIE_Field *)p_node->data;

		switch( idx )
		{
			case 1:
				//Cause
				if( p_protIEfield->id != ASN1V_id_Cause )
					ERR_DEC_MND( Cause );
				decHNBAP_Cause( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			case 2:
				//CriticalDiag
				if( p_protIEfield->id != ASN1V_id_CriticalityDiagnostics ) {
					missing_opt_field = 1;
					DEC_NOTPRESENT_OBJ( tmITP );
				} else
					decHNBAP_CriticalityDiagnostics( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			case 3:
				//BackOffTimer
				if( p_protIEfield->id != ASN1V_id_BackoffTimer ){
					missing_opt_field = 1;
					DEC_NOTPRESENT_OBJ( tmITP );
				} else
					decHNBAP_BackoffTimer( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			default:
                printf("Protocol ID not found\n");
                return -1;
		}

		idx++;
		if ( !missing_opt_field )
			p_node = p_node->next;
	} while ( p_node != pdu.protocolIEs.tail->next );

	// Fill missing optional IE fields at the end of the Message
	for( fill = idx; fill <= PDU_N_IE; fill++ )
	{
		DEC_NOTPRESENT_OBJ( tmITP );
	}

	// Free context
	ASN1_FREE( ctxt )

#undef PDU_NAME
#undef PDU_N_IE

	return ASN_OK;
}

int decHNBAPHNBDeRegister( OSOCTET *buf_in, uint len )
{
#define PDU_NAME    HnbHNBDe_Register
#define	PDU_N_IE	hnbapPduNIEs_HNB_DEREGISTER   /* 2 */

    OSCTXT                    ctxt;
    OSBOOL                    aligned = TRUE;
    OSRTDListNode             *p_node = NULL;
    ProtocolIE_Field            *p_protIEfield;
    PDU_NAME                    pdu;
    int                         stat;
    int                         idx = 1;
	int							fill = 0;
    int                         missing_opt_field;

	// Initialize decoding context block
    ASN1_INIT_CTXT( ctxt )

	// Define buffer for decoded message
	ASN1_SET_BUFFER( ctxt, buf_in, defsPduMAX_SIZE_BUF, aligned )

	// Call decoding function
    stat = asn1PD_HnbHNBDe_Register( &ctxt, &pdu );
    CHECK_DECODING( stat, ctxt )

	// Search IEs into the list of Protocols IE
	p_node = pdu.protocolIEs.head;

	do {
		missing_opt_field = 0;
		p_protIEfield = (ProtocolIE_Field *)p_node->data;

		switch( idx )
		{
			case 1:
				//Cause
				if( p_protIEfield->id != ASN1V_id_Cause )
					ERR_DEC_MND( Cause );
				decHNBAP_Cause( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			case 2:
				//BackOffTimer
				if( p_protIEfield->id != ASN1V_id_BackoffTimer ){
					missing_opt_field = 1;
					DEC_NOTPRESENT_OBJ( tmITP );
				} else
					decHNBAP_BackoffTimer( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			default:
                printf("Protocol ID not found\n");
                return -1;
		}

		idx++;
		if ( !missing_opt_field )
			p_node = p_node->next;
	} while ( p_node != pdu.protocolIEs.tail->next );

	// Fill missing optional IE fields at the end of the Message
	for( fill = idx; fill <= PDU_N_IE; fill++ )
	{
		DEC_NOTPRESENT_OBJ( tmITP );
	}

	// Free context
	ASN1_FREE( ctxt )

#undef PDU_NAME
#undef PDU_N_IE

	return ASN_OK;
}

int decHNBAPUERegisterRequest( OSOCTET *buf_in, uint len )
{
#define PDU_NAME    HnbUERegisterRequest
#define	PDU_N_IE	hnbapPduNIEs_HNB_UEREGISTER   /* 3 */

    OSCTXT                    ctxt;
    OSBOOL                    aligned = TRUE;
    OSRTDListNode             *p_node = NULL;
    ProtocolIE_Field            *p_protIEfield;
    PDU_NAME                    pdu;
    int                         stat;
    int                         idx = 1;
	int							fill = 0;
    int                         missing_opt_field;

	// Initialize decoding context block
    ASN1_INIT_CTXT( ctxt )

	// Define buffer for decoded message
	ASN1_SET_BUFFER( ctxt, buf_in, defsPduMAX_SIZE_BUF, aligned )

	// Call decoding function
    stat = asn1PD_HnbUERegisterRequest( &ctxt, &pdu );
    CHECK_DECODING( stat, ctxt )

	// Search IEs into the list of Protocols IE
	p_node = pdu.protocolIEs.head;

	do {
		missing_opt_field = 0;
		p_protIEfield = (ProtocolIE_Field *)p_node->data;

		switch( idx )
		{
			case 1:
				//UeId
				if( p_protIEfield->id != ASN1V_id_UE_Identity )
					ERR_DEC_MND( UeId );
				decHNBAP_UE_Identity( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			case 2:
				//RegCause
				if( p_protIEfield->id != ASN1V_id_Registration_Cause )
					ERR_DEC_MND( RegCause );
				decHNBAP_Registration_Cause( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			case 3:
				//UE_Cap
				if( p_protIEfield->id != ASN1V_id_UE_Capabilities )
					ERR_DEC_MND( UE_Cap );
				decHNBAP_UE_Capabilities( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			default:
                printf("Protocol ID not found\n");
                return -1;
		}

		idx++;
		if ( !missing_opt_field )
			p_node = p_node->next;
	} while ( p_node != pdu.protocolIEs.tail->next );

	// Fill missing optional IE fields at the end of the Message
	for( fill = idx; fill <= PDU_N_IE; fill++ )
	{
		DEC_NOTPRESENT_OBJ( tmITP );
	}

	// Free context
	ASN1_FREE( ctxt )

#undef PDU_NAME
#undef PDU_N_IE

	return ASN_OK;
}

int decHNBAPUERegisterAccept( OSOCTET *buf_in, uint len )
{
#define PDU_NAME    HnbUERegisterAccept
#define	PDU_N_IE	hnbapPduNIEs_HNB_UEREGISTERACC   /* 2 */

    OSCTXT                    ctxt;
    OSBOOL                    aligned = TRUE;
    OSRTDListNode             *p_node = NULL;
    ProtocolIE_Field            *p_protIEfield;
    PDU_NAME                    pdu;
    int                         stat;
    int                         idx = 1;
	int							fill = 0;
    int                         missing_opt_field;

	// Initialize decoding context block
    ASN1_INIT_CTXT( ctxt )

	// Define buffer for decoded message
	ASN1_SET_BUFFER( ctxt, buf_in, defsPduMAX_SIZE_BUF, aligned )

	// Call decoding function
    stat = asn1PD_HnbUERegisterAccept( &ctxt, &pdu );
    CHECK_DECODING( stat, ctxt )

	// Search IEs into the list of Protocols IE
	p_node = pdu.protocolIEs.head;

	do {
		missing_opt_field = 0;
		p_protIEfield = (ProtocolIE_Field *)p_node->data;

		switch( idx )
		{
			case 1:
				//UeId
				if( p_protIEfield->id != ASN1V_id_UE_Identity )
					ERR_DEC_MND( UeId );
				decHNBAP_UE_Identity( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			case 2:
				//Context ID
				if( p_protIEfield->id != ASN1V_id_Context_ID )
					ERR_DEC_MND( ContextId );
				decHNBAP_Context_ID( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			default:
                printf("Protocol ID not found\n");
                return -1;
		}

		idx++;
		if ( !missing_opt_field )
			p_node = p_node->next;
	} while ( p_node != pdu.protocolIEs.tail->next );

	// Fill missing optional IE fields at the end of the Message
	for( fill = idx; fill <= PDU_N_IE; fill++ )
	{
		DEC_NOTPRESENT_OBJ( tmITP );
	}

	// Free context
	ASN1_FREE( ctxt )

#undef PDU_NAME
#undef PDU_N_IE

	return ASN_OK;
}

int decHNBAPUERegisterReject( OSOCTET *buf_in, uint len )
{
#define PDU_NAME    HnbUERegisterReject
#define	PDU_N_IE	hnbapPduNIEs_HNB_UEREGISTERREJ   /* 3 */

    OSCTXT                    ctxt;
    OSBOOL                    aligned = TRUE;
    OSRTDListNode             *p_node = NULL;
    ProtocolIE_Field            *p_protIEfield;
    PDU_NAME                    pdu;
    int                         stat;
    int                         idx = 1;
	int							fill = 0;
    int                         missing_opt_field;

	// Initialize decoding context block
    ASN1_INIT_CTXT( ctxt )

	// Define buffer for decoded message
	ASN1_SET_BUFFER( ctxt, buf_in, defsPduMAX_SIZE_BUF, aligned )

	// Call decoding function
    stat = asn1PD_HnbUERegisterReject( &ctxt, &pdu );
    CHECK_DECODING( stat, ctxt )

	// Search IEs into the list of Protocols IE
	p_node = pdu.protocolIEs.head;

	do {
		missing_opt_field = 0;
		p_protIEfield = (ProtocolIE_Field *)p_node->data;

		switch( idx )
		{
			case 1:
				//UeId
				if( p_protIEfield->id != ASN1V_id_UE_Identity )
					ERR_DEC_MND( UeId );
				decHNBAP_UE_Identity( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			case 2:
				//Cause
				if( p_protIEfield->id != ASN1V_id_Cause )
					ERR_DEC_MND( Cause );
				decHNBAP_Cause( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			case 3:
				//CriticalDiag
				if( p_protIEfield->id != ASN1V_id_CriticalityDiagnostics ) {
					missing_opt_field = 1;
					DEC_NOTPRESENT_OBJ( tmITP );
				} else
					decHNBAP_CriticalityDiagnostics( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			default:
                printf("Protocol ID not found\n");
                return -1;
		}

		idx++;
		if ( !missing_opt_field )
			p_node = p_node->next;
	} while ( p_node != pdu.protocolIEs.tail->next );

	// Fill missing optional IE fields at the end of the Message
	for( fill = idx; fill <= PDU_N_IE; fill++ )
	{
		DEC_NOTPRESENT_OBJ( tmITP );
	}

	// Free context
	ASN1_FREE( ctxt )

#undef PDU_NAME
#undef PDU_N_IE

	return ASN_OK;
}

int decHNBAPUEDeRegister( OSOCTET *buf_in, uint len )
{
#define PDU_NAME    HnbUEDe_Register
#define	PDU_N_IE	hnbapPduNIEs_HNB_UEDEREGISTER   /* 2 */

    OSCTXT                    ctxt;
    OSBOOL                    aligned = TRUE;
    OSRTDListNode             *p_node = NULL;
    ProtocolIE_Field            *p_protIEfield;
    PDU_NAME                    pdu;
    int                         stat;
    int                         idx = 1;
	int							fill = 0;
    int                         missing_opt_field;

	// Initialize decoding context block
    ASN1_INIT_CTXT( ctxt )

	// Define buffer for decoded message
	ASN1_SET_BUFFER( ctxt, buf_in, defsPduMAX_SIZE_BUF, aligned )

	// Call decoding function
    stat = asn1PD_HnbUEDe_Register( &ctxt, &pdu );
    CHECK_DECODING( stat, ctxt )

	// Search IEs into the list of Protocols IE
	p_node = pdu.protocolIEs.head;

	do {
		missing_opt_field = 0;
		p_protIEfield = (ProtocolIE_Field *)p_node->data;

		switch( idx )
		{
			case 1:
				//Context ID
				if( p_protIEfield->id != ASN1V_id_Context_ID )
					ERR_DEC_MND( ContextId );
				decHNBAP_Context_ID( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			case 2:
				//Cause
				if( p_protIEfield->id != ASN1V_id_Cause )
					ERR_DEC_MND( Cause );
				decHNBAP_Cause( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			default:
                printf("Protocol ID not found\n");
                return -1;
		}

		idx++;
		if ( !missing_opt_field )
			p_node = p_node->next;
	} while ( p_node != pdu.protocolIEs.tail->next );

	// Fill missing optional IE fields at the end of the Message
	for( fill = idx; fill <= PDU_N_IE; fill++ )
	{
		DEC_NOTPRESENT_OBJ( tmITP );
	}

	// Free context
	ASN1_FREE( ctxt )

#undef PDU_NAME
#undef PDU_N_IE

	return ASN_OK;
}

int decHNBAPErrorIndication( OSOCTET *buf_in, uint len )
{
#define PDU_NAME    HnbErrorIndication
#define	PDU_N_IE	hnbapPduNIEs_HNB_ERRORINDICATION   /* 2 */

    OSCTXT                    ctxt;
    OSBOOL                    aligned = TRUE;
    OSRTDListNode             *p_node = NULL;
    ProtocolIE_Field            *p_protIEfield;
    PDU_NAME                    pdu;
    int                         stat;
    int                         idx = 1;
	int							fill = 0;
    int                         missing_opt_field;

	// Initialize decoding context block
    ASN1_INIT_CTXT( ctxt )

	// Define buffer for decoded message
	ASN1_SET_BUFFER( ctxt, buf_in, defsPduMAX_SIZE_BUF, aligned )

	// Call decoding function
    stat = asn1PD_HnbErrorIndication( &ctxt, &pdu );
    CHECK_DECODING( stat, ctxt )

	// Search IEs into the list of Protocols IE
	p_node = pdu.protocolIEs.head;

	do {
		missing_opt_field = 0;
		p_protIEfield = (ProtocolIE_Field *)p_node->data;

		switch( idx )
		{

			case 1:
				//Cause
				if( p_protIEfield->id != ASN1V_id_Cause )
					ERR_DEC_MND( Cause );
				decHNBAP_Cause( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			case 2:
				//CriticalDiag
				if( p_protIEfield->id != ASN1V_id_CriticalityDiagnostics ) {
					missing_opt_field = 1;
					DEC_NOTPRESENT_OBJ( tmITP );
				} else
					decHNBAP_CriticalityDiagnostics( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			default:
                printf("Protocol ID not found\n");
                return -1;
		}

		idx++;
		if ( !missing_opt_field )
			p_node = p_node->next;
	} while ( p_node != pdu.protocolIEs.tail->next );

	// Fill missing optional IE fields at the end of the Message
	for( fill = idx; fill <= PDU_N_IE; fill++ )
	{
		DEC_NOTPRESENT_OBJ( tmITP );
	}

	// Free context
	ASN1_FREE( ctxt )

#undef PDU_NAME
#undef PDU_N_IE

	return ASN_OK;
}


int decHNBAPPrivateMessage( OSOCTET *buf_in, uint len )
{
#define PDU_NAME    HnbPrivateMessage

    OSCTXT                    ctxt;
    OSBOOL                    aligned = TRUE;
    OSRTDListNode             *p_node = NULL;
 //   ProtocolIE_Field            *p_protIEfield;
    PDU_NAME                    pdu;
    int                         stat;
//    int                         idx = 1;
//	int							fill = 0;
//    int                         missing_opt_field;

	// Initialize decoding context block
    ASN1_INIT_CTXT( ctxt )

	// Define buffer for decoded message
	ASN1_SET_BUFFER( ctxt, buf_in, defsPduMAX_SIZE_BUF, aligned )

	// Call decoding function
    stat = asn1PD_HnbPrivateMessage( &ctxt, &pdu );
    CHECK_DECODING( stat, ctxt )

	// Search IEs into the list of Protocols IE
	p_node = pdu.privateIEs.head;
    // tmLog ("PrivateMessage IEs Count: %u",pdu.privateIEs.count);

	// Free context
	ASN1_FREE( ctxt )

#undef PDU_NAME

	return ASN_OK;
}



