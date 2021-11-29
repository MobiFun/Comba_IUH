/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/HNBAP/tags/HNBAP-1.3.0/src/encIeHNBAP.h $
$Author: roger $
$Date: 2012-07-12 18:11:54 +0200 (Thu, 12 Jul 2012) $
$Rev: 53111 $
----------------------------------------------------------------*/

#ifndef encIeHNBAPINCLUDED
#define encIeHNBAPINCLUDED

#include <tcl.h>
#include "hnbapAsn1c.h"
#include "defs.h"
/***********************************************************************
************************************************************************
                Encoding functions for HNBAP IEs
************************************************************************
************************************************************************/
int encHNBAP_Cause (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality);
int encHNBAP_HNB_Identity (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality);
int encHNBAP_PLMNidentity (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality);
int encHNBAP_CellIdentity (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality);
int encHNBAP_LAC (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality);
int encHNBAP_RAC (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality);
int encHNBAP_SAC (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality);
int encHNBAP_CSG_ID (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality);
int encHNBAP_HNB_Location_Information (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality);
int encHNBAP_MacroCoverageInformationStruct (Tcl_Obj *p_obj, MacroCoverageInformation *p_val, OSCTXT *p_ctxt);
int encHNBAP_GeographicalLocationStruct (Tcl_Obj *p_obj, GeographicalLocation *p_val, OSCTXT *p_ctxt);
int encHNBAP_RNC_ID (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality);
int encHNBAP_CriticalityDiagnostics (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality);
int encHNBAP_BackoffTimer (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality);
int encHNBAP_Registration_Cause (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality);
int encHNBAP_UE_Identity (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality);
int encHNBAP_UE_Capabilities (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality);
int encHNBAP_Context_ID (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality);

#endif
