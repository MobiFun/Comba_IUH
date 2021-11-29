/*--------------------------------------------------------------
$URL: http://memo.prisma/svn/tm/scriptProt/HNBAP/tags/HNBAP-1.3.0/src/defs.h $
$Author: roger $
$Date: 2012-07-12 18:11:54 +0200 (Thu, 12 Jul 2012) $
$Rev: 53111 $
----------------------------------------------------------------
--------------------------------------------------------------*/

/*............................................................*/
#ifndef defsDEFINED
#define defsDEFINED

#include "hnbapAsn1c.h"

// the value of following 3 defines still has to be tuned with requirements of HNBAP
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


/***********************************************************
 * Number of IEs for each HNBAP message
 ***********************************************************/
#define	hnbapPduNIEs_HNB_REGISTER        8
#define	hnbapPduNIEs_HNB_REGISTERACC     1
#define	hnbapPduNIEs_HNB_REGISTERREJ     3
#define	hnbapPduNIEs_HNB_DEREGISTER      2
#define	hnbapPduNIEs_HNB_UEREGISTER      3
#define	hnbapPduNIEs_HNB_UEREGISTERACC   2
#define	hnbapPduNIEs_HNB_UEREGISTERREJ   3
#define	hnbapPduNIEs_HNB_UEDEREGISTER    2
#define	hnbapPduNIEs_HNB_ERRORINDICATION 2

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
