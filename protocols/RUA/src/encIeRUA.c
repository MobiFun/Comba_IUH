/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/RUA/tags/RUA-1.3.0/src/encIeRUA.c $
$Author: roger $
$Date: 2012-07-27 15:55:43 +0200 (Fri, 27 Jul 2012) $
$Rev: 53538 $
----------------------------------------------------------------
Description : RUA SIGNALS ENCODING IEs
--------------------------------------------------------------*/

/*............................................................*/
/*  Include */
#include "encIeRUA.h"
#include "codecRUA.h"

/***********************************************************************
************************************************************************
                Encoding functions for RUA IEs
************************************************************************
************************************************************************/

/*-----------------------------------------------------------------------------------------------*/
int encIeRUACNDomain( Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality )
{
#define IE_NAME	RUA_CN_DomainIndicator // from RUA-IEs.h
#define IE_ID	ASN1V_RUA_id_CN_DomainIndicator //from RUA-Constants.h

	OSCTXT					ctxt;
	OSOCTET					*buf;
	OSBOOL					aligned = TRUE;
	IE_NAME					*p_pdu;
	RUA_ProtocolIE_Field	*p_IEfield;
	int						len = 0;
	int						stat;

	// Initialize context
	ASN1_INIT_CTXT( ctxt )

	// Define buffer for encoded message
	ASN1_ALLOC( buf, p_ctxt, defsPduMAX_SIZE_IE )
	ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_IE, aligned )

	// Fill IE data structure
	ASN1_ALLOC( p_pdu, &ctxt, sizeof(IE_NAME) )

	*p_pdu = ENC_UINT_FLD_OBJ (tmITP, "CnDomain", p_obj);
	tmLog ("CnDomain\t%u\n", *p_pdu); // debug

	// Call ASN1 encoding function
	stat = asn1PE_RUA_CN_DomainIndicator( &ctxt, *p_pdu ); // from RUA-IEsEnc.c
	CHECK_ENCODING( stat, ctxt )

	// Get length
	len += pu_getMsgLen (&ctxt);

	// Build ProtocolIE_Field
	ASN1_ALLOC( p_IEfield, p_ctxt, sizeof(RUA_ProtocolIE_Field) )

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
int encIeRUAContextId( Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality )
{
#define IE_NAME	RUA_Context_ID // from RUA-IEs.h
#define IE_ID	ASN1V_RUA_id_Context_ID //from RUA-Constants.h

	OSCTXT					ctxt;
	OSOCTET					*buf;
	OSBOOL					aligned = TRUE;
	IE_NAME					*p_pdu;
	RUA_ProtocolIE_Field	*p_IEfield;
	int						len = 0;
	int						stat;
	uint					tmpuint;

	// Initialize context
	ASN1_INIT_CTXT( ctxt )

	// Define buffer for encoded message
	ASN1_ALLOC( buf, p_ctxt, defsPduMAX_SIZE_IE )
	ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_IE, aligned )

	// Fill IE data structure
	ASN1_ALLOC( p_pdu, &ctxt, sizeof(IE_NAME) )

    p_pdu->numbits = 24;
    // tmLog ("p_pdu->numbits %u\n", p_pdu->numbits);
	tmpuint = ENC_UINT_FLD_OBJ (tmITP, "ContextId", p_obj);
    // tmLog ("tmpuint %u\n", tmpuint);
    //*(uint *)(p_pdu->data) = l2b_int(tmpuint << (32-p_pdu->numbits));
    l2b_int(tmpuint, p_pdu->data, p_pdu->numbits);
	/*
	int i;
	for(i = 0; i < 3; i++) {
    	tmLog ("p_pdu->data[%d] %d\n", p_pdu->data[i] );
	}

	tmLog ("ContextId\t%u\n", *p_pdu); // debug
	*/
	// Call ASN1 encoding function
	stat = asn1PE_RUA_Context_ID( &ctxt, p_pdu ); // from RUA-IEsEnc.c
	CHECK_ENCODING( stat, ctxt )

	// Get length
	len += pu_getMsgLen (&ctxt);

	// Build ProtocolIE_Field
	ASN1_ALLOC( p_IEfield, p_ctxt, sizeof(RUA_ProtocolIE_Field) )

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

int encIeRUACause (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality)
{
#define IE_NAME			RUA_Cause
#define IE_ID			ASN1V_RUA_id_Cause

	OSCTXT                    ctxt;
	OSOCTET                   *buf;
    OSBOOL                    aligned = TRUE;
    IE_NAME                     *p_pdu;
    RUA_ProtocolIE_Field            *p_IEfield;
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
	// tmLog ("p_pdu->t %u\n", p_pdu->t);
	switch (p_pdu->t)
    {
		case T_RUA_Cause_radioNetwork:
			p_pdu->u.radioNetwork = ENC_UINT_FLD_OBJ (tmITP, "Value", ENC_STRUCT_FIELD_PTR (Cause, 2));
			// tmLog ("p_pdu->u.radioNetwork %u\n", p_pdu->u.radioNetwork);
		   break;
		case T_RUA_Cause_transport:
			p_pdu->u.transport = ENC_UINT_FLD_OBJ (tmITP, "Value", ENC_STRUCT_FIELD_PTR (Cause, 2));
			// tmLog ("p_pdu->u.transport %u\n", p_pdu->u.transport);
		   break;
		case T_RUA_Cause_protocol:
			p_pdu->u.protocol = ENC_UINT_FLD_OBJ (tmITP, "Value", ENC_STRUCT_FIELD_PTR (Cause, 2));
			// tmLog ("p_pdu->u.protocol %u\n", p_pdu->u.protocol);
			break;
		case T_RUA_Cause_misc:
			p_pdu->u.misc = ENC_UINT_FLD_OBJ (tmITP, "Value", ENC_STRUCT_FIELD_PTR (Cause, 2));
			// tmLog ("p_pdu->u.misc %u\n", p_pdu->u.misc);
			break;
		case T_RUA_Cause_extElem1:
			p_pdu->u.extElem1->numocts = ENC_HEX_FLD_OBJ (tmITP, "extElem1", p_pdu->u.extElem1->data, ENC_STRUCT_FIELD_PTR (Cause, 2));
			break;
		default:
			tmAbort ("Invalid Tag %d", p_pdu->t);
    }

   	ENC_STOP_STRUCT_OBJ (Cause);

	// Call ASN1 encoding function
   	stat = asn1PE_RUA_Cause( &ctxt, p_pdu );
	CHECK_ENCODING( stat, ctxt )

	// Get length
   	len += pu_getMsgLen (&ctxt);

	// Build ProtocolIE_Field
	ASN1_ALLOC( p_IEfield, p_ctxt, sizeof(RUA_ProtocolIE_Field) )

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

int encIeRUACriticalityDiagnostics (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality)
{
#define IE_NAME         RUA_CriticalityDiagnostics
#define IE_ID           ASN1V_RUA_id_CriticalityDiagnostics

	OSCTXT                    ctxt;
    OSOCTET                   *buf;
    OSBOOL                    aligned = TRUE;
    IE_NAME                     *p_pdu;
    RUA_ProtocolIE_Field            *p_IEfield;
    int                         len = 0;
    int                         stat;
//	char						*tmpstring;
	uint						n, i;
	RUA_CriticalityDiagnostics_IE_List_element	*criticality_diagnostics_ie_item;


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
		// tmLog ("n %u\n", n);
		for (i = 0; i < n; i++)
		{
			ASN1_ALLOC (criticality_diagnostics_ie_item, &ctxt, sizeof (RUA_CriticalityDiagnostics_IE_List_element));
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
    stat = asn1PE_RUA_CriticalityDiagnostics( &ctxt, p_pdu );
    CHECK_ENCODING( stat, ctxt )

	// Get length
    len += pu_getMsgLen (&ctxt);

	// Build ProtocolIE_Field
	ASN1_ALLOC( p_IEfield, p_ctxt, sizeof(RUA_ProtocolIE_Field) )

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


int encIeRUAEstCause (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality)
{
#define IE_NAME			RUA_Establishment_Cause
#define IE_ID			ASN1V_RUA_id_Establishment_Cause

	OSCTXT                    ctxt;
	OSOCTET                   *buf;
    OSBOOL                    aligned = TRUE;
    IE_NAME                     *p_pdu;
    RUA_ProtocolIE_Field            *p_IEfield;
    int                         len = 0;
    int                         stat;


	// Initialize context
	ASN1_INIT_CTXT( ctxt )

	// Define buffer for encoded message
	ASN1_ALLOC( buf, p_ctxt, defsPduMAX_SIZE_IE)
	ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_IE, aligned )

	// Fill IE data structure
	ASN1_ALLOC( p_pdu, &ctxt, sizeof(IE_NAME) )

	*p_pdu = ENC_UINT_FLD_OBJ (tmITP, "EstablishCause", p_obj);


	// Call ASN1 encoding function
   	stat = asn1PE_RUA_Establishment_Cause( &ctxt, *p_pdu );
	CHECK_ENCODING( stat, ctxt )

	// Get length
   	len += pu_getMsgLen (&ctxt);

	// Build ProtocolIE_Field
	ASN1_ALLOC( p_IEfield, p_ctxt, sizeof(RUA_ProtocolIE_Field) )

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

int encIeRUARanapMessage (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality)
{
#define IE_NAME			RUA_RANAP_Message
#define IE_ID			ASN1V_RUA_id_RANAP_Message

	OSCTXT                    ctxt;
    OSOCTET                   *buf;
    OSBOOL                    aligned = TRUE;
    IE_NAME                     *p_pdu;
    RUA_ProtocolIE_Field            *p_IEfield;
    int                         len = 0;
    int                         stat;

	// Initialize context
	ASN1_INIT_CTXT( ctxt )

	// Define buffer for encoded message
	ASN1_ALLOC( buf, p_ctxt, defsPduMAX_SIZE_IE)
	ASN1_SET_BUFFER( ctxt, buf, defsPduMAX_SIZE_IE, aligned )

	// Fill IE data structure
	ASN1_ALLOC( p_pdu, &ctxt, sizeof(IE_NAME) )

	ASN1_ALLOC( p_pdu->data, &ctxt, defsPduMAX_SIZE_DATA );
	p_pdu->numocts = ENC_BINSTR_FLD_OBJ (tmITP, "RANAP_Message", (char *)p_pdu->data, p_obj);
	tmLog ("p_pdu->numocts %u\n", p_pdu->numocts);

	// Call ASN1 encoding function
    stat = asn1PE_RUA_RANAP_Message( &ctxt, *p_pdu );
	CHECK_ENCODING( stat, ctxt )

	// Get length
    len += pu_getMsgLen (&ctxt);

	// Build ProtocolIE_Field
	ASN1_ALLOC( p_IEfield, p_ctxt, sizeof(RUA_ProtocolIE_Field) )

    p_IEfield->id              = IE_ID;
    p_IEfield->criticality     = criticality;
    p_IEfield->value.numocts   = len;
    p_IEfield->value.data      = buf;

	ASN1_LIST_APPEND( p_ctxt, p_list, p_IEfield );

	// Free allocated memory
	ASN1_FREE( ctxt )

#undef IE_NAME
#undef IE_ID

	return ASN_OK;
}

