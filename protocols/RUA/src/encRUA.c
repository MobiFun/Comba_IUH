/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/RUA/tags/RUA-1.3.0/src/encRUA.c $
$Author: roger $
$Date: 2012-07-27 15:55:43 +0200 (Fri, 27 Jul 2012) $
$Rev: 53538 $
----------------------------------------------------------------
Description : RUA SIGNALS ENCODING
--------------------------------------------------------------*/

/*............................................................*/
/* Include */
#include "encRUA.h"
#include "encIeRUA.h"
#include "RUA-PDU-Contents.h"
#include "defs.h"
#include "tm_compat.h"


/***********************************************************************
************************************************************************
                Encoding functions for RUA PDUs
************************************************************************
************************************************************************/
int ruaPduEnc( uint t_proc, uint t_code, OSOCTET *buf_in, OSOCTET *buf_out, uint *len)
{
    OSCTXT             	ctxt;
    OSBOOL                aligned = TRUE;
    RUA_RUA_PDU                *p_pdu;
    RUA_InitiatingMessage		initiatingMessage;
//	SuccessfulOutcome		successfulOutcome;
//	UnsuccessfulOutcome		unsuccessfulOutcome;
    int                     stat;

    // Initialize encoding context block
	ASN1_INIT_CTXT( ctxt )

    // Define buffer for encoded message
	ASN1_SET_BUFFER( ctxt, buf_out, defsPduMAX_SIZE_BUF, aligned )

    // Fill HNBAP-PDU structure
	ASN1_ALLOC( p_pdu, &ctxt, sizeof(RUA_RUA_PDU) )

	// Set type
	p_pdu->t = t_proc;

	switch( (p_pdu->t << 8) | t_code )
	{
		// Connect
		case (T_RUA_RUA_PDU_initiatingMessage << 8) | ASN1V_RUA_id_Connect :
            initiatingMessage.procedureCode = ASN1V_RUA_id_Connect;
            initiatingMessage.criticality   = RUA_ignore;
            initiatingMessage.value.numocts = *len;
            initiatingMessage.value.data    = buf_in;

            p_pdu->u.initiatingMessage = &initiatingMessage;
            break;

		// DirectTransfer
		case (T_RUA_RUA_PDU_initiatingMessage << 8) | ASN1V_RUA_id_DirectTransfer :
			initiatingMessage.procedureCode = ASN1V_RUA_id_DirectTransfer;
			initiatingMessage.criticality   = RUA_ignore;
			initiatingMessage.value.numocts = *len;
			initiatingMessage.value.data    = buf_in;

            p_pdu->u.initiatingMessage = &initiatingMessage;
            break;


		// Disconnect
		case (T_RUA_RUA_PDU_initiatingMessage << 8) | ASN1V_RUA_id_Disconnect :
			initiatingMessage.procedureCode = ASN1V_RUA_id_Disconnect;
			initiatingMessage.criticality   = RUA_ignore;
			initiatingMessage.value.numocts = *len;
			initiatingMessage.value.data    = buf_in;

			p_pdu->u.initiatingMessage = &initiatingMessage;
			break;

		// ConnectionlessTransfer
		case (T_RUA_RUA_PDU_initiatingMessage << 8) | ASN1V_RUA_id_ConnectionlessTransfer :
			initiatingMessage.procedureCode = ASN1V_RUA_id_ConnectionlessTransfer;
			initiatingMessage.criticality   = RUA_ignore;
			initiatingMessage.value.numocts = *len;
			initiatingMessage.value.data    = buf_in;

			p_pdu->u.initiatingMessage = &initiatingMessage;
			break;

		//ErrorIndication
		case (T_RUA_RUA_PDU_initiatingMessage << 8) | ASN1V_RUA_id_ErrorIndication :
            		initiatingMessage.procedureCode = ASN1V_RUA_id_ErrorIndication;
            		initiatingMessage.criticality   = RUA_ignore;
            		initiatingMessage.value.numocts = *len;
            		initiatingMessage.value.data    = buf_in;

            		p_pdu->u.initiatingMessage = &initiatingMessage;
            break;

		//PrivateMessage
		case (T_RUA_RUA_PDU_initiatingMessage << 8) | ASN1V_RUA_id_privateMessage :
			initiatingMessage.procedureCode = ASN1V_RUA_id_privateMessage;
			initiatingMessage.criticality   = RUA_ignore;
			initiatingMessage.value.numocts = *len;
			initiatingMessage.value.data    = buf_in;

			p_pdu->u.initiatingMessage = &initiatingMessage;
			break;

		default:
			tmLog("ERROR: Procedure %u and Code %u unknown while encoding RUA PDU...", p_pdu->t, t_code );
			ASN1_RETURN( ctxt );
			break;
	}

    // Call encoding function
    stat = asn1PE_RUA_RUA_PDU( &ctxt, p_pdu );
	CHECK_ENCODING( stat, ctxt )

	// Get PDU length
	*len = pu_getMsgLen( &ctxt );
	// tmLog ("----> RUA PDU length %u <----", *len);

    // Free context
	ASN1_FREE( ctxt )

    return ASN_OK;
}



/*	CONNECT	(ref. xxx)	*/
int encRUAConnect( OSOCTET *buf_out, int *lenP )
{
#define PDU_NAME    RUA_Connect // from RUA-PDU-Contents.h
#define PDU_TYPE    T_RUA_RUA_PDU_initiatingMessage // from RUA-PDU-Descriptions.h
#define PDU_ID      ASN1V_RUA_id_Connect //from RUA-Constants.h

	OSCTXT		ctxt;
	OSBOOL		aligned = TRUE;
	OSOCTET		*buf;
	PDU_NAME	*p_pdu;
	int			stat;

	// Initialize Context
	ASN1_INIT_CTXT( ctxt )

	// Initialize memory
	ASN1_ALLOC( buf, &ctxt, defsPduMAX_SIZE_BUF )

	// Define buffer for encoded message
	ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_BUF, aligned )

	// Allocate memory for p_pdu
	ASN1_ALLOC( p_pdu, &ctxt, sizeof(PDU_NAME) );

	// Initialize lists
	ASN1_INIT_LIST( &(p_pdu->protocolIEs) );

	// Fill pdu structure described by "ConnectIEs RUA-PROTOCOL-IES"

	// CN-DomainIndicator mandatory
	#define SIG_FLD ENC_SIG_FIELD_PTR(1)
	if (FIELD_PRES_OBJ ("CnDomain", SIG_FLD)) {

		encIeRUACNDomain (SIG_FLD, &(p_pdu->protocolIEs), &ctxt, RUA_reject);

	} else tmAbort ("Field 'CnDomain' is mandatory");
	#undef SIG_FLD

	// Context-ID mandatory
	#define SIG_FLD ENC_SIG_FIELD_PTR(2)
	if (FIELD_PRES_OBJ ("ContextId", SIG_FLD)) {

		encIeRUAContextId (SIG_FLD, &(p_pdu->protocolIEs), &ctxt, RUA_reject);

	} else tmAbort ("Field 'ContextId' is mandatory");
	#undef SIG_FLD

	// IntraDomainNasNodeSelector optional
	#define SIG_FLD ENC_SIG_FIELD_PTR(3)
	if (FIELD_PRES_OBJ ("IntraDomainNasNodeSelector", SIG_FLD)) {

		tmLog("IntraDomainNasNodeSelector encoding is not supported now!");
		
	}
	#undef SIG_FLD

	if (FIELD_PRES_OBJ ("EstCause", ENC_SIG_FIELD_PTR(4)))
	{
		encIeRUAEstCause (ENC_SIG_FIELD_PTR(4), &(p_pdu->protocolIEs), &ctxt, RUA_reject);
	} else
	{
		tmAbort ("Field 'EstCause' is mandatory");
	}

	if (FIELD_PRES_OBJ ("RanapMsg", ENC_SIG_FIELD_PTR(5)))
	{
		encIeRUARanapMessage (ENC_SIG_FIELD_PTR(5), &(p_pdu->protocolIEs), &ctxt, RUA_reject);
	} else
	{
		tmAbort ("Field 'RanapMsg' is mandatory");
	}
	
	// Fill pdu structure - END

	// Call ASN1 Encoding function
	stat = asn1PE_RUA_Connect (&ctxt, p_pdu); // RUA-PDU-ContentsEnc.c
	CHECK_ENCODING (stat, ctxt)

	// Update length
	*lenP = pu_getMsgLen (&ctxt);
	// tmLog ("Message length	%u\n", *lenP);

	ruaPduEnc (PDU_TYPE, PDU_ID, buf,buf_out, lenP);

	// Free allocated memory
	ASN1_FREE (ctxt)

#undef PDU_NAME
#undef PDU_TYPE
#undef PDU_ID

	return 0;
}


int encRUADirectTransfer( OSOCTET *buf_out, int *len )
{
#define PDU_NAME    RUA_DirectTransfer
#define PDU_TYPE    T_RUA_RUA_PDU_initiatingMessage
#define PDU_ID      ASN1V_RUA_id_DirectTransfer

    OSCTXT                    ctxt;
    OSBOOL                    aligned = TRUE;
    OSOCTET                   *buf;
    PDU_NAME                    *p_pdu;
    int                         stat;

	// Initialize Context
    ASN1_INIT_CTXT( ctxt )

    // Initialize memory
    ASN1_ALLOC( buf, &ctxt, defsPduMAX_SIZE_BUF )

    // Define buffer for encoded message
    ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_BUF, aligned )

    // Allocate memory for p_pdu
    ASN1_ALLOC( p_pdu, &ctxt, sizeof(PDU_NAME) );

    // Initialize lists
    ASN1_INIT_LIST( &(p_pdu->protocolIEs) );

    // Fill pdu structure - START
	if (FIELD_PRES_OBJ ("CnDomain", ENC_SIG_FIELD_PTR(1)))
	{
		encIeRUACNDomain (ENC_SIG_FIELD_PTR(1), &(p_pdu->protocolIEs), &ctxt, RUA_reject);
	} else
	{
		tmAbort ("Field 'CnDomain' is mandatory");
	}

	if (FIELD_PRES_OBJ ("ContextId", ENC_SIG_FIELD_PTR(2)))
	{
		encIeRUAContextId (ENC_SIG_FIELD_PTR(2), &(p_pdu->protocolIEs), &ctxt, RUA_reject);
	} else
	{
		tmAbort ("Field 'ContextId' is mandatory");
	}

	if (FIELD_PRES_OBJ ("RanapMsg", ENC_SIG_FIELD_PTR(3)))
	{
		encIeRUARanapMessage (ENC_SIG_FIELD_PTR(3), &(p_pdu->protocolIEs), &ctxt, RUA_reject);
	} else
	{
		tmAbort ("Field 'RanapMsg' is mandatory");
	}

	// Fill pdu structure - END

    // Call ASN1 Encoding function
    stat = asn1PE_RUA_DirectTransfer (&ctxt, p_pdu);
    CHECK_ENCODING (stat, ctxt)

    // Update length
    *len = pu_getMsgLen (&ctxt);
	// tmLog ("Message length	%u\n", *len);

    // Call encoding function for RUA-PDU
    ruaPduEnc (PDU_TYPE, PDU_ID, buf, buf_out, len);

    // Free allocated memory
    ASN1_FREE (ctxt)

#undef PDU_NAME
#undef PDU_TYPE
#undef PDU_ID

    return ASN_OK;
}

int encRUADisconnect( OSOCTET *buf_out, int *len )
{
#define PDU_NAME    RUA_Disconnect
#define PDU_TYPE    T_RUA_RUA_PDU_initiatingMessage
#define PDU_ID      ASN1V_RUA_id_Disconnect

    OSCTXT                    ctxt;
    OSBOOL                    aligned = TRUE;
    OSOCTET                   *buf;
    PDU_NAME                    *p_pdu;
    int                         stat;

	// Initialize Context
    ASN1_INIT_CTXT( ctxt )

    // Initialize memory
    ASN1_ALLOC( buf, &ctxt, defsPduMAX_SIZE_BUF )

    // Define buffer for encoded message
    ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_BUF, aligned )

    // Allocate memory for p_pdu
    ASN1_ALLOC( p_pdu, &ctxt, sizeof(PDU_NAME) );

    // Initialize lists
    ASN1_INIT_LIST( &(p_pdu->protocolIEs) );

    // Fill pdu structure - START
	if (FIELD_PRES_OBJ ("CnDomain", ENC_SIG_FIELD_PTR(1)))
	{
		encIeRUACNDomain (ENC_SIG_FIELD_PTR(1), &(p_pdu->protocolIEs), &ctxt, RUA_reject);
	} else
	{
		tmAbort ("Field 'CnDomain' is mandatory");
	}

	if (FIELD_PRES_OBJ ("ContextId", ENC_SIG_FIELD_PTR(2)))
	{
		encIeRUAContextId (ENC_SIG_FIELD_PTR(2), &(p_pdu->protocolIEs), &ctxt, RUA_reject);
	} else
	{
		tmAbort ("Field 'ContextId' is mandatory");
	}

	if (FIELD_PRES_OBJ ("Cause", ENC_SIG_FIELD_PTR(3)))
	{
		encIeRUACause (ENC_SIG_FIELD_PTR(3), &(p_pdu->protocolIEs), &ctxt, RUA_reject);
	} else
	{
		tmAbort ("Field 'Cause' is mandatory");
	}

	if (FIELD_PRES_OBJ ("RanapMsg", ENC_SIG_FIELD_PTR(4)))
	{
		encIeRUARanapMessage (ENC_SIG_FIELD_PTR(4), &(p_pdu->protocolIEs), &ctxt, RUA_reject);
	}

	// Fill pdu structure - END

    // Call ASN1 Encoding function
    stat = asn1PE_RUA_Disconnect (&ctxt, p_pdu);
    CHECK_ENCODING (stat, ctxt)

    // Update length
    *len = pu_getMsgLen (&ctxt);
	// tmLog ("Message length	%u\n", *len);

    // Call encoding function for RUA-PDU
    ruaPduEnc (PDU_TYPE, PDU_ID, buf, buf_out, len);

    // Free allocated memory
    ASN1_FREE (ctxt)

#undef PDU_NAME
#undef PDU_TYPE
#undef PDU_ID

    return ASN_OK;
}

int encRUAConnectionlessTransfer( OSOCTET *buf_out, int *len )
{
#define PDU_NAME    RUA_ConnectionlessTransfer
#define PDU_TYPE    T_RUA_RUA_PDU_initiatingMessage
#define PDU_ID      ASN1V_RUA_id_ConnectionlessTransfer

    OSCTXT                    ctxt;
    OSBOOL                    aligned = TRUE;
    OSOCTET                   *buf;
    PDU_NAME                    *p_pdu;
    int                         stat;

	// Initialize Context
    ASN1_INIT_CTXT( ctxt )

    // Initialize memory
    ASN1_ALLOC( buf, &ctxt, defsPduMAX_SIZE_BUF )

    // Define buffer for encoded message
    ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_BUF, aligned )

    // Allocate memory for p_pdu
    ASN1_ALLOC( p_pdu, &ctxt, sizeof(PDU_NAME) );

    // Initialize lists
    ASN1_INIT_LIST( &(p_pdu->protocolIEs) );

    // Fill pdu structure - START

	if (FIELD_PRES_OBJ ("RanapMsg", ENC_SIG_FIELD_PTR(1)))
	{
		encIeRUARanapMessage (ENC_SIG_FIELD_PTR(1), &(p_pdu->protocolIEs), &ctxt, RUA_reject);
	} else {
		tmAbort ("Field 'RanapMsg' is mandatory");
	}

	// Fill pdu structure - END

    // Call ASN1 Encoding function
    stat = asn1PE_RUA_ConnectionlessTransfer (&ctxt, p_pdu);
    CHECK_ENCODING (stat, ctxt)

    // Update length
    *len = pu_getMsgLen (&ctxt);
	// tmLog ("Message length	%u\n", *len);

    // Call encoding function for -PDU
    ruaPduEnc (PDU_TYPE, PDU_ID, buf, buf_out, len);

    // Free allocated memory
    ASN1_FREE (ctxt)

#undef PDU_NAME
#undef PDU_TYPE
#undef PDU_ID

    return ASN_OK;
}


int encRUAErrorIndication( OSOCTET *buf_out, int *len )
{
#define PDU_NAME    RUA_ErrorIndication
#define PDU_TYPE    T_RUA_RUA_PDU_initiatingMessage
#define PDU_ID      ASN1V_RUA_id_ErrorIndication

    OSCTXT                    ctxt;
    OSBOOL                    aligned = TRUE;
    OSOCTET                   *buf;
    PDU_NAME                    *p_pdu;
    int                         stat;

	// Initialize Context
    ASN1_INIT_CTXT( ctxt )

    // Initialize memory
    ASN1_ALLOC( buf, &ctxt, defsPduMAX_SIZE_BUF )

    // Define buffer for encoded message
    ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_BUF, aligned )

    // Allocate memory for p_pdu
    ASN1_ALLOC( p_pdu, &ctxt, sizeof(PDU_NAME) );

    // Initialize lists
    ASN1_INIT_LIST( &(p_pdu->protocolIEs) );

    // Fill pdu structure - START

	if (FIELD_PRES_OBJ ("Cause", ENC_SIG_FIELD_PTR(1)))
	{
		encIeRUACause (ENC_SIG_FIELD_PTR(1), &(p_pdu->protocolIEs), &ctxt, RUA_ignore);
	} else
	{
		tmAbort ("Field 'Cause' is mandatory");
	}

	if (FIELD_PRES_OBJ ("CriticalDiag", ENC_SIG_FIELD_PTR(2)))
	{
		encIeRUACriticalityDiagnostics (ENC_SIG_FIELD_PTR(2), &(p_pdu->protocolIEs), &ctxt, RUA_ignore);
	}

	// Fill pdu structure - END

    // Call ASN1 Encoding function
    stat = asn1PE_RUA_ErrorIndication (&ctxt, p_pdu);
    CHECK_ENCODING (stat, ctxt)

    // Update length
    *len = pu_getMsgLen (&ctxt);
	// tmLog ("Message length	%u\n", *len);

    // Call encoding function for -PDU
    ruaPduEnc (PDU_TYPE, PDU_ID, buf, buf_out, len);

    // Free allocated memory
    ASN1_FREE (ctxt)

#undef PDU_NAME
#undef PDU_TYPE
#undef PDU_ID

    return ASN_OK;
}

int encRUAPrivateMessage( OSOCTET *buf_out, int *len )
{
#define PDU_NAME    RUA_PrivateMessage
#define PDU_TYPE    T_RUA_RUA_PDU_initiatingMessage
#define PDU_ID      ASN1V_RUA_id_privateMessage

    OSCTXT                    ctxt;
    OSBOOL                    aligned = TRUE;
    OSOCTET                   *buf;
    PDU_NAME                    *p_pdu;
    int                         stat;

	// Initialize Context
    ASN1_INIT_CTXT( ctxt )

    // Initialize memory
    ASN1_ALLOC( buf, &ctxt, defsPduMAX_SIZE_BUF )

    // Define buffer for encoded message
    ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_BUF, aligned )

    // Allocate memory for p_pdu
    ASN1_ALLOC( p_pdu, &ctxt, sizeof(PDU_NAME) );

    // Initialize lists
    ASN1_INIT_LIST( &(p_pdu->privateIEs) );

    // Fill pdu structure - START


	// Fill pdu structure - END

    // Call ASN1 Encoding function
    stat = asn1PE_RUA_PrivateMessage (&ctxt, p_pdu);
    CHECK_ENCODING (stat, ctxt)

    // Update length
    *len = pu_getMsgLen (&ctxt);
	// tmLog ("Message length	%u\n", *len);

    // Call encoding function for -PDU
    ruaPduEnc (PDU_TYPE, PDU_ID, buf, buf_out, len);

    // Free allocated memory
    ASN1_FREE (ctxt)

#undef PDU_NAME
#undef PDU_TYPE
#undef PDU_ID

    return ASN_OK;
}

