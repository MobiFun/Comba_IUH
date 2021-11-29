/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/HNBAP/tags/HNBAP-1.3.0/src/decIeHNBAP.c $
$Author: roger $
$Date: 2012-07-27 15:55:36 +0200 (Fri, 27 Jul 2012) $
$Rev: 53537 $
----------------------------------------------------------------
Description : HNBAP SIGNALS DECODING
--------------------------------------------------------------*/

/*............................................................*/
/*  Include */
#include "decIeHNBAP.h"
#include "tm_compat.h"

/***********************************************************************
************************************************************************
                Decoding functions for HNBAP IEs
************************************************************************
***********************************************************************/
int decHNBAP_HNB_Identity (OSOCTET *buf, uint len, Tcl_Obj *p_obj)
{
#define IE_NAME	HNB_Identity

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
    stat = asn1PD_HNB_Identity( &ctxt, &pdu );
	CHECK_DECODING( stat, ctxt )

	// Get TCL fields
	tmLog ("pdu.numocts %u\n", pdu.hNB_Identity_Info.numocts);
	DEC_HEX_FLD_OBJ (tmITP, pdu.hNB_Identity_Info.data, pdu.hNB_Identity_Info.numocts, pObj);
	// Free context
	ASN1_FREE( ctxt )

#undef IE_NAME

    return ASN_OK;
}

int decHNBAP_PLMNidentity (OSOCTET *buf, uint len, Tcl_Obj *p_obj)
{
#define IE_NAME	PLMNidentity

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
    stat = asn1PD_PLMNidentity( &ctxt, &pdu );
	CHECK_DECODING( stat, ctxt )

	// Get TCL fields
	tmLog ("pdu.numocts %u\n", pdu.numocts);
	DEC_HEX_FLD_OBJ (tmITP, pdu.data, pdu.numocts, pObj);
	// Free context
	ASN1_FREE( ctxt )

#undef IE_NAME

    return ASN_OK;
}

int decHNBAP_CellIdentity (OSOCTET *buf, uint len, Tcl_Obj *p_obj)
{
#define IE_NAME	CellIdentity

    OSCTXT            ctxt;
    OSBOOL            aligned = TRUE;
    IE_NAME             pdu;
    Tcl_Obj             *pObj = p_obj ? p_obj : DEC_SIG_PTR;
    int                 stat;
    uint                tmpuint;
    // ASN1 decoding of field Cause

    // Initialize decoding context block
	ASN1_INIT_CTXT( ctxt )

    // Define buffer for decoded message
	ASN1_SET_BUFFER( ctxt, buf, len, aligned )

    // Call decoding function
    stat = asn1PD_CellIdentity( &ctxt, &pdu );
	CHECK_DECODING( stat, ctxt )

	// Get TCL fields
	
	/*
	tmLog ("pdu.numbits %u", pdu.numbits);
	tmLog ("pdu.data[0] %u",pdu.data[0]);
	tmLog ("pdu.data[1] %u",pdu.data[1]);
	tmLog ("pdu.data[2] %u",pdu.data[2]);
	tmLog ("pdu.data[3] %u",pdu.data[3]);
	*/
	tmpuint = b2l_int (pdu.data, pdu.numbits);
	// tmLog ("pdu.data %u\n", tmpuint);
	DEC_UINT_FLD_OBJ (tmITP, tmpuint, pObj);
	// Free context
	ASN1_FREE( ctxt )

#undef IE_NAME

    return ASN_OK;
}

int decHNBAP_RAC (OSOCTET *buf, uint len, Tcl_Obj *p_obj)
{
#define IE_NAME	RAC

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
    stat = asn1PD_RAC( &ctxt, &pdu );
	CHECK_DECODING( stat, ctxt )

	// Get TCL fields
	tmLog ("pdu.numocts %u\n", pdu.numocts);
	DEC_HEX_FLD_OBJ (tmITP, pdu.data, pdu.numocts, pObj);
	// Free context
	ASN1_FREE( ctxt )

#undef IE_NAME

    return ASN_OK;
}

int decHNBAP_LAC (OSOCTET *buf, uint len, Tcl_Obj *p_obj)
{
#define IE_NAME	LAC

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
    stat = asn1PD_LAC( &ctxt, &pdu );
	CHECK_DECODING( stat, ctxt )

	// Get TCL fields
	tmLog ("pdu.numocts %u\n", pdu.numocts);
	DEC_HEX_FLD_OBJ (tmITP, pdu.data, pdu.numocts, pObj);
	// Free context
	ASN1_FREE( ctxt )

#undef IE_NAME

    return ASN_OK;
}

int decHNBAP_SAC (OSOCTET *buf, uint len, Tcl_Obj *p_obj)
{
#define IE_NAME	SAC

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
    stat = asn1PD_SAC( &ctxt, &pdu );
	CHECK_DECODING( stat, ctxt )

	// Get TCL fields
	// tmLog ("pdu.numocts %u\n", pdu.numocts);
	DEC_HEX_FLD_OBJ (tmITP, pdu.data, pdu.numocts, pObj);
	// Free context
	ASN1_FREE( ctxt )

#undef IE_NAME

    return ASN_OK;
}

int decHNBAP_MacroCoverageInfoStruct (Tcl_Obj *p_obj, MacroCoverageInformation *p_val)
{

	DEC_START_STRUCT_OBJ (tmITP, MacroCoverageInfo, "MACRO_COVERAGE_INFO");
	tmLog ("p_val->cellIdentity.t %u",p_val->cellIdentity.t);
	DEC_INT_FLD_OBJ (tmITP, p_val->cellIdentity.t, DEC_STRUCT_PTR (MacroCoverageInfo));
    switch( p_val->cellIdentity.t )
    {
		case T_MacroCellID_uTRANCellID:
			decHNBAP_UtranCellIDStruct(DEC_STRUCT_PTR (MacroCoverageInfo),p_val->cellIdentity.u.uTRANCellID);
		   break;
		case T_MacroCellID_gERANCellID:
			decHNBAP_CGIStruct(DEC_STRUCT_PTR (MacroCoverageInfo),p_val->cellIdentity.u.gERANCellID);
		   break;
		case T_MacroCellID_extElem1:
			DEC_HEX_FLD_OBJ (tmITP, p_val->cellIdentity.u.extElem1->data, p_val->cellIdentity.u.extElem1->numocts, DEC_STRUCT_PTR (MacroCoverageInfo));
			break;
		default:
			tmAbort ("decHNBAP_MacroCoverageInfoStruct:Invalid value %u\n", p_val->cellIdentity.t);
    }
	DEC_STOP_STRUCT_OBJ (tmITP, p_obj, MacroCoverageInfo);

	return ASN_OK;
}

int decHNBAP_CGIStruct (Tcl_Obj *p_obj, CGI *p_val) {

	DEC_START_STRUCT_OBJ (tmITP, Cgi, "CGI");

	DEC_HEX_FLD_OBJ (tmITP, p_val->pLMNidentity.data, p_val->pLMNidentity.numocts, DEC_STRUCT_PTR (Cgi));
	DEC_HEX_FLD_OBJ (tmITP, p_val->lAC.data, p_val->lAC.numocts, DEC_STRUCT_PTR (Cgi));
	DEC_HEX_FLD_OBJ (tmITP, p_val->cI.data, p_val->cI.numocts, DEC_STRUCT_PTR (Cgi));
	DEC_STOP_STRUCT_OBJ (tmITP, p_obj, Cgi);

	return ASN_OK;

}

int decHNBAP_UtranCellIDStruct (Tcl_Obj *p_obj, UTRANCellID *p_val)
{
    uint tmpuint;
	DEC_START_STRUCT_OBJ (tmITP, UtranCellID, "UTRAN_CELLID");

	DEC_HEX_FLD_OBJ (tmITP, p_val->lAC.data, p_val->lAC.numocts, DEC_STRUCT_PTR (UtranCellID));
	DEC_HEX_FLD_OBJ (tmITP, p_val->rAC.data, p_val->rAC.numocts, DEC_STRUCT_PTR (UtranCellID));
	DEC_HEX_FLD_OBJ (tmITP, p_val->pLMNidentity.data, p_val->pLMNidentity.numocts, DEC_STRUCT_PTR (UtranCellID));
	tmpuint = b2l_int (p_val->uTRANcellID.data, p_val->uTRANcellID.numbits);
	// tmLog ("p_val->uTRANcellID.data %u\n", tmpuint);
	DEC_UINT_FLD_OBJ (tmITP, tmpuint, DEC_STRUCT_PTR (UtranCellID));
	DEC_STOP_STRUCT_OBJ (tmITP, p_obj, UtranCellID);

	return ASN_OK;
}

int decHNBAP_GeographicalCoordinatesStruct (Tcl_Obj *p_obj, GeographicalLocation *p_val)
{

	DEC_START_STRUCT_OBJ (tmITP, GeographicalLocation, "GEOGRAPHICCAL_LOC");
	//GeographicalCoordinates
	DEC_UINT_FLD_OBJ (tmITP, p_val->geographicalCoordinates.latitudeSign, DEC_STRUCT_PTR (GeographicalLocation));
	DEC_UINT_FLD_OBJ (tmITP, p_val->geographicalCoordinates.latitude, DEC_STRUCT_PTR (GeographicalLocation));
	DEC_INT_FLD_OBJ (tmITP, p_val->geographicalCoordinates.longitude, DEC_STRUCT_PTR (GeographicalLocation));
	//AltitudeAndDirection
	DEC_UINT_FLD_OBJ (tmITP, p_val->altitudeAndDirection.directionOfAltitude, DEC_STRUCT_PTR (GeographicalLocation));
	DEC_USHORT_FLD_OBJ (tmITP, p_val->altitudeAndDirection.altitude, DEC_STRUCT_PTR (GeographicalLocation));

	DEC_STOP_STRUCT_OBJ (tmITP, p_obj, GeographicalLocation);

	return ASN_OK;

}

int decHNBAP_HNB_Location_Information (OSOCTET *buf, uint len, Tcl_Obj *p_obj)
{
#define IE_NAME	HNB_Location_Information

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
    stat = asn1PD_HNB_Location_Information( &ctxt, &pdu );
	CHECK_DECODING( stat, ctxt )

	// Get TCL fields
	DEC_START_STRUCT_OBJ (tmITP, HnbLocInfo, "HNB_LOC_INFO");
	if (pdu.m.macroCoverageInfoPresent) {
		decHNBAP_MacroCoverageInfoStruct(DEC_STRUCT_PTR (HnbLocInfo),&pdu.macroCoverageInfo);
	} else {
		DEC_NOTPRES_FLD_OBJ (tmITP, DEC_STRUCT_PTR (HnbLocInfo));
	}

	if (pdu.m.geographicalCoordinatesPresent){
		decHNBAP_GeographicalCoordinatesStruct(DEC_STRUCT_PTR (HnbLocInfo),&pdu.geographicalCoordinates);
	} else {
		DEC_NOTPRES_FLD_OBJ (tmITP, DEC_STRUCT_PTR (HnbLocInfo));
	}

	DEC_STOP_STRUCT_OBJ (tmITP, pObj, HnbLocInfo);

	// Free context
	ASN1_FREE( ctxt )

#undef IE_NAME

    return ASN_OK;
}

int decHNBAP_CSG_ID (OSOCTET *buf, uint len, Tcl_Obj *p_obj)
{
#define IE_NAME	CSG_ID

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
    stat = asn1PD_CSG_ID( &ctxt, &pdu );
	CHECK_DECODING( stat, ctxt )

	// Get TCL fields
	// tmLog ("pdu.numbits %u\n", pdu.numbits);
	DEC_HEX_FLD_OBJ (tmITP, pdu.data, ( pdu.numbits /8 ), pObj);
	// Free context
	ASN1_FREE( ctxt )

#undef IE_NAME

    return ASN_OK;
}

int decHNBAP_RNC_ID (OSOCTET *buf, uint len, Tcl_Obj *p_obj)
{
#define IE_NAME	RNC_ID

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
    stat = asn1PD_RNC_ID( &ctxt, &pdu );
	CHECK_DECODING( stat, ctxt )

	// Get TCL fields
	// tmLog ("RncID value %u\n", pdu);
	DEC_USHORT_FLD_OBJ (tmITP, pdu, pObj);
	// Free context
	ASN1_FREE( ctxt )

#undef IE_NAME

    return ASN_OK;
}


int decHNBAP_Cause (OSOCTET *buf, uint len, Tcl_Obj *p_obj)
{
#define IE_NAME	Cause

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
    stat = asn1PD_Cause( &ctxt, &pdu );
	CHECK_DECODING( stat, ctxt )

/*
    if( !&pdu )
		ASN1_RETURN( ctxt )
*/
    DEC_START_STRUCT_OBJ (tmITP, Cause, "CAUSE");

	tmLog ("pdu.t %u\n", pdu.t);
    DEC_INT_FLD_OBJ (tmITP, pdu.t, DEC_STRUCT_PTR (Cause));
    switch( pdu.t )
    {
    case T_Cause_radioNetwork:
		// tmLog ("pdu.u.radioNetwork %u\n", pdu.u.radioNetwork);
        DEC_UINT_FLD_OBJ (tmITP, pdu.u.radioNetwork, DEC_STRUCT_PTR (Cause));
       break;
    case T_Cause_transport:
    	// tmLog ("pdu.u.transport %u\n", pdu.u.transport);
	    DEC_UINT_FLD_OBJ (tmITP, pdu.u.transport, DEC_STRUCT_PTR (Cause));
       break;
    case T_Cause_protocol:
    	// tmLog ("pdu.u.protocol %u\n", pdu.u.protocol);
        DEC_UINT_FLD_OBJ (tmITP, pdu.u.protocol, DEC_STRUCT_PTR (Cause));
        break;
    case T_Cause_misc:
    	// tmLog ("pdu.u.misc %u\n", pdu.u.misc);
        DEC_UINT_FLD_OBJ (tmITP, pdu.u.misc, DEC_STRUCT_PTR (Cause));
        break;
    case T_Cause_extElem1:
		DEC_NOTPRES_FLD_OBJ (tmITP, DEC_STRUCT_PTR (Cause));
        break;
    default:
		tmAbort ("decHNBAP_Cause:Invalid value %u\n", pdu.t);
    }
    DEC_STOP_STRUCT_OBJ (tmITP, pObj, Cause);

    // Free context
	ASN1_FREE( ctxt )

#undef IE_NAME

    return ASN_OK;
}

int decHNBAP_CriticalityDiagnostics  (OSOCTET *buf, uint len, Tcl_Obj *p_obj)
{
#define IE_NAME	CriticalityDiagnostics

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
    stat = asn1PD_CriticalityDiagnostics( &ctxt, &pdu );
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
#define ITEM ((CriticalityDiagnostics_IE_List_element *)(p_node->data))
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


int decHNBAP_BackoffTimer (OSOCTET *buf, uint len, Tcl_Obj *p_obj)
{
#define IE_NAME	BackoffTimer

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
    stat = asn1PD_BackoffTimer( &ctxt, &pdu );
	CHECK_DECODING( stat, ctxt )

	// Get TCL fields
	// tmLog ("BackoffTimer value %u\n", pdu);
	DEC_UINT_FLD_OBJ (tmITP, pdu, pObj);
	// Free context
	ASN1_FREE( ctxt )

#undef IE_NAME

    return ASN_OK;
}

int decHNBAP_Registration_Cause (OSOCTET *buf, uint len, Tcl_Obj *p_obj)
{
#define IE_NAME	Registration_Cause

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
    stat = asn1PD_Registration_Cause( &ctxt, &pdu );
	CHECK_DECODING( stat, ctxt )

	// Get TCL fields
	// tmLog ("Registration cause value %u\n", pdu);
	DEC_UINT_FLD_OBJ (tmITP, pdu, pObj);
	// Free context
	ASN1_FREE( ctxt )

#undef IE_NAME

    return ASN_OK;
}


int decHNBAP_UE_Identity (OSOCTET *buf, uint len, Tcl_Obj *p_obj)
{
#define IE_NAME	UE_Identity

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
    stat = asn1PD_UE_Identity( &ctxt, &pdu );
	CHECK_DECODING( stat, ctxt )

	// Get TCL fields
	DEC_START_STRUCT_OBJ (tmITP, UeId, "UE_ID");
	// tmLog("pdu.t: %u",pdu.t);
	DEC_INT_FLD_OBJ (tmITP, pdu.t, DEC_STRUCT_PTR (UeId));
    switch( pdu.t )
    {
		case T_UE_Identity_iMSI:
			DEC_HEX_FLD_OBJ (tmITP, pdu.u.iMSI->data, pdu.u.iMSI->numocts, DEC_STRUCT_PTR (UeId));
		   break;
		case T_UE_Identity_tMSILAI:
			decHNBAP_TMSILAIStruct(DEC_STRUCT_PTR (UeId),pdu.u.tMSILAI);
		   break;
		case T_UE_Identity_pTMSIRAI:
			decHNBAP_PTMSIRAIStruct(DEC_STRUCT_PTR (UeId),pdu.u.pTMSIRAI);
			break;
		case T_UE_Identity_iMEI:
			DEC_HEX_FLD_OBJ (tmITP, pdu.u.iMEI->data, (pdu.u.iMEI->numbits / 8), DEC_STRUCT_PTR (UeId));
		   break;
		case T_UE_Identity_eSN:
			DEC_HEX_FLD_OBJ (tmITP, pdu.u.eSN->data, (pdu.u.eSN->numbits / 8), DEC_STRUCT_PTR (UeId));
		   break;
		case T_UE_Identity_iMSIDS41:
			DEC_HEX_FLD_OBJ (tmITP, pdu.u.iMSIDS41->data, pdu.u.iMSIDS41->numocts, DEC_STRUCT_PTR (UeId));
			break;
		case T_UE_Identity_iMSIESN:
			decHNBAP_IMSIESNStruct(DEC_STRUCT_PTR (UeId),pdu.u.iMSIESN);
			break;
		case T_UE_Identity_tMSIDS41:
			DEC_HEX_FLD_OBJ (tmITP, pdu.u.tMSIDS41->data, pdu.u.tMSIDS41->numocts, DEC_STRUCT_PTR (UeId));
			break;
		case T_UE_Identity_extElem1:
			DEC_HEX_FLD_OBJ (tmITP, pdu.u.extElem1->data, pdu.u.extElem1->numocts, DEC_STRUCT_PTR (UeId));
			break;
		default:
			tmAbort ("decHNBAP_UE_Identity: Invalid value %u\n", pdu.t);
    }
	DEC_STOP_STRUCT_OBJ (tmITP, pObj, UeId);
	// Free context
	ASN1_FREE( ctxt )

#undef IE_NAME

    return ASN_OK;
}

int decHNBAP_TMSILAIStruct (Tcl_Obj *p_obj, TMSILAI *p_val)
{

	DEC_START_STRUCT_OBJ (tmITP, TmsiLai, "TMSILAI");
	DEC_HEX_FLD_OBJ (tmITP, p_val->tMSI.data, (p_val->tMSI.numbits /8), DEC_STRUCT_PTR (TmsiLai));
	//lai
	DEC_HEX_FLD_OBJ (tmITP, p_val->lAI.pLMNID.data, p_val->lAI.pLMNID.numocts, DEC_STRUCT_PTR (TmsiLai));
	DEC_HEX_FLD_OBJ (tmITP, p_val->lAI.lAC.data, p_val->lAI.lAC.numocts, DEC_STRUCT_PTR (TmsiLai));
	DEC_STOP_STRUCT_OBJ (tmITP, p_obj, TmsiLai);

	return ASN_OK;
}


int decHNBAP_PTMSIRAIStruct (Tcl_Obj *p_obj, PTMSIRAI *p_val)
{

	DEC_START_STRUCT_OBJ (tmITP, PtmsiRai, "PTMSIRAI");
	DEC_HEX_FLD_OBJ (tmITP, p_val->pTMSI.data, (p_val->pTMSI.numbits /8), DEC_STRUCT_PTR (PtmsiRai));
	//Rai -> lai
	DEC_HEX_FLD_OBJ (tmITP, p_val->rAI.lAI.pLMNID.data, p_val->rAI.lAI.pLMNID.numocts, DEC_STRUCT_PTR (PtmsiRai));
	DEC_HEX_FLD_OBJ (tmITP, p_val->rAI.lAI.lAC.data, p_val->rAI.lAI.lAC.numocts, DEC_STRUCT_PTR (PtmsiRai));
	//Rai-> Rac
	DEC_HEX_FLD_OBJ (tmITP, p_val->rAI.rAC.data, p_val->rAI.rAC.numocts, DEC_STRUCT_PTR (PtmsiRai));
	DEC_STOP_STRUCT_OBJ (tmITP, p_obj, PtmsiRai);

	return ASN_OK;
}

int decHNBAP_IMSIESNStruct (Tcl_Obj *p_obj, IMSIESN *p_val)
{

	DEC_START_STRUCT_OBJ (tmITP, ImsiEsn, "IMSIESN");
	DEC_HEX_FLD_OBJ (tmITP, p_val->iMSIDS41.data, p_val->iMSIDS41.numocts, DEC_STRUCT_PTR (ImsiEsn));
	DEC_HEX_FLD_OBJ (tmITP, p_val->eSN.data, (p_val->eSN.numbits / 8), DEC_STRUCT_PTR (ImsiEsn));
	DEC_STOP_STRUCT_OBJ (tmITP, p_obj, ImsiEsn);

	return ASN_OK;
}

int decHNBAP_UE_Capabilities (OSOCTET *buf, uint len, Tcl_Obj *p_obj)
{
#define IE_NAME	UE_Capabilities

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
    stat = asn1PD_UE_Capabilities ( &ctxt, &pdu );
	CHECK_DECODING( stat, ctxt )

	// Get TCL fields
	DEC_START_STRUCT_OBJ (tmITP, UeCap, "UE_CAP");
	DEC_UINT_FLD_OBJ (tmITP, pdu.access_stratum_release_indicator, DEC_STRUCT_PTR(UeCap));
	DEC_UINT_FLD_OBJ (tmITP, pdu.csg_indicator, DEC_STRUCT_PTR(UeCap));
	DEC_STOP_STRUCT_OBJ (tmITP, pObj, UeCap);

	// Free context
	ASN1_FREE( ctxt )

#undef IE_NAME

    return ASN_OK;
}

int decHNBAP_Context_ID (OSOCTET *buf, uint len, Tcl_Obj *p_obj)
{
#define IE_NAME	Context_ID

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
    stat = asn1PD_Context_ID( &ctxt, &pdu );
	CHECK_DECODING( stat, ctxt )

	// Get TCL fields
	tmpuint = b2l_int (pdu.data, 24);
	// tmLog ("pdu.data %u\n", tmpuint);
	DEC_UINT_FLD_OBJ (tmITP, tmpuint, pObj);
	// Free context
	ASN1_FREE( ctxt )

#undef IE_NAME

    return ASN_OK;
}


