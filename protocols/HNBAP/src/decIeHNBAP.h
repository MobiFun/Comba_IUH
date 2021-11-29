/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/HNBAP/tags/HNBAP-1.3.0/src/decIeHNBAP.h $
$Author: roger $
$Date: 2012-07-12 18:11:54 +0200 (Thu, 12 Jul 2012) $
$Rev: 53111 $
----------------------------------------------------------------*/

#ifndef decIeHNBAPINCLUDED
#define decIeHNBAPINCLUDED

#include <tcl.h>
#include "hnbapAsn1c.h"
#include "codecHNBAP.h"

/***********************************************************************
************************************************************************
                Decoding functions for HNBAP IEs
************************************************************************
*/
int decHNBAP_HNB_Identity (OSOCTET *buf, uint len, Tcl_Obj *p_obj);
int decHNBAP_PLMNidentity (OSOCTET *buf, uint len, Tcl_Obj *p_obj);
int decHNBAP_CellIdentity (OSOCTET *buf, uint len, Tcl_Obj *p_obj);
int decHNBAP_RAC (OSOCTET *buf, uint len, Tcl_Obj *p_obj);
int decHNBAP_LAC (OSOCTET *buf, uint len, Tcl_Obj *p_obj);
int decHNBAP_SAC (OSOCTET *buf, uint len, Tcl_Obj *p_obj);
int decHNBAP_MacroCoverageInfoStruct (Tcl_Obj *p_obj, MacroCoverageInformation *p_val);
int decHNBAP_CGIStruct (Tcl_Obj *p_obj, CGI *p_val);
int decHNBAP_UtranCellIDStruct (Tcl_Obj *p_obj, UTRANCellID *p_val);
int decHNBAP_GeographicalCoordinatesStruct (Tcl_Obj *p_obj, GeographicalLocation *p_val);
int decHNBAP_HNB_Location_Information (OSOCTET *buf, uint len, Tcl_Obj *p_obj);
int decHNBAP_CSG_ID (OSOCTET *buf, uint len, Tcl_Obj *p_obj);
int decHNBAP_RNC_ID (OSOCTET *buf, uint len, Tcl_Obj *p_obj);
int decHNBAP_Cause (OSOCTET *buf, uint len, Tcl_Obj *p_obj);
int decHNBAP_CriticalityDiagnostics  (OSOCTET *buf, uint len, Tcl_Obj *p_obj);
int decHNBAP_BackoffTimer (OSOCTET *buf, uint len, Tcl_Obj *p_obj);
int decHNBAP_Registration_Cause (OSOCTET *buf, uint len, Tcl_Obj *p_obj);
int decHNBAP_UE_Identity (OSOCTET *buf, uint len, Tcl_Obj *p_obj);
int decHNBAP_TMSILAIStruct (Tcl_Obj *p_obj, TMSILAI *p_val);
int decHNBAP_PTMSIRAIStruct (Tcl_Obj *p_obj, PTMSIRAI *p_val);
int decHNBAP_IMSIESNStruct (Tcl_Obj *p_obj, IMSIESN *p_val);
int decHNBAP_UE_Capabilities (OSOCTET *buf, uint len, Tcl_Obj *p_obj);
int decHNBAP_Context_ID (OSOCTET *buf, uint len, Tcl_Obj *p_obj);

#endif
