/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/RUA/tags/RUA-1.3.0/src/defs.h $
$Author: roger $
$Date: 2012-07-17 11:46:23 +0200 (Tue, 17 Jul 2012) $
$Rev: 53206 $
----------------------------------------------------------------
--------------------------------------------------------------*/

/*............................................................*/
#ifndef defsDEFINED
#define defsDEFINED

#include "ruaAsn1c.h"

// the value of following 3 defines still has to be tuned with requirements of RUA
#define defsPduMAX_SIZE_BUF		(16*1024)
#define defsPduMAX_SIZE_IE		(4*1024)
#define defsPduMAX_SIZE_DATA	32

/*	Macros	*/
#ifndef ASN_OK
#define ASN_OK 	0
#endif

// Encoding/Decoding macros
#define CHECK_ENCODING( ret_val, context )  \
    { if( ret_val != ASN_OK ) { printf("Encoding error...\n"); rtxErrPrint( &context ); rtFreeContext( &context ); return -1;} }

#define CHECK_DECODING( ret_val, context )  \
    { if( ret_val != ASN_OK ) { printf("Decoding error...\n"); rtxErrPrint( &context ); rtFreeContext( &context ); return -1;} }

#define ERR_ENC_MND(name)   \
    { printf( "\nError in encoding %s ???\n", #name ); return -1; }

#define ERR_DEC_MND(name)   \
    { printf( "\nError in decoding %s ???\n", #name ); return -1; }

//ASN1 related macros
#define ASN1_INIT_LIST(list_pointer)    \
{   \
    rtxDListInit(list_pointer);  \
}

#define ASN1_INIT_CTXT(context) {   \
    if( rtInitContext(&context) != ASN_OK ) \
        return -1;  \
}

#define ASN1_ALLOC(pointer, p_context, size)	\
{	\
	pointer = rtxMemAllocZ(p_context, size);	\
}

#define ASN1_SET_BUFFER(context, buffer, size, al)   \
{   \
    pu_setBuffer( &context, buffer, size, al);   \
}

#define ASN1_LIST_APPEND(p_context, list_pointer, value_pointer)	\
{	\
	rtxDListAppend( p_context, list_pointer, (void *)value_pointer );	\
}

#define ASN1_FREE(context) \
{   \
    rtFreeContext(&context);    \
}

#define ASN1_RETURN(context)	\
{	\
	ASN1_FREE(context)	\
	return -1;	\
}

#define	ruaPduNIEs_RUA_CONNECT                  6
#define	ruaPduNIEs_RUA_DIRECTTRANSFER           4
#define	ruaPduNIEs_RUA_DISCONNECT               5
#define	ruaPduNIEs_RUA_CONNECTIONLESSTRANSFER   2
#define	ruaPduNIEs_RUA_ERRORINDICATION          3

/***********************************************************
 * Basic type definitions
 ***********************************************************/

#undef   uchar
#undef   uint
#undef   ushort
#undef   ulong

#define  uchar      unsigned char
#define  uint       unsigned int
#define  ushort     unsigned short
#define  ulong      unsigned long long int

#endif	/*	defsDEFINED	*/
