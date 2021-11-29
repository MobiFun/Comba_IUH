/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/HNBAP/tags/HNBAP-1.3.0/src/encHNBAP.h $
$Author: roger $
$Date: 2012-07-12 18:11:54 +0200 (Thu, 12 Jul 2012) $
$Rev: 53111 $
----------------------------------------------------------------
Description : HNBAP SIGNALS ENCODING
--------------------------------------------------------------*/

#ifndef encHNBAPINCLUDED
#define encHNBAPINCLUDED
#include "defs.h"


/***********************************************************************
************************************************************************
                Encoding functions for HNBAP PDUs
************************************************************************
************************************************************************/

int encHNBAPRegister( OSOCTET *buf_out, int *len );

int encHNBAPHNBRegisterAccept( OSOCTET *buf_out, int *len );

int encHNBAPHNBRegisterReject( OSOCTET *buf_out, int *len );

int encHNBAPHNBDeRegister( OSOCTET *buf_out, int *len );

int encHNBAPUERegisterRequest( OSOCTET *buf_out, int *len );

int encHNBAPUERegisterAccept( OSOCTET *buf_out, int *len );

int encHNBAPUERegisterReject( OSOCTET *buf_out, int *len );

int encHNBAPUEDeRegister( OSOCTET *buf_out, int *len );

int encHNBAPErrorIndication( OSOCTET *buf_out, int *len );

int encHNBAPPrivateMessage( OSOCTET *buf_out, int *len );

#endif
