/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/HNBAP/tags/HNBAP-1.3.0/src/encIeHNBAP.c $
$Author: roger $
$Date: 2012-07-27 15:55:36 +0200 (Fri, 27 Jul 2012) $
$Rev: 53537 $
----------------------------------------------------------------
Description : HNBAP SIGNALS ENCODING IEs
--------------------------------------------------------------*/

/*............................................................*/
/*  Include */
#include "encIeHNBAP.h"
#include "codecHNBAP.h"
#include "tm_compat.h"

/***********************************************************************
************************************************************************
                Encoding functions for HNBAP IEs
************************************************************************
************************************************************************/
int encHNBAP_Cause (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality)
{
#define IE_NAME			Cause
#define IE_ID			ASN1V_id_Cause

	OSCTXT                    ctxt;
	OSOCTET                   *buf;
    OSBOOL                    aligned = TRUE;
    IE_NAME                     *p_pdu;
    ProtocolIE_Field       *p_IEfield;
    int                         len = 0;
    int                         stat;

	// Initialize context
	ASN1_INIT_CTXT( ctxt )

	// Define buffer for encoded message
	ASN1_ALLOC( buf, p_ctxt, defsPduMAX_SIZE_IE)
	ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_IE, aligned )

	// Fill IE data structure
	ASN1_ALLOC( p_pdu, &ctxt, sizeof(IE_NAME) )

    ENC_START_STRUCT_OBJ (tmITP, p_obj, Cause);
	p_pdu->t = ENC_INT_FLD_OBJ (tmITP, "Tag", ENC_STRUCT_FIELD_PTR (Cause, 1));
	tmLog ("p_pdu->t %u\n", p_pdu->t);
	switch (p_pdu->t)
    {
		case T_Cause_radioNetwork:
			p_pdu->u.radioNetwork = ENC_UINT_FLD_OBJ (tmITP, "Value", ENC_STRUCT_FIELD_PTR (Cause, 2));
			// tmLog ("p_pdu->u.radioNetwork %u\n", p_pdu->u.radioNetwork);
		   break;
		case T_Cause_transport:
			p_pdu->u.transport = ENC_UINT_FLD_OBJ (tmITP, "Value", ENC_STRUCT_FIELD_PTR (Cause, 2));
			// tmLog ("p_pdu->u.transport %u\n", p_pdu->u.transport);
		   break;
		case T_Cause_protocol:
			p_pdu->u.protocol = ENC_UINT_FLD_OBJ (tmITP, "Value", ENC_STRUCT_FIELD_PTR (Cause, 2));
			// tmLog ("p_pdu->u.protocol %u\n", p_pdu->u.protocol);
			break;
		case T_Cause_misc:
			p_pdu->u.misc = ENC_UINT_FLD_OBJ (tmITP, "Value", ENC_STRUCT_FIELD_PTR (Cause, 2));
			// tmLog ("p_pdu->u.misc %u\n", p_pdu->u.misc);
			break;
		case T_Cause_extElem1:
			p_pdu->u.extElem1->numocts = ENC_HEX_FLD_OBJ (tmITP, "extElem1", p_pdu->u.extElem1->data, ENC_STRUCT_FIELD_PTR (Cause, 2));
			break;
		default:
			tmAbort ("Invalid Tag %d", p_pdu->t);
    }

   	ENC_STOP_STRUCT_OBJ (Cause);

	// Call ASN1 encoding function
   	stat = asn1PE_Cause( &ctxt, p_pdu );
	CHECK_ENCODING( stat, ctxt )

	// Get length
   	len += pu_getMsgLen (&ctxt);

	// Build ProtocolIE_Field
	ASN1_ALLOC( p_IEfield, p_ctxt, sizeof(ProtocolIE_Field) )

    p_IEfield->id              = IE_ID;
    p_IEfield->criticality     = criticality;
    p_IEfield->value.numocts   = len;
    p_IEfield->value.data      = buf;

	// Append IE to list
	ASN1_LIST_APPEND( p_ctxt, p_list, p_IEfield );

	// Free allocated memory
	ASN1_FREE( ctxt )

#undef IE_NAME
#undef IE_ID

    return ASN_OK;
}

int encHNBAP_HNB_Identity (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality)
{
#define IE_NAME			HNB_Identity
#define IE_ID			ASN1V_id_HNB_Identity

	OSCTXT                    ctxt;
	OSOCTET                   *buf;
    OSBOOL                    aligned = TRUE;
    IE_NAME                     *p_pdu;
    ProtocolIE_Field            *p_IEfield;
    int                         len = 0;
    int                         stat;

	// Initialize context
	ASN1_INIT_CTXT( ctxt )

	// Define buffer for encoded message
	ASN1_ALLOC( buf, p_ctxt, defsPduMAX_SIZE_IE)
	ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_IE, aligned )

	// Fill IE data structure
	ASN1_ALLOC( p_pdu, &ctxt, sizeof(IE_NAME) )

	p_pdu->hNB_Identity_Info.numocts = ENC_HEX_FLD_OBJ (tmITP, "HnbapId", p_pdu->hNB_Identity_Info.data, p_obj);
    p_pdu->m.iE_ExtensionsPresent = 0;
	// Call ASN1 encoding function
   	stat = asn1PE_HNB_Identity( &ctxt, p_pdu );
	CHECK_ENCODING( stat, ctxt )

	// Get length
   	len += pu_getMsgLen (&ctxt);

	// Build ProtocolIE_Field
	ASN1_ALLOC( p_IEfield, p_ctxt, sizeof(ProtocolIE_Field) )

    p_IEfield->id              = IE_ID;
    p_IEfield->criticality     = criticality;
    p_IEfield->value.numocts   = len;
    p_IEfield->value.data      = buf;

	// Append IE to list
	ASN1_LIST_APPEND( p_ctxt, p_list, p_IEfield );

	// Free allocated memory
	ASN1_FREE( ctxt )

#undef IE_NAME
#undef IE_ID

    return ASN_OK;
}

int encHNBAP_PLMNidentity (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality)
{
#define IE_NAME			PLMNidentity
#define IE_ID			ASN1V_id_PLMNidentity

	OSCTXT                    ctxt;
	OSOCTET                   *buf;
    OSBOOL                    aligned = TRUE;
    IE_NAME                     *p_pdu;
    ProtocolIE_Field            *p_IEfield;
    int                         len = 0;
    int                         stat;

	// Initialize context
	ASN1_INIT_CTXT( ctxt )

	// Define buffer for encoded message
	ASN1_ALLOC( buf, p_ctxt, defsPduMAX_SIZE_IE)
	ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_IE, aligned )

	// Fill IE data structure
	ASN1_ALLOC( p_pdu, &ctxt, sizeof(IE_NAME) )

	p_pdu->numocts = ENC_HEX_FLD_OBJ (tmITP, "PlmnId", p_pdu->data, p_obj);

	// Call ASN1 encoding function
   	stat = asn1PE_PLMNidentity( &ctxt, p_pdu );
	CHECK_ENCODING( stat, ctxt )

	// Get length
   	len += pu_getMsgLen (&ctxt);

	// Build ProtocolIE_Field
	ASN1_ALLOC( p_IEfield, p_ctxt, sizeof(ProtocolIE_Field) )

    p_IEfield->id              = IE_ID;
    p_IEfield->criticality     = criticality;
    p_IEfield->value.numocts   = len;
    p_IEfield->value.data      = buf;

	// Append IE to list
	ASN1_LIST_APPEND( p_ctxt, p_list, p_IEfield );

	// Free allocated memory
	ASN1_FREE( ctxt )

#undef IE_NAME
#undef IE_ID

    return ASN_OK;
}

int encHNBAP_CellIdentity (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality)
{
#define IE_NAME			CellIdentity
#define IE_ID			ASN1V_id_CellIdentity

	OSCTXT                    ctxt;
	OSOCTET                   *buf;
    OSBOOL                    aligned = TRUE;
    IE_NAME                     *p_pdu;
    ProtocolIE_Field            *p_IEfield;
    int                         len = 0;
    int                         stat;
    uint                        tmpuint;

	// Initialize context
	ASN1_INIT_CTXT( ctxt )

	// Define buffer for encoded message
	ASN1_ALLOC( buf, p_ctxt, defsPduMAX_SIZE_IE)
	ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_IE, aligned )

	// Fill IE data structure
	ASN1_ALLOC( p_pdu, &ctxt, sizeof(IE_NAME) )

	tmpuint = ENC_UINT_FLD_OBJ (tmITP, "Cell_ID", p_obj);
	// tmLog ("tmpuint %u\n", tmpuint);
	p_pdu->numbits = 28;
	l2b_int(tmpuint, p_pdu->data, p_pdu->numbits);
/*
	*(uint *)(p_pdu->data) =(uint) l2b_hnbap_int (tmpuint << 4);

    tmLog ("p_pdu.data %u\n", *(uint *)(p_pdu->data));
    
    tmLog ("p_pdu.data[0] 0x%x", p_pdu->data[0]);
    tmLog ("p_pdu.data[1] 0x%x", p_pdu->data[1]);
    tmLog ("p_pdu.data[2] 0x%x", p_pdu->data[2]);
    tmLog ("p_pdu.data[3] 0x%x", p_pdu->data[3]);
    */
	// Call ASN1 encoding function
   	stat = asn1PE_CellIdentity( &ctxt, p_pdu );
	CHECK_ENCODING( stat, ctxt )

	// Get length
   	len += pu_getMsgLen (&ctxt);

	// Build ProtocolIE_Field
	ASN1_ALLOC( p_IEfield, p_ctxt, sizeof(ProtocolIE_Field) )

    p_IEfield->id              = IE_ID;
    p_IEfield->criticality     = criticality;
    p_IEfield->value.numocts   = len;
    p_IEfield->value.data      = buf;

	// Append IE to list
	ASN1_LIST_APPEND( p_ctxt, p_list, p_IEfield );

	// Free allocated memory
	ASN1_FREE( ctxt )

#undef IE_NAME
#undef IE_ID

    return ASN_OK;
}
int encHNBAP_LAC (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality)
{
#define IE_NAME			LAC
#define IE_ID			ASN1V_id_LAC

	OSCTXT                    ctxt;
	OSOCTET                   *buf;
    OSBOOL                    aligned = TRUE;
    IE_NAME                     *p_pdu;
    ProtocolIE_Field            *p_IEfield;
    int                         len = 0;
    int                         stat;
//    uint                        tmpuint;

	// Initialize context
	ASN1_INIT_CTXT( ctxt )

	// Define buffer for encoded message
	ASN1_ALLOC( buf, p_ctxt, defsPduMAX_SIZE_IE)
	ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_IE, aligned )

	// Fill IE data structure
	ASN1_ALLOC( p_pdu, &ctxt, sizeof(IE_NAME) )

	p_pdu->numocts = ENC_HEX_FLD_OBJ (tmITP, "LAC", p_pdu->data, p_obj);


	// Call ASN1 encoding function
   	stat = asn1PE_LAC( &ctxt, p_pdu );
	CHECK_ENCODING( stat, ctxt )

	// Get length
   	len += pu_getMsgLen (&ctxt);

	// Build ProtocolIE_Field
	ASN1_ALLOC( p_IEfield, p_ctxt, sizeof(ProtocolIE_Field) )

    p_IEfield->id              = IE_ID;
    p_IEfield->criticality     = criticality;
    p_IEfield->value.numocts   = len;
    p_IEfield->value.data      = buf;

	// Append IE to list
	ASN1_LIST_APPEND( p_ctxt, p_list, p_IEfield );

	// Free allocated memory
	ASN1_FREE( ctxt )

#undef IE_NAME
#undef IE_ID

    return ASN_OK;
}

int encHNBAP_RAC (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality)
{
#define IE_NAME			RAC
#define IE_ID			ASN1V_id_RAC

	OSCTXT                    ctxt;
	OSOCTET                   *buf;
    OSBOOL                    aligned = TRUE;
    IE_NAME                     *p_pdu;
    ProtocolIE_Field            *p_IEfield;
    int                         len = 0;
    int                         stat;
//    uint                        tmpuint;

	// Initialize context
	ASN1_INIT_CTXT( ctxt )

	// Define buffer for encoded message
	ASN1_ALLOC( buf, p_ctxt, defsPduMAX_SIZE_IE)
	ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_IE, aligned )

	// Fill IE data structure
	ASN1_ALLOC( p_pdu, &ctxt, sizeof(IE_NAME) )

	p_pdu->numocts = ENC_HEX_FLD_OBJ (tmITP, "RAC", p_pdu->data, p_obj);


	// Call ASN1 encoding function
   	stat = asn1PE_RAC( &ctxt, p_pdu );
	CHECK_ENCODING( stat, ctxt )

	// Get length
   	len += pu_getMsgLen (&ctxt);

	// Build ProtocolIE_Field
	ASN1_ALLOC( p_IEfield, p_ctxt, sizeof(ProtocolIE_Field) )

    p_IEfield->id              = IE_ID;
    p_IEfield->criticality     = criticality;
    p_IEfield->value.numocts   = len;
    p_IEfield->value.data      = buf;

	// Append IE to list
	ASN1_LIST_APPEND( p_ctxt, p_list, p_IEfield );

	// Free allocated memory
	ASN1_FREE( ctxt )

#undef IE_NAME
#undef IE_ID

    return ASN_OK;
}

int encHNBAP_SAC (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality)
{
#define IE_NAME			SAC
#define IE_ID			ASN1V_id_SAC

	OSCTXT                    ctxt;
	OSOCTET                   *buf;
    OSBOOL                    aligned = TRUE;
    IE_NAME                     *p_pdu;
    ProtocolIE_Field            *p_IEfield;
    int                         len = 0;
    int                         stat;
//    uint                        tmpuint;

	// Initialize context
	ASN1_INIT_CTXT( ctxt )

	// Define buffer for encoded message
	ASN1_ALLOC( buf, p_ctxt, defsPduMAX_SIZE_IE)
	ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_IE, aligned )

	// Fill IE data structure
	ASN1_ALLOC( p_pdu, &ctxt, sizeof(IE_NAME) )

	p_pdu->numocts = ENC_HEX_FLD_OBJ (tmITP, "SAC", p_pdu->data, p_obj);


	// Call ASN1 encoding function
   	stat = asn1PE_SAC( &ctxt, p_pdu );
	CHECK_ENCODING( stat, ctxt )

	// Get length
   	len += pu_getMsgLen (&ctxt);

	// Build ProtocolIE_Field
	ASN1_ALLOC( p_IEfield, p_ctxt, sizeof(ProtocolIE_Field) )

    p_IEfield->id              = IE_ID;
    p_IEfield->criticality     = criticality;
    p_IEfield->value.numocts   = len;
    p_IEfield->value.data      = buf;

	// Append IE to list
	ASN1_LIST_APPEND( p_ctxt, p_list, p_IEfield );

	// Free allocated memory
	ASN1_FREE( ctxt )

#undef IE_NAME
#undef IE_ID

    return ASN_OK;
}

int encHNBAP_CSG_ID (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality)
{
#define IE_NAME			CSG_ID
#define IE_ID			ASN1V_id_CSG_ID

	OSCTXT                    ctxt;
	OSOCTET                   *buf;
    OSBOOL                    aligned = TRUE;
    IE_NAME                     *p_pdu;
    ProtocolIE_Field            *p_IEfield;
    int                         len = 0;
    int                         stat;
//  uint                        tmpuint;

	// Initialize context
	ASN1_INIT_CTXT( ctxt )

	// Define buffer for encoded message
	ASN1_ALLOC( buf, p_ctxt, defsPduMAX_SIZE_IE)
	ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_IE, aligned )

	// Fill IE data structure
	ASN1_ALLOC( p_pdu, &ctxt, sizeof(IE_NAME) )

	p_pdu->numbits = 27;
	ENC_HEX_FLD_OBJ (tmITP, "CsgId", p_pdu->data, p_obj);


	// Call ASN1 encoding function
   	stat = asn1PE_CSG_ID( &ctxt, p_pdu );
	CHECK_ENCODING( stat, ctxt )

	// Get length
   	len += pu_getMsgLen (&ctxt);

	// Build ProtocolIE_Field
	ASN1_ALLOC( p_IEfield, p_ctxt, sizeof(ProtocolIE_Field) )

    p_IEfield->id              = IE_ID;
    p_IEfield->criticality     = criticality;
    p_IEfield->value.numocts   = len;
    p_IEfield->value.data      = buf;

	// Append IE to list
	ASN1_LIST_APPEND( p_ctxt, p_list, p_IEfield );

	// Free allocated memory
	ASN1_FREE( ctxt )

#undef IE_NAME
#undef IE_ID

    return ASN_OK;
}

int encHNBAP_HNB_Location_Information (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality)
{
#define IE_NAME			HNB_Location_Information
#define IE_ID			ASN1V_id_HNB_Location_Information

	OSCTXT                    ctxt;
	OSOCTET                   *buf;
    OSBOOL                    aligned = TRUE;
    IE_NAME                     *p_pdu;
    ProtocolIE_Field            *p_IEfield;
    int                         len = 0;
    int                         stat;
//    uint                        tmpuint;

	// Initialize context
	ASN1_INIT_CTXT( ctxt )

	// Define buffer for encoded message
	ASN1_ALLOC( buf, p_ctxt, defsPduMAX_SIZE_IE)
	ASN1_SET_BUFFER( ctxt, buf,defsPduMAX_SIZE_IE, aligned )

	// Fill IE data structure
	ASN1_ALLOC( p_pdu, &ctxt, sizeof(IE_NAME) )

	ENC_START_STRUCT_OBJ (tmITP, p_obj, HNB_LOC_INFO);
	if (FIELD_PRES_OBJ ("MacroCoverageInformation", ENC_STRUCT_FIELD_PTR (HNB_LOC_INFO, 1)))
	{
		p_pdu->m.macroCoverageInfoPresent = 1;
		encHNBAP_MacroCoverageInformationStruct(ENC_STRUCT_FIELD_PTR (HNB_LOC_INFO, 1),&p_pdu->macroCoverageInfo,&ctxt);
	} else
	{
		p_pdu->m.macroCoverageInfoPresent = 0;
		tmLog ("p_pdu->m.macroCoverageInfoPresent %u\n", p_pdu->m.macroCoverageInfoPresent);
	}

	if (FIELD_PRES_OBJ ("GeographicalLocation", ENC_STRUCT_FIELD_PTR (HNB_LOC_INFO, 2)))
	{
		p_pdu->m.geographicalCoordinatesPresent = 1;
		encHNBAP_GeographicalLocationStruct(ENC_STRUCT_FIELD_PTR (HNB_LOC_INFO, 2),&p_pdu->geographicalCoordinates,&ctxt);
	} else
	{
		p_pdu->m.geographicalCoordinatesPresent = 0;
		tmLog ("p_pdu->m.geographicalCoordinatesPresent %u\n", p_pdu->m.geographicalCoordinatesPresent);
	}

	ENC_STOP_STRUCT_OBJ (HNB_LOC_INFO);


	// Call ASN1 encoding function
   	stat = asn1PE_HNB_Location_Information( &ctxt, p_pdu );
	CHECK_ENCODING( stat, ctxt )

	// Get length
   	len += pu_getMsgLen (&ctxt);

	// Build ProtocolIE_Field
	ASN1_ALLOC( p_IEfield, p_ctxt, sizeof(ProtocolIE_Field) )

    p_IEfield->id              = IE_ID;
    p_IEfield->criticality     = criticality;
    p_IEfield->value.numocts   = len;
    p_IEfield->value.data      = buf;

	// Append IE to list
	ASN1_LIST_APPEND( p_ctxt, p_list, p_IEfield );

	// Free allocated memory
	ASN1_FREE( ctxt )

#undef IE_NAME
#undef IE_ID

    return ASN_OK;
}

int encHNBAP_MacroCoverageInformationStruct (Tcl_Obj *p_obj, MacroCoverageInformation *p_val, OSCTXT *p_ctxt)
{
    uint tmpuint;
	ENC_START_STRUCT_OBJ (tmITP, p_obj, MacroCoverageInformation);
	p_val->cellIdentity.t = ENC_INT_FLD_OBJ (tmITP, "Tag", ENC_STRUCT_FIELD_PTR (MacroCoverageInformation, 1));
	switch (p_val->cellIdentity.t)
    {
		case T_MacroCellID_uTRANCellID:
			ENC_START_STRUCT_OBJ (tmITP, ENC_STRUCT_FIELD_PTR(MacroCoverageInformation,2), UTRAN_CELLID);
			ASN1_ALLOC (p_val->cellIdentity.u.uTRANCellID, p_ctxt, sizeof (UTRANCellID));
			p_val->cellIdentity.u.uTRANCellID->lAC.numocts = 2;
			ENC_HEX_FLD_OBJ (tmITP, "LAC", p_val->cellIdentity.u.uTRANCellID->lAC.data, ENC_STRUCT_FIELD_PTR (UTRAN_CELLID, 1));
			p_val->cellIdentity.u.uTRANCellID->rAC.numocts = 1;
			ENC_HEX_FLD_OBJ (tmITP, "RAC", p_val->cellIdentity.u.uTRANCellID->rAC.data, ENC_STRUCT_FIELD_PTR (UTRAN_CELLID, 2));
			//PLMNidentity
			p_val->cellIdentity.u.uTRANCellID->pLMNidentity.numocts = 3;
			ENC_HEX_FLD_OBJ (tmITP, "PLMNidentity", p_val->cellIdentity.u.uTRANCellID->pLMNidentity.data, ENC_STRUCT_FIELD_PTR (UTRAN_CELLID, 3));
			tmpuint = ENC_UINT_FLD_OBJ (tmITP, "Cell_ID", ENC_STRUCT_FIELD_PTR (UTRAN_CELLID, 4));
			// tmLog ("tmpuint %u\n", tmpuint);
			p_val->cellIdentity.u.uTRANCellID->uTRANcellID.numbits = 28;
			l2b_int(tmpuint, p_val->cellIdentity.u.uTRANCellID->uTRANcellID.data,p_val->cellIdentity.u.uTRANCellID->uTRANcellID.numbits);
			/*
			tmLog ("tmpuint 0x%x", tmpuint);
			tmLog ("p_val->cellIdentity.u.uTRANCellID->uTRANcellID.data[0] 0x%x", p_val->cellIdentity.u.uTRANCellID->uTRANcellID.data[0]);
    			tmLog ("p_val->cellIdentity.u.uTRANCellID->uTRANcellID.data[1] 0x%x", p_val->cellIdentity.u.uTRANCellID->uTRANcellID.data[1]);
    			tmLog ("p_val->cellIdentity.u.uTRANCellID->uTRANcellID.data[2] 0x%x", p_val->cellIdentity.u.uTRANCellID->uTRANcellID.data[2]);
    			tmLog ("p_val->cellIdentity.u.uTRANCellID->uTRANcellID.data[3] 0x%x", p_val->cellIdentity.u.uTRANCellID->uTRANcellID.data[3]);
			*/
			ENC_STOP_STRUCT_OBJ (UTRAN_CELLID);

		   break;
		case T_MacroCellID_gERANCellID:
			ENC_START_STRUCT_OBJ (tmITP, ENC_STRUCT_FIELD_PTR(MacroCoverageInformation,2), CGI);
			ASN1_ALLOC (p_val->cellIdentity.u.gERANCellID, p_ctxt, sizeof (CGI));
			//PLMNidentity
			p_val->cellIdentity.u.gERANCellID->pLMNidentity.numocts = 3;
			ENC_HEX_FLD_OBJ (tmITP, "PLMNidentity", p_val->cellIdentity.u.gERANCellID->pLMNidentity.data, ENC_STRUCT_FIELD_PTR (CGI, 1));
			p_val->cellIdentity.u.gERANCellID->lAC.numocts = 2;
			ENC_HEX_FLD_OBJ (tmITP, "LAC", p_val->cellIdentity.u.gERANCellID->lAC.data, ENC_STRUCT_FIELD_PTR (CGI, 2));
			p_val->cellIdentity.u.gERANCellID->cI.numocts = 2;
			ENC_HEX_FLD_OBJ (tmITP, "CI", p_val->cellIdentity.u.gERANCellID->cI.data, ENC_STRUCT_FIELD_PTR (CGI, 3));

			ENC_STOP_STRUCT_OBJ (CGI);

		   break;
		case T_MacroCellID_extElem1:
			ASN1_ALLOC (p_val->cellIdentity.u.extElem1, p_ctxt, defsPduMAX_SIZE_DATA);
			p_val->cellIdentity.u.extElem1->numocts = ENC_HEX_FLD_OBJ (tmITP, "extElem1", p_val->cellIdentity.u.extElem1->data, ENC_STRUCT_FIELD_PTR (MacroCoverageInformation, 2));
			break;
		default:
			tmAbort ("Invalid Tag %d", p_val->cellIdentity.t);
    }


	p_val->extElem1.count = 0;
	p_val->m.iE_ExtensionsPresent = 0;
	ENC_STOP_STRUCT_OBJ (MacroCoverageInformation);

	return ASN_OK;
}

int encHNBAP_GeographicalLocationStruct (Tcl_Obj *p_obj, GeographicalLocation *p_val, OSCTXT *p_ctxt)
{
	ENC_START_STRUCT_OBJ (tmITP, p_obj, GeographicalLocation);
	p_val->geographicalCoordinates.latitudeSign = ENC_UINT_FLD_OBJ (tmITP, "LatitudeSign", ENC_STRUCT_FIELD_PTR (GeographicalLocation, 1));
	p_val->geographicalCoordinates.latitude = ENC_UINT_FLD_OBJ (tmITP, "Latitude", ENC_STRUCT_FIELD_PTR (GeographicalLocation, 2));
	p_val->geographicalCoordinates.longitude = ENC_INT_FLD_OBJ (tmITP, "Longitude", ENC_STRUCT_FIELD_PTR (GeographicalLocation, 3));
	p_val->geographicalCoordinates.m.iE_ExtensionsPresent  = 0;
	p_val->geographicalCoordinates.extElem1.count = 0;
	p_val->altitudeAndDirection.directionOfAltitude = ENC_UINT_FLD_OBJ (tmITP, "DirectionOfAltitude", ENC_STRUCT_FIELD_PTR (GeographicalLocation, 4));
	p_val->altitudeAndDirection.altitude = ENC_USHORT_FLD_OBJ (tmITP, "Altitude", ENC_STRUCT_FIELD_PTR (GeographicalLocation, 5));
	p_val->altitudeAndDirection.extElem1.count = 0;
	ENC_STOP_STRUCT_OBJ (GeographicalLocation);
    p_val->m.iE_ExtensionsPresent  = 0;
    p_val->extElem1.count = 0;
	return ASN_OK;
}


int encHNBAP_RNC_ID (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality)
{
#define IE_NAME			RNC_ID
#define IE_ID			ASN1V_id_RNC_ID

	OSCTXT                    ctxt;
	OSOCTET                   *buf;
    OSBOOL                    aligned = TRUE;
    IE_NAME                     *p_pdu;
    ProtocolIE_Field            *p_IEfield;
    int                         len = 0;
    int                         stat;


	// Initialize context
	ASN1_INIT_CTXT( ctxt )

	// Define buffer for encoded message
	ASN1_ALLOC( buf, p_ctxt, defsPduMAX_SIZE_IE)
	ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_IE, aligned )

	// Fill IE data structure
	ASN1_ALLOC( p_pdu, &ctxt, sizeof(IE_NAME) )

	*p_pdu = ENC_USHORT_FLD_OBJ (tmITP, "RncId", p_obj);

	// Call ASN1 encoding function
   	stat = asn1PE_RNC_ID( &ctxt, *p_pdu );
	CHECK_ENCODING( stat, ctxt )

	// Get length
   	len += pu_getMsgLen (&ctxt);

	// Build ProtocolIE_Field
	ASN1_ALLOC( p_IEfield, p_ctxt, sizeof(ProtocolIE_Field) )

    p_IEfield->id              = IE_ID;
    p_IEfield->criticality     = criticality;
    p_IEfield->value.numocts   = len;
    p_IEfield->value.data      = buf;

	// Append IE to list
	ASN1_LIST_APPEND( p_ctxt, p_list, p_IEfield );

	// Free allocated memory
	ASN1_FREE( ctxt )

#undef IE_NAME
#undef IE_ID

    return ASN_OK;
}

int encHNBAP_CriticalityDiagnostics (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality)
{
#define IE_NAME        CriticalityDiagnostics
#define IE_ID           ASN1V_id_CriticalityDiagnostics

	OSCTXT                    ctxt;
    OSOCTET                   *buf;
    OSBOOL                    aligned = TRUE;
    IE_NAME                     *p_pdu;
    ProtocolIE_Field            *p_IEfield;
    int                         len = 0;
    int                         stat;
//	char						*tmpstring;
	uint						n, i;
	CriticalityDiagnostics_IE_List_element	*criticality_diagnostics_ie_item;


	// Initialize context
	ASN1_INIT_CTXT( ctxt )

	// Define buffer for encoded message
	ASN1_ALLOC( buf, p_ctxt, defsPduMAX_SIZE_IE)
	ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_IE, aligned )

	// Fill IE data structure
	ASN1_ALLOC( p_pdu, &ctxt, sizeof(IE_NAME) )

    ENC_START_STRUCT_OBJ (tmITP, p_obj, Criticality_Diagnostics);
	if (FIELD_PRES_OBJ ("ProcedureCode", ENC_STRUCT_FIELD_PTR (Criticality_Diagnostics, 1)))
	{
		p_pdu->m.procedureCodePresent = 1;
		// tmLog ("p_pdu->m.procedureCodePresent %u\n", p_pdu->m.procedureCodePresent);
		p_pdu->procedureCode = ENC_UCHAR_FLD_OBJ (tmITP, "ProcedureCode", ENC_STRUCT_FIELD_PTR (Criticality_Diagnostics, 1));
		// tmLog ("p_pdu->procedureCode %u\n", p_pdu->procedureCode);
	} else
	{
		p_pdu->m.procedureCodePresent = 0;
		// tmLog ("p_pdu->m.procedureCodePresent %u\n", p_pdu->m.procedureCodePresent);
	}

	if (FIELD_PRES_OBJ ("TriggeringMessage", ENC_STRUCT_FIELD_PTR (Criticality_Diagnostics, 2)))
	{
		p_pdu->m.triggeringMessagePresent = 1;
		// tmLog ("p_pdu->m.triggeringMessagePresent %u\n", p_pdu->m.triggeringMessagePresent);
		p_pdu->triggeringMessage = ENC_UINT_FLD_OBJ (tmITP, "TriggeringMessage", ENC_STRUCT_FIELD_PTR (Criticality_Diagnostics, 2));
		// tmLog ("p_pdu->triggeringMessage %u\n", p_pdu->triggeringMessage);
	} else
	{
		p_pdu->m.triggeringMessagePresent = 0;
		// tmLog ("p_pdu->m.triggeringMessagePresent %u\n", p_pdu->m.triggeringMessagePresent);
	}

	if (FIELD_PRES_OBJ ("ProcedureCriticality", ENC_STRUCT_FIELD_PTR (Criticality_Diagnostics, 3)))
	{
		p_pdu->m.procedureCriticalityPresent = 1;
		// tmLog ("p_pdu->m.procedureCriticalityPresent %u\n", p_pdu->m.procedureCriticalityPresent);
		p_pdu->procedureCriticality = ENC_UINT_FLD_OBJ (tmITP, "ProcedureCriticality", ENC_STRUCT_FIELD_PTR (Criticality_Diagnostics, 3));
	} else
	{
		p_pdu->m.procedureCriticalityPresent = 0;
		// tmLog ("p_pdu->m.procedureCriticalityPresent %u\n", p_pdu->m.procedureCriticalityPresent);
	}

	if (FIELD_PRES_OBJ ("IEsCriticalityDiagnostics", ENC_STRUCT_FIELD_PTR (Criticality_Diagnostics, 4)))
	{
		p_pdu->m.iEsCriticalityDiagnosticsPresent = 1;
		// tmLog ("p_pdu->m.iEsCriticalityDiagnosticsPresent %u\n", p_pdu->m.iEsCriticalityDiagnosticsPresent);

		ASN1_INIT_LIST (&p_pdu->iEsCriticalityDiagnostics);
		ENC_START_LIST_OBJ (tmITP, n, ENC_STRUCT_FIELD_PTR (Criticality_Diagnostics, 4), IEsCriticalityDiagnostics);
		tmLog ("n %u\n", n);
		for (i = 0; i < n; i++)
		{
			ASN1_ALLOC (criticality_diagnostics_ie_item, &ctxt, sizeof (CriticalityDiagnostics_IE_List_element));
			ENC_START_STRUCT_OBJ (tmITP, ENC_LIST_FIELD_PTR (IEsCriticalityDiagnostics, i), IEsCriticalityDiagnostics_Item);
			criticality_diagnostics_ie_item->iECriticality = ENC_UINT_FLD_OBJ (tmITP, "IECriticality", ENC_STRUCT_FIELD_PTR (IEsCriticalityDiagnostics_Item, 1));

			// tmLog ("criticality_diagnostics_ie_item->iECriticality %u\n", criticality_diagnostics_ie_item->iECriticality);

			criticality_diagnostics_ie_item->iE_ID = ENC_USHORT_FLD_OBJ (tmITP, "IE_ID", ENC_STRUCT_FIELD_PTR (IEsCriticalityDiagnostics_Item, 2));
			// tmLog ("criticality_diagnostics_ie_item->iE_ID %u\n", criticality_diagnostics_ie_item->iE_ID);

			criticality_diagnostics_ie_item->typeOfError = ENC_UINT_FLD_OBJ (tmITP, "TypeOfError", ENC_STRUCT_FIELD_PTR (IEsCriticalityDiagnostics_Item, 3));
			// tmLog ("criticality_diagnostics_ie_item->typeOfError %u\n", criticality_diagnostics_ie_item->typeOfError);

			criticality_diagnostics_ie_item->m.iE_ExtensionsPresent = 0;
			// tmLog ("criticality_diagnostics_ie_item->m.iE_ExtensionsPresent %u\n", criticality_diagnostics_ie_item->m.iE_ExtensionsPresent);
			criticality_diagnostics_ie_item->extElem1.count = 0;
			// tmLog ("criticality_diagnostics_ie_item->extElem1.count %u\n", criticality_diagnostics_ie_item->extElem1.count);
			ENC_STOP_STRUCT_OBJ (IEsCriticalityDiagnostics_Item);

			ASN1_LIST_APPEND (&ctxt, &p_pdu->iEsCriticalityDiagnostics, criticality_diagnostics_ie_item);
		}
		ENC_STOP_LIST_OBJ (IEsCriticalityDiagnostics);
	}
	else
	{
		p_pdu->m.iEsCriticalityDiagnosticsPresent = 0;
		// tmLog ("p_pdu->m.iEsCriticalityDiagnosticsPresent %u\n", p_pdu->m.iEsCriticalityDiagnosticsPresent);
	}

	p_pdu->m.iE_ExtensionsPresent = 0;
	// tmLog ("p_pdu->m.iE_ExtensionsPresent %u\n", p_pdu->m.iE_ExtensionsPresent);
	p_pdu->extElem1.count = 0;
	// tmLog ("p_pdu->extElem1.count %u\n", p_pdu->extElem1.count);

	ENC_STOP_STRUCT_OBJ (Criticality_Diagnostics);

	// Call ASN1 encoding function
    stat = asn1PE_CriticalityDiagnostics( &ctxt, p_pdu );
    CHECK_ENCODING( stat, ctxt )

	// Get length
    len += pu_getMsgLen (&ctxt);

	// Build ProtocolIE_Field
	ASN1_ALLOC( p_IEfield, p_ctxt, sizeof(ProtocolIE_Field) )

    p_IEfield->id              = IE_ID;
    p_IEfield->criticality     = criticality;
    p_IEfield->value.numocts   = len;
    p_IEfield->value.data      = buf;

	// Append IE to list
	ASN1_LIST_APPEND( p_ctxt, p_list, p_IEfield );

	// Free allocated memory
	ASN1_FREE( ctxt )

#undef IE_NAME
#undef IE_ID

	return ASN_OK;
}

int encHNBAP_BackoffTimer (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality)
{
#define IE_NAME			BackoffTimer
#define IE_ID			ASN1V_id_BackoffTimer

	OSCTXT                    ctxt;
	OSOCTET                   *buf;
    OSBOOL                    aligned = TRUE;
    IE_NAME                     *p_pdu;
    ProtocolIE_Field            *p_IEfield;
    int                         len = 0;
    int                         stat;


	// Initialize context
	ASN1_INIT_CTXT( ctxt )

	// Define buffer for encoded message
	ASN1_ALLOC( buf, p_ctxt, defsPduMAX_SIZE_IE)
	ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_IE, aligned )

	// Fill IE data structure
	ASN1_ALLOC( p_pdu, &ctxt, sizeof(IE_NAME) )

	*p_pdu = ENC_UINT_FLD_OBJ (tmITP, "BackoffTimer", p_obj);


	// Call ASN1 encoding function
   	stat = asn1PE_BackoffTimer( &ctxt, *p_pdu );
	CHECK_ENCODING( stat, ctxt )

	// Get length
   	len += pu_getMsgLen (&ctxt);

	// Build ProtocolIE_Field
	ASN1_ALLOC( p_IEfield, p_ctxt, sizeof(ProtocolIE_Field) )

    p_IEfield->id              = IE_ID;
    p_IEfield->criticality     = criticality;
    p_IEfield->value.numocts   = len;
    p_IEfield->value.data      = buf;

	// Append IE to list
	ASN1_LIST_APPEND( p_ctxt, p_list, p_IEfield );

	// Free allocated memory
	ASN1_FREE( ctxt )

#undef IE_NAME
#undef IE_ID

    return ASN_OK;
}

int encHNBAP_Registration_Cause (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality)
{
#define IE_NAME			Registration_Cause
#define IE_ID			ASN1V_id_Registration_Cause

	OSCTXT                    ctxt;
	OSOCTET                   *buf;
    OSBOOL                    aligned = TRUE;
    IE_NAME                     *p_pdu;
    ProtocolIE_Field            *p_IEfield;
    int                         len = 0;
    int                         stat;


	// Initialize context
	ASN1_INIT_CTXT( ctxt )

	// Define buffer for encoded message
	ASN1_ALLOC( buf, p_ctxt, defsPduMAX_SIZE_IE)
	ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_IE, aligned )

	// Fill IE data structure
	ASN1_ALLOC( p_pdu, &ctxt, sizeof(IE_NAME) )

	*p_pdu = ENC_UINT_FLD_OBJ (tmITP, "RegCause", p_obj);


	// Call ASN1 encoding function
   	stat = asn1PE_Registration_Cause( &ctxt, *p_pdu );
	CHECK_ENCODING( stat, ctxt )

	// Get length
   	len += pu_getMsgLen (&ctxt);

	// Build ProtocolIE_Field
	ASN1_ALLOC( p_IEfield, p_ctxt, sizeof(ProtocolIE_Field) )

    p_IEfield->id              = IE_ID;
    p_IEfield->criticality     = criticality;
    p_IEfield->value.numocts   = len;
    p_IEfield->value.data      = buf;

	// Append IE to list
	ASN1_LIST_APPEND( p_ctxt, p_list, p_IEfield );

	// Free allocated memory
	ASN1_FREE( ctxt )

#undef IE_NAME
#undef IE_ID

    return ASN_OK;
}

int encHNBAP_UE_Identity (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality)
{
#define IE_NAME			UE_Identity
#define IE_ID			ASN1V_id_UE_Identity

	OSCTXT                    ctxt;
	OSOCTET                   *buf;
    OSBOOL                    aligned = TRUE;
    IE_NAME                     *p_pdu;
    ProtocolIE_Field            *p_IEfield;
    int                         len = 0;
    int                         stat;


	// Initialize context
	ASN1_INIT_CTXT( ctxt )

	// Define buffer for encoded message
	ASN1_ALLOC( buf, p_ctxt, defsPduMAX_SIZE_IE)
	ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_IE, aligned )

	// Fill IE data structure
	ASN1_ALLOC( p_pdu, &ctxt, sizeof(IE_NAME) )

    ENC_START_STRUCT_OBJ (tmITP, p_obj, UE_Identity);
	p_pdu->t = ENC_INT_FLD_OBJ (tmITP, "Tag", ENC_STRUCT_FIELD_PTR (UE_Identity, 1));
	// tmLog ("p_pdu->t %u\n", p_pdu->t);
	switch (p_pdu->t)
	{
		case T_UE_Identity_iMSI:
			ASN1_ALLOC (p_pdu->u.iMSI, &ctxt, sizeof (IMSI));
			p_pdu->u.iMSI->numocts = ENC_HEX_FLD_OBJ (tmITP, "IMSI", p_pdu->u.iMSI->data, ENC_STRUCT_FIELD_PTR (UE_Identity, 2));
			break;
		case T_UE_Identity_tMSILAI:
			ENC_START_STRUCT_OBJ (tmITP, ENC_STRUCT_FIELD_PTR (UE_Identity, 2), TMSILAI);
			ASN1_ALLOC (p_pdu->u.tMSILAI, &ctxt, sizeof (TMSILAI));
			p_pdu->u.tMSILAI->tMSI.numbits = 32;
			ENC_HEX_FLD_OBJ (tmITP, "TMSI", p_pdu->u.tMSILAI->tMSI.data, ENC_STRUCT_FIELD_PTR (TMSILAI, 1));
			p_pdu->u.tMSILAI->lAI.pLMNID.numocts = 3;
			ENC_HEX_FLD_OBJ (tmITP, "PlmnId", p_pdu->u.tMSILAI->lAI.pLMNID.data, ENC_STRUCT_FIELD_PTR (TMSILAI, 2));
			p_pdu->u.tMSILAI->lAI.lAC.numocts = 2;
			ENC_HEX_FLD_OBJ (tmITP, "LAC", p_pdu->u.tMSILAI->lAI.lAC.data, ENC_STRUCT_FIELD_PTR (TMSILAI, 3));
			p_pdu->u.tMSILAI->lAI.extElem1.count  = 0;
			ENC_STOP_STRUCT_OBJ (TMSILAI);
		   break;
		case T_UE_Identity_pTMSIRAI:
			ENC_START_STRUCT_OBJ (tmITP, ENC_STRUCT_FIELD_PTR (UE_Identity, 2), PTMSIRAI);
			ASN1_ALLOC (p_pdu->u.pTMSIRAI, &ctxt, sizeof (PTMSIRAI));
			p_pdu->u.pTMSIRAI->pTMSI.numbits = 32;
			ENC_HEX_FLD_OBJ (tmITP, "PTMSI", p_pdu->u.pTMSIRAI->pTMSI.data, ENC_STRUCT_FIELD_PTR (PTMSIRAI, 1));
			p_pdu->u.pTMSIRAI->rAI.lAI.pLMNID.numocts = 3;
			ENC_HEX_FLD_OBJ (tmITP, "PlmnId", p_pdu->u.pTMSIRAI->rAI.lAI.pLMNID.data, ENC_STRUCT_FIELD_PTR (PTMSIRAI, 2));
			p_pdu->u.pTMSIRAI->rAI.lAI.lAC.numocts = 2;
			ENC_HEX_FLD_OBJ (tmITP, "LAC", p_pdu->u.pTMSIRAI->rAI.lAI.lAC.data, ENC_STRUCT_FIELD_PTR (PTMSIRAI, 3));
			p_pdu->u.pTMSIRAI->rAI.rAC.numocts = 1;
			ENC_HEX_FLD_OBJ (tmITP, "RAC", p_pdu->u.pTMSIRAI->rAI.rAC.data, ENC_STRUCT_FIELD_PTR (PTMSIRAI, 4));
			p_pdu->u.pTMSIRAI->extElem1.count  = 0;
			p_pdu->u.pTMSIRAI->rAI.extElem1.count = 0;
			//p_pdu->u.pTMSIRAI->rAI.m.iE_ExtensionsPresent = 0;
			ENC_STOP_STRUCT_OBJ (PTMSIRAI);
			break;
		case T_UE_Identity_iMEI:
			ASN1_ALLOC (p_pdu->u.iMEI, &ctxt, sizeof (IMEI));
			p_pdu->u.iMEI->numbits = 60;
			ENC_HEX_FLD_OBJ (tmITP, "IMEI", p_pdu->u.iMEI->data, ENC_STRUCT_FIELD_PTR (UE_Identity, 2));
			break;
		case T_UE_Identity_eSN:
			ASN1_ALLOC (p_pdu->u.eSN, &ctxt, sizeof (ESN));
			p_pdu->u.eSN->numbits = 32;
			ENC_HEX_FLD_OBJ (tmITP, "ESN", p_pdu->u.eSN->data, ENC_STRUCT_FIELD_PTR (UE_Identity, 2));
			break;
		case T_UE_Identity_iMSIDS41:
			ASN1_ALLOC (p_pdu->u.iMSIDS41, &ctxt, sizeof (IMSIDS41));
			p_pdu->u.iMSIDS41->numocts = ENC_HEX_FLD_OBJ (tmITP, "IMSIDS41", p_pdu->u.iMSIDS41->data, ENC_STRUCT_FIELD_PTR (UE_Identity, 2));
			break;
		case T_UE_Identity_iMSIESN:
			ENC_START_STRUCT_OBJ (tmITP, ENC_STRUCT_FIELD_PTR (UE_Identity, 2), IMSIESN);
			ASN1_ALLOC (p_pdu->u.iMSIESN, &ctxt, sizeof (IMSIESN));
			p_pdu->u.iMSIESN->iMSIDS41.numocts = ENC_HEX_FLD_OBJ (tmITP, "IMSIDS41", p_pdu->u.iMSIESN->iMSIDS41.data, ENC_STRUCT_FIELD_PTR (IMSIESN, 1));
			p_pdu->u.iMSIESN->eSN.numbits = 32;
			ENC_HEX_FLD_OBJ (tmITP, "ESN", p_pdu->u.iMSIESN->eSN.data, ENC_STRUCT_FIELD_PTR (IMSIESN, 2));
			ENC_STOP_STRUCT_OBJ (IMSIESN);
			break;
		case T_UE_Identity_tMSIDS41:
			ASN1_ALLOC (p_pdu->u.tMSIDS41, &ctxt, sizeof (TMSIDS41));
			p_pdu->u.tMSIDS41->numocts = ENC_HEX_FLD_OBJ (tmITP, "TMSIDS41", p_pdu->u.tMSIDS41->data, ENC_STRUCT_FIELD_PTR (UE_Identity, 2));
			break;
		default:
			tmAbort ("Invalid Tag %d", p_pdu->t);
	}

	ENC_STOP_STRUCT_OBJ (UE_Identity);


	// Call ASN1 encoding function
   	stat = asn1PE_UE_Identity( &ctxt, p_pdu );
	CHECK_ENCODING( stat, ctxt )

	// Get length
   	len += pu_getMsgLen (&ctxt);

	// Build ProtocolIE_Field
	ASN1_ALLOC( p_IEfield, p_ctxt, sizeof(ProtocolIE_Field) )

    p_IEfield->id              = IE_ID;
    p_IEfield->criticality     = criticality;
    p_IEfield->value.numocts   = len;
    p_IEfield->value.data      = buf;

	// Append IE to list
	ASN1_LIST_APPEND( p_ctxt, p_list, p_IEfield );

	// Free allocated memory
	ASN1_FREE( ctxt )

#undef IE_NAME
#undef IE_ID

    return ASN_OK;
}

int encHNBAP_UE_Capabilities (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality)
{
#define IE_NAME			UE_Capabilities
#define IE_ID			ASN1V_id_UE_Capabilities

	OSCTXT                    ctxt;
	OSOCTET                   *buf;
    OSBOOL                    aligned = TRUE;
    IE_NAME                     *p_pdu;
    ProtocolIE_Field            *p_IEfield;
    int                         len = 0;
    int                         stat;


	// Initialize context
	ASN1_INIT_CTXT( ctxt )

	// Define buffer for encoded message
	ASN1_ALLOC( buf, p_ctxt, defsPduMAX_SIZE_IE)
	ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_IE, aligned )

	// Fill IE data structure
	ASN1_ALLOC( p_pdu, &ctxt, sizeof(IE_NAME) )

    ENC_START_STRUCT_OBJ (tmITP, p_obj, UE_CAP);
    p_pdu->access_stratum_release_indicator = ENC_UINT_FLD_OBJ (tmITP, "AS_Rel_Indicator", ENC_STRUCT_FIELD_PTR(UE_CAP,1));
    p_pdu->csg_indicator = ENC_UINT_FLD_OBJ (tmITP, "CSG_Indicator", ENC_STRUCT_FIELD_PTR(UE_CAP,2));
	p_pdu->m.iE_ExtensionsPresent = 0;
	p_pdu->extElem1.count = 0;
    ENC_STOP_STRUCT_OBJ (UE_CAP);

	// Call ASN1 encoding function
   	stat = asn1PE_UE_Capabilities( &ctxt, p_pdu );
	CHECK_ENCODING( stat, ctxt )

	// Get length
   	len += pu_getMsgLen (&ctxt);

	// Build ProtocolIE_Field
	ASN1_ALLOC( p_IEfield, p_ctxt, sizeof(ProtocolIE_Field) )

    p_IEfield->id              = IE_ID;
    p_IEfield->criticality     = criticality;
    p_IEfield->value.numocts   = len;
    p_IEfield->value.data      = buf;

	// Append IE to list
	ASN1_LIST_APPEND( p_ctxt, p_list, p_IEfield );

	// Free allocated memory
	ASN1_FREE( ctxt )

#undef IE_NAME
#undef IE_ID

    return ASN_OK;
}

int encHNBAP_Context_ID (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality)
{
#define IE_NAME			Context_ID
#define IE_ID			ASN1V_id_Context_ID

	OSCTXT                    ctxt;
	OSOCTET                   *buf;
    OSBOOL                    aligned = TRUE;
    IE_NAME                     *p_pdu;
    ProtocolIE_Field            *p_IEfield;
    int                         len = 0;
    int                         stat;
    uint                        tmpuint;

	// Initialize context
	ASN1_INIT_CTXT( ctxt )

	// Define buffer for encoded message
	ASN1_ALLOC( buf, p_ctxt, defsPduMAX_SIZE_IE)
	ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_IE, aligned )

	// Fill IE data structure
	ASN1_ALLOC( p_pdu, &ctxt, sizeof(IE_NAME) )

	tmpuint = ENC_UINT_FLD_OBJ (tmITP, "ContextId", p_obj);
	// tmLog ("tmpuint %u\n", tmpuint);
	p_pdu->numbits = 24;
	l2b_int(tmpuint, p_pdu->data,p_pdu->numbits);
	/*
	(uint )*(p_pdu->data) = l2b_hnbap_int (tmpuint << 8);
*/
	// Call ASN1 encoding function
   	stat = asn1PE_Context_ID( &ctxt, p_pdu );
	CHECK_ENCODING( stat, ctxt )

	// Get length
   	len += pu_getMsgLen (&ctxt);

	// Build ProtocolIE_Field
	ASN1_ALLOC( p_IEfield, p_ctxt, sizeof(ProtocolIE_Field) )

    p_IEfield->id              = IE_ID;
    p_IEfield->criticality     = criticality;
    p_IEfield->value.numocts   = len;
    p_IEfield->value.data      = buf;

	// Append IE to list
	ASN1_LIST_APPEND( p_ctxt, p_list, p_IEfield );

	// Free allocated memory
	ASN1_FREE( ctxt )

#undef IE_NAME
#undef IE_ID

    return ASN_OK;
}


/*-----------------------------------------------------------------------------------------------*/

