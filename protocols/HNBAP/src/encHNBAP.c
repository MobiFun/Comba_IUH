/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/HNBAP/tags/HNBAP-1.3.0/src/encHNBAP.c $
$Author: roger $
$Date: 2012-07-27 15:55:36 +0200 (Fri, 27 Jul 2012) $
$Rev: 53537 $
----------------------------------------------------------------
Description : HNBAP SIGNALS ENCODING
--------------------------------------------------------------*/

/*............................................................*/
/* Include */
#include "encHNBAP.h"
#include "encIeHNBAP.h"
#include "HNBAP-PDU-Contents.h"
#include "defs.h"
#include "tm_compat.h"


/***********************************************************************
************************************************************************
                Encoding functions for HNBAP PDUs
************************************************************************
************************************************************************/
int hnbapPduEnc( uint t_proc, uint t_code, OSOCTET *buf_in, OSOCTET *buf_out, uint *len)
{
    OSCTXT             	ctxt;
    OSBOOL                aligned = TRUE;
    HnbHNBAP_PDU                *p_pdu;
    HnbInitiatingMessage		initiatingMessage;
    HnbSuccessfulOutcome		successfulOutcome;
    HnbUnsuccessfulOutcome		unsuccessfulOutcome;
    int                     stat;

    // Initialize encoding context block
	ASN1_INIT_CTXT( ctxt )

    // Define buffer for encoded message
	ASN1_SET_BUFFER( ctxt, buf_out, defsPduMAX_SIZE_BUF, aligned )

    // Fill HNBAP-PDU structure
	ASN1_ALLOC( p_pdu, &ctxt, sizeof(HnbHNBAP_PDU) )

	// Set type
	p_pdu->t = t_proc;

	switch( (p_pdu->t << 8) | t_code )
	{
		// HNBRegisterRequest
		case (T_HnbHNBAP_PDU_initiatingMessage << 8) | ASN1V_id_HNBRegister :
            initiatingMessage.procedureCode = ASN1V_id_HNBRegister;
            initiatingMessage.criticality   = reject;
            initiatingMessage.value.numocts = *len;
            initiatingMessage.value.data    = buf_in;

            p_pdu->u.initiatingMessage = &initiatingMessage;
            break;

		// HNBRegisterAccept
		case (T_HnbHNBAP_PDU_successfulOutcome << 8) | ASN1V_id_HNBRegister :
            successfulOutcome.procedureCode = ASN1V_id_HNBRegister;
            successfulOutcome.criticality   = reject;
            successfulOutcome.value.numocts = *len;
            successfulOutcome.value.data    = buf_in;

            p_pdu->u.successfulOutcome = &successfulOutcome;
            break;

		// HNBRegisterReject
		case (T_HnbHNBAP_PDU_unsuccessfulOutcome << 8) | ASN1V_id_HNBRegister :
			unsuccessfulOutcome.procedureCode = ASN1V_id_HNBRegister;
			unsuccessfulOutcome.criticality   = reject;
			unsuccessfulOutcome.value.numocts = *len;
			unsuccessfulOutcome.value.data    = buf_in;

            p_pdu->u.unsuccessfulOutcome = &unsuccessfulOutcome;
            break;

		// HNBDe-Register
		case (T_HnbHNBAP_PDU_initiatingMessage << 8) | ASN1V_id_HNBDe_Register :
            initiatingMessage.procedureCode = ASN1V_id_HNBDe_Register;
            initiatingMessage.criticality   = ignore;
            initiatingMessage.value.numocts = *len;
            initiatingMessage.value.data    = buf_in;

            p_pdu->u.initiatingMessage = &initiatingMessage;
            break;

		// UERegisterRequest
		case (T_HnbHNBAP_PDU_initiatingMessage << 8) | ASN1V_id_UERegister :
			initiatingMessage.procedureCode = ASN1V_id_UERegister;
			initiatingMessage.criticality   = reject;
			initiatingMessage.value.numocts = *len;
			initiatingMessage.value.data    = buf_in;

			p_pdu->u.initiatingMessage = &initiatingMessage;
			break;

		// UERegisterAccept
		case (T_HnbHNBAP_PDU_successfulOutcome << 8) | ASN1V_id_UERegister :
			successfulOutcome.procedureCode = ASN1V_id_UERegister;
			successfulOutcome.criticality   = reject;
			successfulOutcome.value.numocts = *len;
			successfulOutcome.value.data    = buf_in;

			p_pdu->u.successfulOutcome = &successfulOutcome;
			break;

		// UERegisterReject
		case (T_HnbHNBAP_PDU_unsuccessfulOutcome << 8) | ASN1V_id_UERegister :
			unsuccessfulOutcome.procedureCode = ASN1V_id_UERegister;
			unsuccessfulOutcome.criticality   = reject;
			unsuccessfulOutcome.value.numocts = *len;
			unsuccessfulOutcome.value.data    = buf_in;

			p_pdu->u.unsuccessfulOutcome = &unsuccessfulOutcome;
			break;

		// UEDe-Register
		case (T_HnbHNBAP_PDU_initiatingMessage << 8) | ASN1V_id_UEDe_Register :
			initiatingMessage.procedureCode = ASN1V_id_UEDe_Register;
			initiatingMessage.criticality   = ignore;
			initiatingMessage.value.numocts = *len;
			initiatingMessage.value.data    = buf_in;

			p_pdu->u.initiatingMessage = &initiatingMessage;
			break;

		//ErrorIndication
		case (T_HnbHNBAP_PDU_initiatingMessage << 8) | ASN1V_id_ErrorIndication :
            initiatingMessage.procedureCode = ASN1V_id_ErrorIndication;
            initiatingMessage.criticality   = ignore;
            initiatingMessage.value.numocts = *len;
            initiatingMessage.value.data    = buf_in;

            p_pdu->u.initiatingMessage = &initiatingMessage;
            break;

		//PrivateMessage
		case (T_HnbHNBAP_PDU_initiatingMessage << 8) | ASN1V_id_privateMessage :
			initiatingMessage.procedureCode = ASN1V_id_privateMessage;
			initiatingMessage.criticality   = ignore;
			initiatingMessage.value.numocts = *len;
			initiatingMessage.value.data    = buf_in;

			p_pdu->u.initiatingMessage = &initiatingMessage;
			break;

		default:
			tmLog("ERROR: Procedure %u and Code %u unknown while encoding HNBAP PDU...", p_pdu->t, t_code );
			ASN1_RETURN( ctxt );
			break;
	}

    // Call encoding function
    stat = asn1PE_HnbHNBAP_PDU( &ctxt, p_pdu );
	CHECK_ENCODING( stat, ctxt )

	// Get PDU length
	*len = pu_getMsgLen( &ctxt );
	// tmLog ("----> HNBAP PDU length %u <----", *len);

    // Free context
	ASN1_FREE( ctxt )

    return ASN_OK;
}

/*	REGISTER	(ref. xxx)	*/
int encHNBAPRegister( OSOCTET *buf_out, int *lenP )
{
#define PDU_NAME    HnbHNBRegisterRequest // from HNBAP-PDU-Contents.h
#define PDU_TYPE    T_HnbHNBAP_PDU_initiatingMessage // from HNBAP-PDU-Descriptions.h
#define PDU_ID      ASN1V_id_HNBRegister //from HNBAP-Constants.h

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

    // Fill pdu structure - START
	if (FIELD_PRES_OBJ ("HnbapId", ENC_SIG_FIELD_PTR(1)))
	{
		encHNBAP_HNB_Identity (ENC_SIG_FIELD_PTR(1), &(p_pdu->protocolIEs), &ctxt, reject);
	} else
	{
		tmAbort ("Field 'HnbapId' is mandatory");
	}

	if (FIELD_PRES_OBJ ("HnbapLocInfo", ENC_SIG_FIELD_PTR(2)))
	{
		encHNBAP_HNB_Location_Information (ENC_SIG_FIELD_PTR(2), &(p_pdu->protocolIEs), &ctxt, reject);
	} else
	{
		tmAbort ("Field 'HnbapLocInfo' is mandatory");
	}

	if (FIELD_PRES_OBJ ("PlmnId", ENC_SIG_FIELD_PTR(3)))
	{
		encHNBAP_PLMNidentity (ENC_SIG_FIELD_PTR(3), &(p_pdu->protocolIEs), &ctxt, reject);
	} else
	{
		tmAbort ("Field 'PlmnId' is mandatory");
	}

	if (FIELD_PRES_OBJ ("CellId", ENC_SIG_FIELD_PTR(4)))
	{
		encHNBAP_CellIdentity (ENC_SIG_FIELD_PTR(4), &(p_pdu->protocolIEs), &ctxt, reject);
	} else
	{
		tmAbort ("Field 'CellId' is mandatory");
	}

	if (FIELD_PRES_OBJ ("LAC", ENC_SIG_FIELD_PTR(5)))
	{
		encHNBAP_LAC (ENC_SIG_FIELD_PTR(5), &(p_pdu->protocolIEs), &ctxt, reject);
	} else
	{
		tmAbort ("Field 'LAC' is mandatory");
	}

	if (FIELD_PRES_OBJ ("RAC", ENC_SIG_FIELD_PTR(6)))
	{
		encHNBAP_RAC (ENC_SIG_FIELD_PTR(6), &(p_pdu->protocolIEs), &ctxt, reject);
	} else
	{
		tmAbort ("Field 'RAC' is mandatory");
	}

	if (FIELD_PRES_OBJ ("SAC", ENC_SIG_FIELD_PTR(7)))
	{
		encHNBAP_SAC (ENC_SIG_FIELD_PTR(7), &(p_pdu->protocolIEs), &ctxt, reject);
	} else
	{
		tmAbort ("Field 'SAC' is mandatory");
	}

	if (FIELD_PRES_OBJ ("CsgId", ENC_SIG_FIELD_PTR(8)))
	{
		encHNBAP_CSG_ID (ENC_SIG_FIELD_PTR(8), &(p_pdu->protocolIEs), &ctxt, reject);
	}

	// Fill pdu structure - END

	// Call ASN1 Encoding function
	stat = asn1PE_HnbHNBRegisterRequest (&ctxt, p_pdu); // HNBAP-PDU-ContentsEnc.c
	CHECK_ENCODING (stat, ctxt)

	// Update length
	*lenP = pu_getMsgLen (&ctxt);
	// tmLog ("Message length	%u\n", *lenP);

	hnbapPduEnc (PDU_TYPE, PDU_ID, buf, buf_out, lenP);

	// Free allocated memory
	ASN1_FREE (ctxt)

#undef PDU_NAME
#undef PDU_TYPE
#undef PDU_ID

	return 0;
}

int encHNBAPHNBRegisterAccept( OSOCTET *buf_out, int *len )
{
#define PDU_NAME    HnbHNBRegisterAccept
#define PDU_TYPE    T_HnbHNBAP_PDU_successfulOutcome
#define PDU_ID      ASN1V_id_HNBRegister

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
	if (FIELD_PRES_OBJ ("RncId", ENC_SIG_FIELD_PTR(1)))
	{
		encHNBAP_RNC_ID (ENC_SIG_FIELD_PTR(1), &(p_pdu->protocolIEs), &ctxt, reject);
	} else
	{
		tmAbort ("Field 'RncId' is mandatory");
	}


	// Fill pdu structure - END

    // Call ASN1 Encoding function
    stat = asn1PE_HnbHNBRegisterAccept (&ctxt, p_pdu);
    CHECK_ENCODING (stat, ctxt)

    // Update length
    *len = pu_getMsgLen (&ctxt);
	// tmLog ("Message length	%u\n", *len);

    // Call encoding function for HNBAP-PDU
    hnbapPduEnc (PDU_TYPE, PDU_ID, buf, buf_out, len);

    // Free allocated memory
    ASN1_FREE (ctxt)

#undef PDU_NAME
#undef PDU_TYPE
#undef PDU_ID

    return ASN_OK;
}

int encHNBAPHNBRegisterReject( OSOCTET *buf_out, int *len )
{
#define PDU_NAME    HnbHNBRegisterReject
#define PDU_TYPE    T_HnbHNBAP_PDU_unsuccessfulOutcome
#define PDU_ID      ASN1V_id_HNBRegister

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
		encHNBAP_Cause (ENC_SIG_FIELD_PTR(1), &(p_pdu->protocolIEs), &ctxt, ignore);
	} else
	{
		tmAbort ("Field 'Cause' is mandatory");
	}

	if (FIELD_PRES_OBJ ("CriticalDiag", ENC_SIG_FIELD_PTR(2)))
	{
		encHNBAP_CriticalityDiagnostics (ENC_SIG_FIELD_PTR(2), &(p_pdu->protocolIEs), &ctxt, ignore);
	}

	if (FIELD_PRES_OBJ ("BackOffTimer", ENC_SIG_FIELD_PTR(3)))
	{
		encHNBAP_BackoffTimer (ENC_SIG_FIELD_PTR(3), &(p_pdu->protocolIEs), &ctxt, reject);
	}
	// Fill pdu structure - END

    // Call ASN1 Encoding function
    stat = asn1PE_HnbHNBRegisterReject (&ctxt, p_pdu);
    CHECK_ENCODING (stat, ctxt)

    // Update length
    *len = pu_getMsgLen (&ctxt);
	// tmLog ("Message length	%u\n", *len);

    // Call encoding function for HNBAP-PDU
    hnbapPduEnc (PDU_TYPE, PDU_ID, buf, buf_out, len);

    // Free allocated memory
    ASN1_FREE (ctxt)

#undef PDU_NAME
#undef PDU_TYPE
#undef PDU_ID

    return ASN_OK;
}

int encHNBAPHNBDeRegister( OSOCTET *buf_out, int *len )
{
#define PDU_NAME    HnbHNBDe_Register
#define PDU_TYPE    T_HnbHNBAP_PDU_initiatingMessage
#define PDU_ID      ASN1V_id_HNBDe_Register

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
		encHNBAP_Cause (ENC_SIG_FIELD_PTR(1), &(p_pdu->protocolIEs), &ctxt, ignore);
	} else
	{
		tmAbort ("Field 'Cause' is mandatory");
	}


	if (FIELD_PRES_OBJ ("BackOffTimer", ENC_SIG_FIELD_PTR(2)))
	{
		encHNBAP_BackoffTimer (ENC_SIG_FIELD_PTR(2), &(p_pdu->protocolIEs), &ctxt, reject);
	}
	// Fill pdu structure - END

    // Call ASN1 Encoding function
    stat = asn1PE_HnbHNBDe_Register (&ctxt, p_pdu);
    CHECK_ENCODING (stat, ctxt)

    // Update length
    *len = pu_getMsgLen (&ctxt);
	// tmLog ("Message length	%u\n", *len);

    // Call encoding function for HNBAP-PDU
    hnbapPduEnc (PDU_TYPE, PDU_ID, buf, buf_out, len);

    // Free allocated memory
    ASN1_FREE (ctxt)

#undef PDU_NAME
#undef PDU_TYPE
#undef PDU_ID

    return ASN_OK;
}

int encHNBAPUERegisterRequest( OSOCTET *buf_out, int *len )
{
#define PDU_NAME    HnbUERegisterRequest
#define PDU_TYPE    T_HnbHNBAP_PDU_initiatingMessage
#define PDU_ID      ASN1V_id_UERegister

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
	if (FIELD_PRES_OBJ ("UeId", ENC_SIG_FIELD_PTR(1)))
	{
		encHNBAP_UE_Identity (ENC_SIG_FIELD_PTR(1), &(p_pdu->protocolIEs), &ctxt, reject);
	} else
	{
		tmAbort ("Field 'UeId' is mandatory");
	}

	if (FIELD_PRES_OBJ ("RegCause", ENC_SIG_FIELD_PTR(2)))
	{
		encHNBAP_Registration_Cause (ENC_SIG_FIELD_PTR(2), &(p_pdu->protocolIEs), &ctxt, ignore);
	} else {
		tmAbort("Field 'RegCause' is mandatory");
	}

	if (FIELD_PRES_OBJ ("UE_Cap", ENC_SIG_FIELD_PTR(3)))
	{
		encHNBAP_UE_Capabilities (ENC_SIG_FIELD_PTR(3), &(p_pdu->protocolIEs), &ctxt, ignore);
	} else {
		tmAbort("Field 'UE_Cap' is mandatory");
	}
	// Fill pdu structure - END

    // Call ASN1 Encoding function
    stat = asn1PE_HnbUERegisterRequest (&ctxt, p_pdu);
    CHECK_ENCODING (stat, ctxt)

    // Update length
    *len = pu_getMsgLen (&ctxt);
	// tmLog ("Message length	%u\n", *len);

    // Call encoding function for HNBAP-PDU
    hnbapPduEnc (PDU_TYPE, PDU_ID, buf, buf_out, len);

    // Free allocated memory
    ASN1_FREE (ctxt)

#undef PDU_NAME
#undef PDU_TYPE
#undef PDU_ID

    return ASN_OK;
}

int encHNBAPUERegisterAccept( OSOCTET *buf_out, int *len )
{
#define PDU_NAME    HnbUERegisterAccept
#define PDU_TYPE    T_HnbHNBAP_PDU_successfulOutcome
#define PDU_ID      ASN1V_id_UERegister

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
	if (FIELD_PRES_OBJ ("UeId", ENC_SIG_FIELD_PTR(1)))
	{
		encHNBAP_UE_Identity (ENC_SIG_FIELD_PTR(1), &(p_pdu->protocolIEs), &ctxt, reject);
	} else
	{
		tmAbort ("Field 'UeId' is mandatory");
	}

	if (FIELD_PRES_OBJ ("ContextId", ENC_SIG_FIELD_PTR(2)))
	{
		encHNBAP_Context_ID (ENC_SIG_FIELD_PTR(2), &(p_pdu->protocolIEs), &ctxt, ignore);
	} else {
		tmAbort("Field 'ContextId' is mandatory");
	}

	// Fill pdu structure - END

    // Call ASN1 Encoding function
    stat = asn1PE_HnbUERegisterAccept (&ctxt, p_pdu);
    CHECK_ENCODING (stat, ctxt)

    // Update length
    *len = pu_getMsgLen (&ctxt);
	// tmLog ("Message length	%u\n", *len);

    // Call encoding function for HNBAP-PDU
    hnbapPduEnc (PDU_TYPE, PDU_ID, buf, buf_out, len);

    // Free allocated memory
    ASN1_FREE (ctxt)

#undef PDU_NAME
#undef PDU_TYPE
#undef PDU_ID

    return ASN_OK;
}


int encHNBAPUERegisterReject( OSOCTET *buf_out, int *len )
{
#define PDU_NAME    HnbUERegisterReject
#define PDU_TYPE    T_HnbHNBAP_PDU_unsuccessfulOutcome
#define PDU_ID      ASN1V_id_UERegister

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
	if (FIELD_PRES_OBJ ("UeId", ENC_SIG_FIELD_PTR(1)))
	{
		encHNBAP_UE_Identity (ENC_SIG_FIELD_PTR(1), &(p_pdu->protocolIEs), &ctxt, reject);
	} else
	{
		tmAbort ("Field 'UeId' is mandatory");
	}

	if (FIELD_PRES_OBJ ("Cause", ENC_SIG_FIELD_PTR(2)))
	{
		encHNBAP_Cause (ENC_SIG_FIELD_PTR(2), &(p_pdu->protocolIEs), &ctxt, ignore);
	} else
	{
		tmAbort ("Field 'Cause' is mandatory");
	}

	if (FIELD_PRES_OBJ ("CriticalDiag", ENC_SIG_FIELD_PTR(3)))
	{
		encHNBAP_CriticalityDiagnostics (ENC_SIG_FIELD_PTR(3), &(p_pdu->protocolIEs), &ctxt, ignore);
	}
	// Fill pdu structure - END

    // Call ASN1 Encoding function
    stat = asn1PE_HnbUERegisterReject (&ctxt, p_pdu);
    CHECK_ENCODING (stat, ctxt)

    // Update length
    *len = pu_getMsgLen (&ctxt);
	// tmLog ("Message length	%u\n", *len);

    // Call encoding function for HNBAP-PDU
    hnbapPduEnc (PDU_TYPE, PDU_ID, buf, buf_out, len);

    // Free allocated memory
    ASN1_FREE (ctxt)

#undef PDU_NAME
#undef PDU_TYPE
#undef PDU_ID

    return ASN_OK;
}

int encHNBAPUEDeRegister( OSOCTET *buf_out, int *len )
{
#define PDU_NAME    HnbUEDe_Register
#define PDU_TYPE    T_HnbHNBAP_PDU_initiatingMessage
#define PDU_ID      ASN1V_id_UEDe_Register

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
	if (FIELD_PRES_OBJ ("ContextId", ENC_SIG_FIELD_PTR(1)))
	{
		encHNBAP_Context_ID (ENC_SIG_FIELD_PTR(1), &(p_pdu->protocolIEs), &ctxt, reject);
	} else {
		tmAbort("Field 'ContextId' is mandatory");
	}

	if (FIELD_PRES_OBJ ("Cause", ENC_SIG_FIELD_PTR(2)))
	{
		encHNBAP_Cause (ENC_SIG_FIELD_PTR(2), &(p_pdu->protocolIEs), &ctxt, ignore);
	} else
	{
		tmAbort ("Field 'Cause' is mandatory");
	}

	// Fill pdu structure - END

    // Call ASN1 Encoding function
    stat = asn1PE_HnbUEDe_Register (&ctxt, p_pdu);
    CHECK_ENCODING (stat, ctxt)

    // Update length
    *len = pu_getMsgLen (&ctxt);
	// tmLog ("Message length	%u\n", *len);

    // Call encoding function for HNBAP-PDU
    hnbapPduEnc (PDU_TYPE, PDU_ID, buf, buf_out, len);

    // Free allocated memory
    ASN1_FREE (ctxt)

#undef PDU_NAME
#undef PDU_TYPE
#undef PDU_ID

    return ASN_OK;
}


int encHNBAPErrorIndication( OSOCTET *buf_out, int *len )
{
#define PDU_NAME    HnbErrorIndication
#define PDU_TYPE    T_HnbHNBAP_PDU_initiatingMessage
#define PDU_ID      ASN1V_id_ErrorIndication

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
		encHNBAP_Cause (ENC_SIG_FIELD_PTR(1), &(p_pdu->protocolIEs), &ctxt, ignore);
	} else
	{
		tmAbort ("Field 'Cause' is mandatory");
	}

	if (FIELD_PRES_OBJ ("CriticalDiag", ENC_SIG_FIELD_PTR(2)))
	{
		encHNBAP_CriticalityDiagnostics (ENC_SIG_FIELD_PTR(2), &(p_pdu->protocolIEs), &ctxt, ignore);
	}
	// Fill pdu structure - END

    // Call ASN1 Encoding function
    stat = asn1PE_HnbErrorIndication (&ctxt, p_pdu);
    CHECK_ENCODING (stat, ctxt)

    // Update length
    *len = pu_getMsgLen (&ctxt);
	// tmLog ("Message length	%u\n", *len);

    // Call encoding function for HNBAP-PDU
    hnbapPduEnc (PDU_TYPE, PDU_ID, buf, buf_out, len);

    // Free allocated memory
    ASN1_FREE (ctxt)

#undef PDU_NAME
#undef PDU_TYPE
#undef PDU_ID

    return ASN_OK;
}


int encHNBAPPrivateMessage( OSOCTET *buf_out, int *len )
{
#define PDU_NAME    HnbPrivateMessage
#define PDU_TYPE    T_HnbHNBAP_PDU_initiatingMessage
#define PDU_ID      ASN1V_id_privateMessage

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
    stat = asn1PE_HnbPrivateMessage (&ctxt, p_pdu);
    CHECK_ENCODING (stat, ctxt)

    // Update length
    *len = pu_getMsgLen (&ctxt);
	// tmLog ("Message length	%u\n", *len);

    // Call encoding function for HNBAP-PDU
    hnbapPduEnc (PDU_TYPE, PDU_ID, buf, buf_out, len);

    // Free allocated memory
    ASN1_FREE (ctxt)

#undef PDU_NAME
#undef PDU_TYPE
#undef PDU_ID

    return ASN_OK;
}


