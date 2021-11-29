/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/RUA/tags/RUA-1.3.0/src/encIeRUA.h $
$Author: roger $
$Date: 2012-07-17 11:46:23 +0200 (Tue, 17 Jul 2012) $
$Rev: 53206 $
----------------------------------------------------------------*/

#ifndef encIeRUAINCLUDED
#define encIeRUAINCLUDED

#include <tcl.h>
#include "ruaAsn1c.h"

/***********************************************************************
************************************************************************
                Encoding functions for RUA IEs
************************************************************************
************************************************************************/

int encIeRUACNDomain( Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality );
int encIeRUAContextId( Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality );
int encIeRUACause (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality);
int encIeRUACriticalityDiagnostics (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality);
int encIeRUAEstCause (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality);
int encIeRUARanapMessage (Tcl_Obj *p_obj, OSRTDList *p_list, OSCTXT *p_ctxt, uint criticality);

#endif
