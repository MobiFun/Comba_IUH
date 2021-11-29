/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/HNBAP/tags/HNBAP-1.3.0/src/decHNBAP.h $
$Author: roger $
$Date: 2012-07-12 18:11:54 +0200 (Thu, 12 Jul 2012) $
$Rev: 53111 $
--------------------------------------------------------------*/

#ifndef decHNBAPINCLUDED
#define decHNBAPINCLUDED

#include "hnbapAsn1c.h"

/***********************************************************************
************************************************************************
                Decoding functions for HNBAP PDUs
************************************************************************
************************************************************************/

int decHNBAPPdu( uint *t_proc, uint *t_code, uchar *buf_in, OSOCTET *buf_out, uint *len_out );

int decHNBAPRegister( OSOCTET *buf_in, uint len );

int decHNBAPHNBRegisterAccept( OSOCTET *buf_in, uint len );

int decHNBAPHNBRegisterReject( OSOCTET *buf_in, uint len );

int decHNBAPHNBDeRegister( OSOCTET *buf_in, uint len );

int decHNBAPUERegisterRequest( OSOCTET *buf_in, uint len );

int decHNBAPUERegisterAccept( OSOCTET *buf_in, uint len );

int decHNBAPUERegisterReject( OSOCTET *buf_in, uint len );

int decHNBAPUEDeRegister( OSOCTET *buf_in, uint len );

int decHNBAPErrorIndication( OSOCTET *buf_in, uint len );

int decHNBAPPrivateMessage( OSOCTET *buf_in, uint len );

#endif
