/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/RUA/tags/RUA-1.3.0/src/decIeRUA.c $
$Author: roger $
$Date: 2012-07-27 15:55:43 +0200 (Fri, 27 Jul 2012) $
$Rev: 53538 $
----------------------------------------------------------------
Description : RUA SIGNALS DECODING
--------------------------------------------------------------*/

/*............................................................*/
/*  Include */
#include "decIeRUA.h"
#include "tm_compat.h"

/***********************************************************************
************************************************************************
                Decoding functions for RUA IEs
************************************************************************
***********************************************************************/

int decIeRUACNDomain(OSOCTET *buf, uint len, Tcl_Obj *p_obj)
{
#define IE_NAME RUA_CN_DomainIndicator //RUA-IEs.h

	OSCTXT		ctxt;
    OSBOOL		aligned = TRUE;
    IE_NAME		pdu;
    Tcl_Obj		*pObj = p_obj ? p_obj : DEC_SIG_PTR;
    int			stat;

    // Initialize decoding context block
    ASN1_INIT_CTXT( ctxt )

    // Define buffer for decoded message
    ASN1_SET_BUFFER( ctxt, buf, len, aligned )

    // Call decoding function
    stat = asn1PD_RUA_CN_DomainIndicator( &ctxt, &pdu ); // from RUA-IEsDec.c

    CHECK_DECODING( stat, ctxt )

    // Get TCL fields

	// tmLog ("CN_DomainIndicator %u\n", pdu);
	DEC_UINT_FLD_OBJ (tmITP, pdu, pObj);

	// Free context
    ASN1_FREE( ctxt )

#undef IE_NAME

	return ASN_OK;
}

int decIeRUAContextId(OSOCTET *buf, uint len, Tcl_Obj *p_obj)
{
    #define IE_NAME	RUA_Context_ID

    OSCTXT            ctxt;
    OSBOOL            aligned = TRUE;
    IE_NAME             pdu;
    Tcl_Obj             *pObj = p_obj ? p_obj : DEC_SIG_PTR;
    int                 stat;
    uint 				tmpuint;
    // ASN1 decoding of field Cause

    // Initialize decoding context block
	ASN1_INIT_CTXT( ctxt )

    // Define buffer for decoded message
	ASN1_SET_BUFFER( ctxt, buf, len, aligned )

    // Call decoding function
    stat = asn1PD_RUA_Context_ID( &ctxt, &pdu );
	CHECK_DECODING( stat, ctxt )

	// Get TCL fields
	tmpuint = b2l_int (pdu.data, pdu.numbits);
	// tmLog ("pdu.data %u\n", tmpuint);
	DEC_UINT_FLD_OBJ (tmITP, tmpuint, pObj);
	// Free context
	ASN1_FREE( ctxt )

	#undef IE_NAME

	return ASN_OK;
}

int decIeRUAIntraDomNasNodeSel(OSOCTET *buf, uint len, Tcl_Obj *p_obj)
{
	// TODO

	return ASN_OK;
}

int decIeRUACause(OSOCTET *buf, uint len, Tcl_Obj *p_obj)
{
	#define IE_NAME	RUA_Cause

    OSCTXT            ctxt;
    OSBOOL            aligned = TRUE;
    IE_NAME             pdu;
    Tcl_Obj             *pObj = p_obj ? p_obj : DEC_SIG_PTR;
    int                 stat;

    // ASN1 decoding of field Cause

    // Initialize decoding context block
	ASN1_INIT_CTXT( ctxt )

    // Define buffer for decoded message
	ASN1_SET_BUFFER( ctxt, buf, len, aligned )

    // Call decoding function
    stat = asn1PD_RUA_Cause( &ctxt, &pdu );
	CHECK_DECODING( stat, ctxt )

/*
    if( !&pdu )
		ASN1_RETURN( ctxt )
*/
    DEC_START_STRUCT_OBJ (tmITP, Cause, "CAUSE");

	// tmLog ("pdu.t %u\n", pdu.t);
    DEC_INT_FLD_OBJ (tmITP, pdu.t, DEC_STRUCT_PTR (Cause));
    switch( pdu.t )
    {
    case T_RUA_Cause_radioNetwork:
		// tmLog ("pdu.u.radioNetwork %u\n", pdu.u.radioNetwork);
        DEC_UINT_FLD_OBJ (tmITP, pdu.u.radioNetwork, DEC_STRUCT_PTR (Cause));
       break;
    case T_RUA_Cause_transport:
    	// tmLog ("pdu.u.transport %u\n", pdu.u.transport);
	    DEC_UINT_FLD_OBJ (tmITP, pdu.u.transport, DEC_STRUCT_PTR (Cause));
       break;
    case T_RUA_Cause_protocol:
    	// tmLog ("pdu.u.protocol %u\n", pdu.u.protocol);
        DEC_UINT_FLD_OBJ (tmITP, pdu.u.protocol, DEC_STRUCT_PTR (Cause));
        break;
    case T_RUA_Cause_misc:
    	// tmLog ("pdu.u.misc %u\n", pdu.u.misc);
        DEC_UINT_FLD_OBJ (tmITP, pdu.u.misc, DEC_STRUCT_PTR (Cause));
        break;
    case T_RUA_Cause_extElem1:
		DEC_NOTPRES_FLD_OBJ (tmITP, DEC_STRUCT_PTR (Cause));
        break;
    default:
		tmAbort ("decRUA_Cause:Invalid value %u\n", pdu.t);
    }
    DEC_STOP_STRUCT_OBJ (tmITP, pObj, Cause);

    // Free context
	ASN1_FREE( ctxt )

#undef IE_NAME


	return ASN_OK;
}

int decIeRUACriticalityDiagnostics  (OSOCTET *buf, uint len, Tcl_Obj *p_obj)
{
#define IE_NAME	RUA_CriticalityDiagnostics

    OSCTXT            ctxt;
    OSBOOL            aligned = TRUE;
    IE_NAME             pdu;
	OSRTDListNode		*p_node;
	uint 				i;
    int                 stat;
	Tcl_Obj 			*pObj = p_obj ? p_obj : DEC_SIG_PTR;

    // Initialize decoding context block
	ASN1_INIT_CTXT( ctxt )

    // Define buffer for decoded message
	ASN1_SET_BUFFER( ctxt, buf, len, aligned )

    // Call decoding function
    stat = asn1PD_RUA_CriticalityDiagnostics( &ctxt, &pdu );
	CHECK_DECODING( stat, ctxt )

    // Get TCL fields
    /*
	if( !&pdu )
		ASN1_RETURN( ctxt )
	*/
	DEC_START_STRUCT_OBJ (tmITP, Criticality_Diagnostics, "CRITICALITY_DIAGNOSTICS");
	// tmLog ("pdu.m.procedureCodePresent %u\n", pdu.m.procedureCodePresent);
	if (pdu.m.procedureCodePresent) {
		// tmLog ("pdu.procedureCode %u\n", pdu.procedureCode);
		DEC_UCHAR_FLD_OBJ (tmITP, pdu.procedureCode, DEC_STRUCT_PTR(Criticality_Diagnostics));
	} else {
		DEC_NOTPRES_FLD_OBJ (tmITP, DEC_STRUCT_PTR (Criticality_Diagnostics));
	}

	// tmLog ("pdu.m.triggeringMessagePresent %u\n", pdu.m.triggeringMessagePresent);
	if (pdu.m.triggeringMessagePresent) {
		// tmLog ("pdu.triggeringMessage %u\n", pdu.triggeringMessage);
		DEC_UINT_FLD_OBJ (tmITP, pdu.triggeringMessage, DEC_STRUCT_PTR(Criticality_Diagnostics));
	} else {
		DEC_NOTPRES_FLD_OBJ (tmITP, DEC_STRUCT_PTR (Criticality_Diagnostics));
	}

	// tmLog ("pdu.m.procedureCriticalityPresent %u\n", pdu.m.procedureCriticalityPresent);
	if (pdu.m.procedureCriticalityPresent)
	{
		// tmLog ("pdu.procedureCriticality %u\n", pdu.procedureCriticality);
		DEC_UINT_FLD_OBJ (tmITP, pdu.procedureCriticality, DEC_STRUCT_PTR(Criticality_Diagnostics));
	} else {
		DEC_NOTPRES_FLD_OBJ (tmITP, DEC_STRUCT_PTR (Criticality_Diagnostics));
	}

	// tmLog ("pdu.m.iEsCriticalityDiagnosticsPresent %u\n", pdu.m.iEsCriticalityDiagnosticsPresent);
	if ( pdu.m.iEsCriticalityDiagnosticsPresent)
	{
		// tmLog ("pdu.iEsCriticalityDiagnostics.count %u\n", pdu.iEsCriticalityDiagnostics.count);
		DEC_START_LIST_OBJ (IEsCriticalityDiagnostics);
		p_node = pdu.iEsCriticalityDiagnostics.head;
		for (i = 0; i < pdu.iEsCriticalityDiagnostics.count; i++)
		{
#define ITEM ((RUA_CriticalityDiagnostics_IE_List_element *)p_node->data)
			DEC_START_STRUCT_OBJ (tmITP, IEsCriticalityDiagnostics_Item, "CRITICALITY_DIAGNOSTICS_IE_ITEM");
			// tmLog ("ITEM->iECriticality %u\n", ITEM->iECriticality);
			DEC_UINT_FLD_OBJ (tmITP, ITEM->iECriticality, DEC_STRUCT_PTR (IEsCriticalityDiagnostics_Item));

			// tmLog ("ITEM->iE_ID %u\n", ITEM->iE_ID);
			DEC_USHORT_FLD_OBJ (tmITP, ITEM->iE_ID, DEC_STRUCT_PTR (IEsCriticalityDiagnostics_Item));
			// tmLog ("ITEM->typeOfError %u\n", ITEM->typeOfError);
			DEC_UINT_FLD_OBJ (tmITP, ITEM->typeOfError, DEC_STRUCT_PTR (IEsCriticalityDiagnostics_Item));

			// tmLog ("ITEM->m.iE_ExtensionsPresent %u\n", ITEM->m.iE_ExtensionsPresent);
			// tmLog ("ITEM->extElem1.count %u\n", ITEM->extElem1.count);
			DEC_STOP_STRUCT_OBJ (tmITP, DEC_LIST_PTR (IEsCriticalityDiagnostics), IEsCriticalityDiagnostics_Item);
#undef ITEM
			p_node = p_node->next;
		}
		DEC_STOP_LIST_OBJ (tmITP, DEC_STRUCT_PTR (Criticality_Diagnostics), IEsCriticalityDiagnostics);
	}
    else
	{
		DEC_NOTPRES_FLD_OBJ (tmITP, DEC_STRUCT_PTR (Criticality_Diagnostics));
	}

	// tmLog ("pdu.m.iE_ExtensionsPresent %u\n", pdu.m.iE_ExtensionsPresent);
	// tmLog ("pdu.extElem1.count %u\n", pdu.extElem1.count);

	DEC_STOP_STRUCT_OBJ (tmITP, pObj, Criticality_Diagnostics);

    // Free context
	ASN1_FREE( ctxt )

#undef IE_NAME

	return ASN_OK;
}

int decIeRUAEstablishmentCause (OSOCTET *buf, uint len, Tcl_Obj *p_obj)
{
#define IE_NAME	RUA_Establishment_Cause

    OSCTXT            ctxt;
    OSBOOL            aligned = TRUE;
    IE_NAME             pdu;
    Tcl_Obj             *pObj = p_obj ? p_obj : DEC_SIG_PTR;
    int                 stat;

    // ASN1 decoding of field Cause

    // Initialize decoding context block
	ASN1_INIT_CTXT( ctxt )

    // Define buffer for decoded message
	ASN1_SET_BUFFER( ctxt, buf, len, aligned )

    // Call decoding function
    stat = asn1PD_RUA_Establishment_Cause( &ctxt, &pdu );
	CHECK_DECODING( stat, ctxt )

	// Get TCL fields
	// tmLog ("Establishment cause value %u\n", pdu);
	DEC_UINT_FLD_OBJ (tmITP, pdu, pObj);
	// Free context
	ASN1_FREE( ctxt )

#undef IE_NAME

    return ASN_OK;
}


int decIeRUARanapMessage (OSOCTET *buf, uint len, Tcl_Obj *p_obj)
{
#define IE_NAME	RUA_RANAP_Message

    OSCTXT            ctxt;
    OSBOOL            aligned = TRUE;
    IE_NAME             pdu;
    int                 stat;

    // Initialize decoding context block
	ASN1_INIT_CTXT( ctxt )

    // Define buffer for decoded message
	ASN1_SET_BUFFER( ctxt, buf, len, aligned )

    // Call decoding function
    stat = asn1PD_RUA_RANAP_Message( &ctxt, &pdu );
	CHECK_DECODING( stat, ctxt )

    // Get TCL fields
    /*
	if( !&pdu )
		ASN1_RETURN( ctxt )
    */
	// tmLog ("pdu.numocts %u\n", pdu.numocts);
    DEC_BINSTR_OBJ (tmITP, pdu.data, pdu.numocts);

    // Free context
	ASN1_FREE( ctxt )

#undef IE_NAME

	return ASN_OK;
}



