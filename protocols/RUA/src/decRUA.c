/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/RUA/tags/RUA-1.3.0/src/decRUA.c $
$Author: roger $
$Date: 2012-07-27 15:55:43 +0200 (Fri, 27 Jul 2012) $
$Rev: 53538 $
----------------------------------------------------------------
Description : RUA SIGNALS DECODING
--------------------------------------------------------------*/

/*............................................................*/
/*  Includes    */
#include "decRUA.h"
#include "decIeRUA.h"
#include "tstmRUA.h"
#include "tm_compat.h"

/* ---------------------------------------------------------------------------------------- */
int decRUAPdu( uint *t_proc, uint *t_code, uchar *buf_in, size_t buf_in_len, OSOCTET *buf_out, uint *len_out )
{
	OSCTXT		ctxt;
	OSBOOL		aligned = TRUE;
	RUA_RUA_PDU		pdu;
	int			stat;
	
	// Initialize decoding context block
	ASN1_INIT_CTXT( ctxt )
	
	// Define buffer for decoded message
	ASN1_SET_BUFFER( ctxt, buf_in, buf_in_len, aligned )
	
	// Call decoding function
	stat = asn1PD_RUA_RUA_PDU (&ctxt, &pdu);
	CHECK_DECODING( stat, ctxt )
	
	// Set type and procedure code
	*t_proc = pdu.t;
	switch( pdu.t )
	{
		case T_RUA_RUA_PDU_initiatingMessage:
			*t_code 	= pdu.u.initiatingMessage->procedureCode;
			*len_out	= pdu.u.initiatingMessage->value.numocts;
			memcpy( buf_out, pdu.u.initiatingMessage->value.data, *len_out);
			break;
		case T_RUA_RUA_PDU_successfulOutcome:
			*t_code 	= pdu.u.successfulOutcome->procedureCode;
			*len_out	= pdu.u.successfulOutcome->value.numocts;
			memcpy( buf_out, pdu.u.successfulOutcome->value.data, *len_out);
			break;
		case T_RUA_RUA_PDU_unsuccessfulOutcome:
			*t_code 	= pdu.u.unsuccessfulOutcome->procedureCode;
			*len_out	= pdu.u.unsuccessfulOutcome->value.numocts;
			memcpy( buf_out, pdu.u.unsuccessfulOutcome->value.data, *len_out);
			break;
		case T_RUA_RUA_PDU_extElem1:
			break;
		default:
			tmLogscr("decRUAPdu: unexpected pdu.t = %d\n");
			break;
	}
	
	// Free allocated memory
	ASN1_FREE( ctxt )
	
	return 0;
}

/********************************************
        Decoding functions for RUA PDUs
*********************************************/
/*  Connect    ( spec. reference )   */
int decRUAConnect( OSOCTET *buf_in, uint len )
{
#define PDU_NAME    RUA_Connect // from RUA-PDU-Contents.h
#define	PDU_N_IE	tstmRUA_PDU_N_IES_CONNECT // from tstmRUA.h

	OSCTXT					ctxt;
	OSBOOL					aligned = TRUE;
	OSRTDListNode			*p_node = NULL;
	RUA_ProtocolIE_Field	*p_protIEfield;
	PDU_NAME				pdu;
	int						stat, idx = 1, fill = 0, missing_opt_field; 
	uint					n = 0;

	// Initialize decoding context block
	ASN1_INIT_CTXT( ctxt )

	// Define buffer for decoded message
	ASN1_SET_BUFFER( ctxt, buf_in, defsPduMAX_SIZE_BUF, aligned )

	// Call decoding function
	stat = asn1PD_RUA_Connect( &ctxt, &pdu ); // from RUA-PDU-ContentsDec.c
	CHECK_DECODING( stat, ctxt )

	// tmLog ("IE number: %u", pdu.protocolIEs.count);
	if (pdu.protocolIEs.count != 0)
	{
		// Search IEs into the list of Protocols IE
		p_node = pdu.protocolIEs.head;

		do {
			missing_opt_field = 0;
			p_protIEfield = (RUA_ProtocolIE_Field *)p_node->data;

			switch( idx )
			{
				case 1:
					// CN-DomainIndicator mandatory
					if( p_protIEfield->id != ASN1V_RUA_id_CN_DomainIndicator ) {
						ERR_DEC_MND( CnDomain )
					}

					decIeRUACNDomain( (OSOCTET *)p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
					n++;
					break;

				case 2:
					// Context-ID mandatory
					if( p_protIEfield->id != ASN1V_RUA_id_Context_ID ) {
						ERR_DEC_MND( ContextId )
					}

					decIeRUAContextId( (OSOCTET *)p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
					n++;

				case 3:
					// IntraDomainNasNodeSelector optional
					if( p_protIEfield->id != ASN1V_RUA_id_IntraDomainNasNodeSelector ) {
						missing_opt_field = 1;
						DEC_NOTPRESENT_OBJ( tm_compatITP() );
					} else {
					/*
						decIeRUAIntraDomNasNodeSel( (OSOCTET *)p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
						n++;
					*/
						tmLog("Warning[decRUAConnect]: it does not support IE IntraDomainNasNodeSelector");
						DEC_NOTPRESENT_OBJ( tm_compatITP() );
					}

				case 4:
					// Establishment-Cause mandatory
					if( p_protIEfield->id != ASN1V_RUA_id_Establishment_Cause ) {
						ERR_DEC_MND( EstCause )
					}

					decIeRUAEstablishmentCause( (OSOCTET *)p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
					n++;
				case 5:
					//RanapMsg
					if( p_protIEfield->id != ASN1V_RUA_id_RANAP_Message )
						ERR_DEC_MND( RanapMsg );
					decIeRUARanapMessage( (OSOCTET *)p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
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
		DEC_NOTPRESENT_OBJ( tm_compatITP() );
	}

	// Free context
	ASN1_FREE( ctxt )

#undef PDU_NAME
#undef PDU_N_IE

	return 0;
}

int decRUADirectTransfer( OSOCTET *buf_in, uint len )
{
#define PDU_NAME    RUA_DirectTransfer
#define	PDU_N_IE	ruaPduNIEs_RUA_DIRECTTRANSFER   /* 3+1 */

    OSCTXT                    ctxt;
    OSBOOL                    aligned = TRUE;
    OSRTDListNode             *p_node = NULL;
    RUA_ProtocolIE_Field            *p_protIEfield;
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
    stat = asn1PD_RUA_DirectTransfer( &ctxt, &pdu );
    CHECK_DECODING( stat, ctxt )

	// Search IEs into the list of Protocols IE
	p_node = pdu.protocolIEs.head;

	do {
		missing_opt_field = 0;
		p_protIEfield = (RUA_ProtocolIE_Field *)p_node->data;

		switch( idx )
		{
			case 1:
				//CnDomain
				if( p_protIEfield->id != ASN1V_RUA_id_CN_DomainIndicator )
					ERR_DEC_MND( CnDomain );
				decIeRUACNDomain( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			case 2:
				//ContextId
				if( p_protIEfield->id != ASN1V_RUA_id_Context_ID )
					ERR_DEC_MND( ContextId );
				decIeRUAContextId( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			case 3:
				//RanapMsg
				if( p_protIEfield->id != ASN1V_RUA_id_RANAP_Message )
					ERR_DEC_MND( RanapMsg );
				decIeRUARanapMessage( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
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


int decRUADisconnect( OSOCTET *buf_in, uint len )
{
#define PDU_NAME    RUA_Disconnect
#define	PDU_N_IE	ruaPduNIEs_RUA_DISCONNECT   /* 4+1 */

    OSCTXT                    ctxt;
    OSBOOL                    aligned = TRUE;
    OSRTDListNode             *p_node = NULL;
    RUA_ProtocolIE_Field            *p_protIEfield;
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
    stat = asn1PD_RUA_Disconnect( &ctxt, &pdu );
    CHECK_DECODING( stat, ctxt )

	// Search IEs into the list of Protocols IE
	p_node = pdu.protocolIEs.head;

	do {
		missing_opt_field = 0;
		p_protIEfield = (RUA_ProtocolIE_Field *)p_node->data;

		switch( idx )
		{
			case 1:
				//CnDomain
				if( p_protIEfield->id != ASN1V_RUA_id_CN_DomainIndicator )
					ERR_DEC_MND( CnDomain );
				decIeRUACNDomain( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			case 2:
				//ContextId
				if( p_protIEfield->id != ASN1V_RUA_id_Context_ID )
					ERR_DEC_MND( ContextId );
				decIeRUAContextId( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			case 3:
				//Cause
				if( p_protIEfield->id != ASN1V_RUA_id_Cause )
					ERR_DEC_MND( Cause );
				decIeRUACause( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			case 4:
				//RanapMsg
				if( p_protIEfield->id != ASN1V_RUA_id_RANAP_Message ) {
					missing_opt_field = 1;
					DEC_NOTPRESENT_OBJ( tmITP );
				} else
					decIeRUARanapMessage( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
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

int decRUAConnectionlessTransfer( OSOCTET *buf_in, uint len )
{
#define PDU_NAME    RUA_ConnectionlessTransfer
#define	PDU_N_IE	ruaPduNIEs_RUA_CONNECTIONLESSTRANSFER   /* 1+1 */

    OSCTXT                    ctxt;
    OSBOOL                    aligned = TRUE;
    OSRTDListNode             *p_node = NULL;
    RUA_ProtocolIE_Field            *p_protIEfield;
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
    stat = asn1PD_RUA_ConnectionlessTransfer( &ctxt, &pdu );
    CHECK_DECODING( stat, ctxt )

	// Search IEs into the list of Protocols IE
	p_node = pdu.protocolIEs.head;

	do {
		missing_opt_field = 0;
		p_protIEfield = (RUA_ProtocolIE_Field *)p_node->data;

		switch( idx )
		{
			case 1:
				//RanapMsg
				if( p_protIEfield->id != ASN1V_RUA_id_RANAP_Message )
					ERR_DEC_MND( RanapMsg );
				decIeRUARanapMessage( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
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

int decRUAErrorIndication( OSOCTET *buf_in, uint len )
{
#define PDU_NAME    RUA_ErrorIndication
#define	PDU_N_IE	ruaPduNIEs_RUA_ERRORINDICATION   /* 2+1 */

    OSCTXT                    ctxt;
    OSBOOL                    aligned = TRUE;
    OSRTDListNode             *p_node = NULL;
    RUA_ProtocolIE_Field            *p_protIEfield;
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
    stat = asn1PD_RUA_ErrorIndication( &ctxt, &pdu );
    CHECK_DECODING( stat, ctxt )

	// Search IEs into the list of Protocols IE
	p_node = pdu.protocolIEs.head;

	do {
		missing_opt_field = 0;
		p_protIEfield = (RUA_ProtocolIE_Field *)p_node->data;

		switch( idx )
		{
			case 1:
				//Cause
				if( p_protIEfield->id != ASN1V_RUA_id_Cause )
					ERR_DEC_MND( Cause );
				decIeRUACause( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
				break;
			case 2:
				//CriticalDiag
				if( p_protIEfield->id != ASN1V_RUA_id_CriticalityDiagnostics ) {
					missing_opt_field = 1;
					DEC_NOTPRESENT_OBJ( tmITP );
				} else
					decIeRUACriticalityDiagnostics( p_protIEfield->value.data, p_protIEfield->value.numocts, NULL );
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

int decRUAPrivateMessage( OSOCTET *buf_in, uint len )
{
#define PDU_NAME    RUA_PrivateMessage

    OSCTXT                    ctxt;
    OSBOOL                    aligned = TRUE;
//    OSRTDListNode             *p_node = NULL;
//    ProtocolIE_Field            *p_protIEfield;
    PDU_NAME                    pdu;
    int                         stat;
 //   int                         idx = 1;
//	int							fill = 0;
//    int                         missing_opt_field;

	// Initialize decoding context block
    ASN1_INIT_CTXT( ctxt )

	// Define buffer for decoded message
	ASN1_SET_BUFFER( ctxt, buf_in, defsPduMAX_SIZE_BUF, aligned )

	// Call decoding function
    stat = asn1PD_RUA_PrivateMessage( &ctxt, &pdu );
    CHECK_DECODING( stat, ctxt )

	// Search IEs into the list of Protocols IE
    // tmLog("decRUAPrivateMessage: PrivateIEs Count %u",pdu.privateIEs.count);

	// Free context
	ASN1_FREE( ctxt )

#undef PDU_NAME

	return ASN_OK;
}

