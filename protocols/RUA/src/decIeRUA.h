/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/RUA/tags/RUA-1.3.0/src/decIeRUA.h $
$Author: roger $
$Date: 2012-07-17 11:46:23 +0200 (Tue, 17 Jul 2012) $
$Rev: 53206 $
----------------------------------------------------------------*/

#ifndef decIeRUAINCLUDED
#define decIeRUAINCLUDED

#include <tcl.h>
#include "ruaAsn1c.h"
#include "codecRUA.h"

/***********************************************************************
************************************************************************
                Decoding functions for RUA IEs
************************************************************************
************************************************************************/

int decIeRUACNDomain(OSOCTET *buf, uint len, Tcl_Obj *p_obj);
int decIeRUAContextId(OSOCTET *buf, uint len, Tcl_Obj *p_obj);
int decIeRUAIntraDomNasNodeSel(OSOCTET *buf, uint len, Tcl_Obj *p_obj);
int decIeRUACause(OSOCTET *buf, uint len, Tcl_Obj *p_obj);
int decIeRUACriticalityDiagnostics(OSOCTET *buf, uint len, Tcl_Obj *p_obj);
int decIeRUAEstablishmentCause(OSOCTET *buf, uint len, Tcl_Obj *p_obj);
int decIeRUARanapMessage(OSOCTET *buf, uint len, Tcl_Obj *p_obj);

#endif
