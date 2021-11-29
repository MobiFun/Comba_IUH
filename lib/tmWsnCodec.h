/*********************************************************************
  Title: WSN<->C CODEC MACROS - tmWsnCodec.h
 ---------------------------------------------------------------------
  $URL: http://memo.prisma/svn/fw/fw-3/3.0.5/fwsrc/com/fwtstm/tmWsnCodec.h $

  $Author: roger $
  $Date: 2011-09-29 09:28:29 +0200 (Thu, 29 Sep 2011) $

  $Rev: 772 $
 *********************************************************************/


/*	IMPORTANT!! THIS IS NOT A PUBLIC HEADER
 *
 * 	This file contains macros which do not conform to Prisma LSU naming
 * 	conventions (it MUST be included only locally to .c modules).
 *
 * 	PLEASE USE THIS MACROS!!
 * 	If possible, use this macros: do not call directly the tmWsnEnc/Dec
 * 	functions nor re-implement functions that do the same job.
 */

#include "tmWsn.h"

#define ENCODER_PROTOTYPE(func) \
	static int func (msgBUFt* msg, uint sid, char* var)

#define DECODER_PROTOTYPE(func) \
	static int func (char* var, uint sid, uint src, msgBUFt* msg)

#define WBUF 	tmWsnBuf	/* buffer */
#define WFP  	tmWsnFp		/* array of pointers to field values */
#define WFSFP  	tmWsnFsFp	/* array of pointers to FLDSTR field values */

/************************************************************************
 *	ENCODING (WSN->C)													*
 ************************************************************************/

#define ENC_START(itp,var)	   			tmWsnEncStart(itp,var)
/* Inits WFP array with pointers to signal fields.
 * Returns no. of fields in signal.
 *
 * itp = the TCL interpreter
 * var = name of TCL variable containing signal
 *
 * Example:
 *
 * 	  set sig "HELLO 1 0xFF pippo ? a:5:???" ;# in itp
 *
 * 	  int nfields = ENC_START(itp,"sig");
 *
 *    nfields = 6;
 * 	  WFP[0] = "HELLO"	// signal type
 * 	  WFP[1] = "1"
 * 	  WFP[2] = "0xFF"
 * 	  WFP[3] = "pippo"
 * 	  WFP[4] = "?"
 * 	  WFP[5] = "a:5:???"
 */


#define ENC_INVALID_VALUE(fname,sname) \
	tmAbort("invalid %s field value in signal '%s'",fname,sname)

/* char* Xxx(int n,char* fname) */
#define ENC_STRING(n,fname) 			tmWsnEncStr(WFP[n],fname)
#define ENC_STRING_D(n,fname,defval) 	tmWsnEncStrDef(WFP[n],fname,defval)

/* int Xxx(int n, char* fname) */
#define ENC_INT(n,fname) 			tmWsnEncInt(WFP[n],fname)
#define ENC_INT_D(n,fname,defval) 	tmWsnEncIntDef(WFP[n],fname,defval)
#define ENC_UINT 					ENC_INT
#define ENC_UINT_D 					ENC_INT_D
#define ENC_BIT 					ENC_INT
#define ENC_BIT_D 					ENC_INT_D
#define ENC_CHAR 					ENC_INT
#define ENC_CHAR_D 					ENC_INT_D
#define ENC_UCHAR 					ENC_INT
#define ENC_UCHAR_D 				ENC_INT_D
#define ENC_SHORT 					ENC_INT
#define ENC_SHORT_D				 	ENC_INT_D
#define ENC_USHORT 					ENC_INT
#define ENC_USHORT_D			 	ENC_INT_D
#define ENC_LONG 					ENC_INT
#define ENC_LONG_D 					ENC_INT_D
#define ENC_ULONG 					ENC_INT
#define ENC_ULONG_D					ENC_INT_D

/* int Xxx(int n,char* fname, char* dst)
 * returns no. of bytes copied in dst.
 */
#define ENC_HEX(n,fname,dst) 	tmWsnEncHex(dst,WFP[n],fname)


#define ENC_STRVAL2(n,fname,str1,val1,str2,val2,dst) 						\
 	{ if(strcmp(WFP[n],str1)==0) dst = val1;								\
	else if(strcmp(WFP[n],str2)==0) dst = val2;								\
	else tmAbort("WSN invalid value %s for field '%s'",WFP[n],fname);	}

#define ENC_STRVAL2_D(n,fname,str1,val1,str2,val2,defval,dst) 				\
 	{ if(strcmp(WFP[n],str1)==0) dst = val1;								\
	else if(strcmp(WFP[n],str2)==0) dst = val2;								\
	else if(strcmp(WFP[n],"?")==0)  dst = defval;							\
	else tmAbort("WSN invalid value %s for field '%s'",WFP[n],fname);	}

/*----------------------------------------------------------------------*
 |	FLDSTR ENCODING		                    							|
 *----------------------------------------------------------------------*/
#define ENC_FS_START(n)		   			tmWsnEncFsStart(n)
/* Inits WFSFP array with pointers to subfields of field WFP[n].
 * Returns no. of subfield in signal.
 *
 * Example:
 *
 * 	  WFP[5] = "a:5:???" (see ENC_START example)
 *
 * 	  int nsubfields = ENC_FS_START(5));
 *
 *	  nsubfields = 3;
 * 	  WFSFP[0] = "a"
 * 	  WFSFP[1] = "5"
 * 	  WFSFP[2] = "???"
 */

#define ENC_FS_INT(n,fname) 			tmWsnEncInt(WFSFP[n],fname)
#define ENC_FS_INT_D(n,fname,defval) 	tmWsnEncIntDef(WFSFP[n],fname,defval)
#define ENC_FS_BIT(n,fname) 			tmWsnEncInt(WFSFP[n],fname)
#define ENC_FS_BIT_D(n,fname,defval) 	tmWsnEncIntDef(WFSFP[n],fname,defval)
#define ENC_FS_UINT(n,fname) 			tmWsnEncInt(WFSFP[n],fname)
#define ENC_FS_UINT_D(n,fname,defval)	tmWsnEncIntDef(WFSFP[n],fname,defval)
#define ENC_FS_CHAR(n,fname) 			tmWsnEncInt(WFSFP[n],fname)
#define ENC_FS_CHAR_D(n,fname,defval) 	tmWsnEncIntDef(WFSFP[n],fname,defval)
#define ENC_FS_UCHAR(n,fname) 			tmWsnEncInt(WFSFP[n],fname)
#define ENC_FS_UCHAR_D(n,fname,defval) 	tmWsnEncIntDef(WFSFP[n],fname,defval)
#define ENC_FS_SHORT(n,fname) 			tmWsnEncInt(WFSFP[n],fname)
#define ENC_FS_SHORT_D(n,fname,defval) 	tmWsnEncIntDef(WFSFP[n],fname,defval)
#define ENC_FS_USHORT(n,fname) 			tmWsnEncInt(WFSFP[n],fname)
#define ENC_FS_USHORT_D(n,fname,defval)	tmWsnEncIntDef(WFSFP[n],fname,defval)
#define ENC_FS_LONG(n,fname) 			tmWsnEncInt(WFSFP[n],fname)
#define ENC_FS_LONG_D(n,fname,defval) 	tmWsnEncIntDef(WFSFP[n],fname,defval)
#define ENC_FS_ULONG(n,fname) 			tmWsnEncInt(WFSFP[n],fname)
#define ENC_FS_ULONG_D(n,fname,defval) 	tmWsnEncIntDef(WFSFP[n],fname,defval)
#define ENC_FS_STRING(n,fname) 			tmWsnEncStr(WFSFP[n],fname)
#define ENC_FS_STRING_D(n,fname,defval)	tmWsnEncStrDef(WFSFP[n],fname,defval)
#define ENC_FS_HEX(n,fname,dst) 		tmWsnEncHex(dst,WFSFP[n],fname)

#define ENC_FS_STRVAL2(n,fname,str1,val1,str2,val2,dst) 		\
 	{															\
	if(strcmp(WFSFP[n],str1)==0) dst = val1;					\
	else if(strcmp(WFSFP[n],str2)==0) dst = val2;				\
	else tmAbort("(WSN) invalid value %s for subfield '%s'",WFSFP[n],fname);\
	}

#define ENC_FS_STRVAL2_D(n,fname,str1,val1,str2,val2,defval,dst) 	\
 	{																\
	if(strcmp(WFSFP[n],str1)==0) dst = val1;						\
	else if(strcmp(WFSFP[n],str2)==0) dst = val2;					\
	else if(strcmp(WFSFP[n],"?")==0)  dst = defval;					\
	else tmAbort("(WSN) invalid value %s for subfield '%s'",WFSFP[n],fname);\
	}


/************************************************************************
 *	ENCODING (WSN->C) Object version									*
 *	Common parameters meaning:
 *	itp: tmITPt* (pointer to the current TCL interpreter)
 *	n: uint (position of a field in the signal) The value start from 1. 0 is the position of the signal name.
 *	fname: char* (optional string with the field name)
 *	defval: default value in case the field is = "?". The
 *	type il related to the type of the field
 ************************************************************************/

/* Returns no. of fields in signal, included the signal name */
#define ENC_START_OBJ(itp,var) 				tmWsnEncStartObj(itp,var)

/* Returns the string pointer */
#define ENC_STRING_OBJ(itp,n,fname) 		tmWsnEncStrObj(n,fname)
#define ENC_STRING_D_OBJ(itp,n,fname,defval) 	tmWsnEncStrDefObj(n,defval)

#define ENC_BOOL_OBJ(itp,n,fname)           tmWsnEncBoolObj(itp,n,fname)
#define ENC_INT_OBJ(itp,n,fname) 			tmWsnEncIntObj(itp,n,fname)
#define ENC_INT_D_OBJ(itp,n,fname,defval) 	tmWsnEncIntDefObj(itp,n,fname,defval)
#define ENC_UINT_OBJ 						ENC_INT_OBJ
#define ENC_UINT_D_OBJ 						ENC_INT_D_OBJ
#define ENC_LONGLONG_OBJ(itp,n,fname)		tmWsnEncLongLongObj(itp,n,fname)
#define ENC_LONGLONG_D_OBJ(itp,n,fname,defval)		tmWsnEncLongLongDefObj(itp,n,fname,defval)
#define ENC_ULONGLONG_OBJ					ENC_LONGLONG_OBJ
#define ENC_ULONGLONG_D_OBJ(itp,n,fname,defval)		ENC_LONGLONG_D_OBJ
#define ENC_BIT_OBJ 						ENC_INT_OBJ
#define ENC_BIT_D_OBJ 						ENC_INT_D_OBJ
#define ENC_CHAR_OBJ 						ENC_INT_OBJ
#define ENC_CHAR_D_OBJ 						ENC_INT_D_OBJ
#define ENC_UCHAR_OBJ 						ENC_INT_OBJ
#define ENC_UCHAR_D_OBJ 					ENC_INT_D_OBJ
#define ENC_SHORT_OBJ 						ENC_INT_OBJ
#define ENC_SHORT_D_OBJ					 	ENC_INT_D_OBJ
#define ENC_USHORT_OBJ 						ENC_INT_OBJ
#define ENC_USHORT_D_OBJ				 	ENC_INT_D_OBJ
#define ENC_LONG_OBJ 						ENC_INT_OBJ
#define ENC_LONG_D_OBJ 						ENC_INT_D_OBJ
#define ENC_ULONG_OBJ 						ENC_INT_OBJ
#define ENC_ULONG_D_OBJ						ENC_INT_D_OBJ

/*these macros *_O_* set value pointed by dst and return dst value if field != ?,
 * otherwise return NULL */
/*tmITPt* itp, uint n, char* fname, char* dst*/
#define ENC_CHAR_O_OBJ(itp,n,fname,dst) 	tmWsnEncCharOptObj(itp,n,fname,dst)
#define ENC_UCHAR_O_OBJ(itp,n,fname,dst) 	ENC_CHAR_O_OBJ(itp,n,fname,((char *)(dst)))

/*tmITPt* itp, uint n, char* fname, short* dst*/
#define ENC_SHORT_O_OBJ(itp,n,fname,dst) 	tmWsnEncShortOptObj(itp,n,fname,dst)
#define ENC_USHORT_O_OBJ(itp,n,fname,dst) 	ENC_SHORT_O_OBJ(itp,n,fname,((short *)(dst)))

/*tmITPt* itp, uint n, char* fname, int* dst*/
#define ENC_INT_O_OBJ(itp,n,fname,dst) 		tmWsnEncIntOptObj(itp,n,fname,dst)
#define ENC_UINT_O_OBJ(itp,n,fname,dst)		ENC_INT_O_OBJ(itp,n,fname,((int *)(dst)))
/*
#define ENC_LONG_O_OBJ(itp,n,fname,dst) 	tmWsnEncLongOptObj(itp,n,fname,dst)
#define ENC_ULONG_O_OBJ(itp,n,fname,dst)	ENC_LONG_O_OBJ*/

/* returns no. of bytes copied in dst, 0 if signal field = "?" */
#define ENC_HEX_OBJ(itp,n,fname,dst) 		tmWsnEncHexObj(dst,n,fname)

/* BINSTR is a binary string as returned by TCL command "binary format" */
/* returns int value: no. of bytes copied in dst */
/*There isn't a default value for empty field as "?"*/
#define ENC_BINSTR_OBJ(itp,n,fname,dst)		tmWsnEncBinStrObj(dst,n,fname)


/***** LIST HANDLING for a field that is a list *****/

/* itp: tmITPt*
 *
 * nel: uint. It is set by the macro to the number of elements of the list
 *
 * listPtr: Tcl_Obj *. For this parameter you have to use one of the following
 * macros:
 * ENC_SIG_FIELD_PTR, ENC_LIST_FIELD_PTR, ENC_STRUCT_FIELD_PTR
 * If, for example, the list is the 2nd field of a signal,
 * use ENC_SIG_FIELD_PTR(2);
 * if it is the 2nd field of a list (list inside a list),
 * use ENC_LIST_FIELD_PTR(IncludingListId, 1);
 * if, for example, the list is the 2nd field of a structure,
 * use ENC_STRUCT_FIELD_PTR(IncludingStrId, 2).
 *
 * listId: it is a string used by the macro to compose the name of a variable.
 * This name needs to be unique in case of a multi-level list, that is
 * if a list contains another list, they need to have different listIds */

/* Example for a LIST of UINT, that is the third field of a signal */
/*
	uint nListElem;

	ENC_START_LIST_OBJ(tmITP,nListElem,ENC_SIG_FIELD_PTR(3),ChanList);

	for( i=0; i<nListElem; i++ )
	{

		strPtr->chan = ENC_UINT_FLD_OBJ( tmITP, "Chan", ENC_LIST_FIELD_PTR(ChanList,i) );

	}
	ENC_STOP_LIST_OBJ(ChanList);
*/

/* Example for a LIST of STRUCTs */
/*
	uint nListElem;

	ENC_START_LIST_OBJ(tmITP,nListElem,ENC_SIG_FIELD_PTR(3),ChanList);

	for( i=0; i<nListElem; i++ )
	{
		ENC_START_STRUCT_OBJ( tmITP, ENC_LIST_FIELD_PTR(ChanList,i) , chanStr );

		strPtr->chan = ENC_USHORT_FLD_OBJ( tmITP, "Chan", ENC_STRUCT_FIELD_PTR(chanStr,1) );
		strPtr->ts = ENC_UCHAR_FLD_OBJ( tmITP, "Ts", ENC_STRUCT_FIELD_PTR(chanStr,2) );

		ENC_STOP_STRUCT_OBJ( chanStr );
	}
	ENC_STOP_LIST_OBJ(ChanList);
*/

#define ENC_START_LIST_OBJ(itp,nel,listPtr,listId) 		\
	do {Tcl_Obj **ListPtr##listId; nel = tmWsnEncStartListObj(itp,listPtr,&ListPtr##listId)

#define ENC_STOP_LIST_OBJ(listId) 			} while(0)

/***** STRUCT HANDLING for a field that is a struct *****/
#define ENC_START_STRUCT_OBJ(itp,listPtr,strId) 		\
	do {Tcl_Obj **StrPtr##strId; \
		tmWsnEncStartListObj(itp,listPtr,&StrPtr##strId)

#define ENC_STOP_STRUCT_OBJ(strId) 		} while(0)

/***** FIELD ENCODING for a field of a struct or a list *****/
#define ENC_SIG_FIELD_PTR(n) EncSigPtr[n]
#define ENC_LIST_FIELD_PTR(listId,n) ListPtr##listId[n]
#define ENC_STRUCT_FIELD_PTR(strId,n) StrPtr##strId[n]
#define ENC_STRUCT_PTR(strId) StrPtr##strId
/*N.B. Struct and signal fields start from 1. On the contrary, list fields start from 0*/
/*In fact a struct contains in the 0th place the Struct type name and the signal contains the signal name*/

/* Check if a field is present. Tipically used for a field which
 * is themself a structure.
 * Return value 0 for false and 1 for true. */
/* fld: field ptr (Tcl_Obj *) as returned for example by macro
 * ENC_SIG_FIELD_PTR, etc. */
#define FIELD_PRES_OBJ(fname,fld) \
	tmWsnStructFieldPresObj(fld)

#define STRUCT_FIELD_PRES_OBJ(fname,fld) \
	FIELD_PRES_OBJ(fname,fld)

/*MONDATORY FIELDS*/
/*N.B. List fields start from 0, on the contrary, Struct fields from 1*/
/*tmITPt* itp, char* fname, char* dst, Tcl_Obj* fld*/
/* Parameters:
 * itp: TCL interpeter
 * fname: field name (only for debug purpose)
 * dst: destination for encoded value
 * fld: pointer to the TCL object representing the field
*/
/*example of use:
 *ENC_UINT_FLD_OBJ(itp, "FieldName", ENC_STRUCT_FIELD_PTR(Str1, 3))
 * */
#define ENC_ULONGLONG_FLD_OBJ(itp,fname,fld) \
	tmWsnEncLongLongListObj(itp,fname,fld)

#define ENC_UINT_FLD_OBJ(itp,fname,fld) \
	tmWsnEncIntListObj(itp,fname,fld)
#define ENC_UINT_FLD_D_OBJ(itp,fname,fld,defval) \
	tmWsnEncIntListDefObj(itp,fname,fld,defval)

#define ENC_LONGLONG_FLD_OBJ(itp,fname,fld) \
	ENC_ULONGLONG_FLD_OBJ(itp,fname,fld)

#define ENC_INT_FLD_OBJ(itp,fname,fld) \
	ENC_UINT_FLD_OBJ(itp,fname,fld)

#define ENC_USHORT_FLD_OBJ(itp,fname,fld) \
	ENC_UINT_FLD_OBJ(itp,fname,fld)
#define ENC_USHORT_FLD_D_OBJ(itp,fname,fld,defval) \
	ENC_UINT_FLD_D_OBJ(itp,fname,fld,defval)

#define ENC_SHORT_FLD_OBJ(itp,fname,fld) \
	ENC_UINT_FLD_OBJ(itp,fname,fld)

#define ENC_UCHAR_FLD_OBJ(itp,fname,fld) \
	ENC_UINT_FLD_OBJ(itp,fname,fld)
#define ENC_UCHAR_FLD_D_OBJ(itp,fname,fld,defval) \
	ENC_UINT_FLD_D_OBJ(itp,fname,fld,defval)

#define ENC_CHAR_FLD_OBJ(itp,fname,fld) \
	ENC_UINT_FLD_OBJ(itp,fname,fld)

#define ENC_BOOL_FLD_OBJ(itp,fname,fld) \
	tmWsnEncBoolListObj (itp,fname,fld)

/* returns no. of bytes copied in dst */
/*There isn't a default value for empty field as "?"*/
#define ENC_BINSTR_FLD_OBJ(itp,fname,dst,fld)	\
	tmWsnEncBinStrListObj(dst,fname,fld)

/* Returns the string pointer */
#define ENC_STRING_FLD_OBJ(itp,fname,fld)	\
	tmWsnEncStrListObj(fname,fld)

/*OPTIONAL FIELDS*/

// Return number of octets that are represented by the HEXSTR.
// It is the same value that should be returned calling ENC_HEX_FLD_OBJ.
#define HEX_FLD_LEN_OBJ(fld) 	\
	tmWsnHexFldLenListObj(fld)

/*these macros *_O_* set value pointed by dst and return dst value if field != ?,
 * otherwise return NULL */
/* Parameters:
 * itp: TCL interpeter
 * fname: field name (only for debug purpose)
 * dst: destination for encoded value
 * fld: pointer to the TCL object representing the field
 */
/*example of use:
 *ENC_HEX_FLD_OBJ(itp, "FieldName", dst, ENC_STRUCT_FIELD_PTR(Str1, 3))
 * */
/*tmITPt* itp, char* fname, char* dst, Tcl_Obj* fld*/
/* returns no. of bytes copied in dst, 0 if signal field = "?" */
#define ENC_HEX_FLD_OBJ(itp,fname,dst,fld) 	\
	tmWsnEncHexListObj(dst,fld)

/*tmITPt* itp, char* fname, char* dst, Tcl_Obj* fld*/
#define ENC_CHAR_O_STRUCT_OBJ(itp,fname,dst,fld)	\
	tmWsnEncCharOptListObj(itp,fname,dst,fld)
/*tmITPt* itp, char* fname, uchar* dst, Tcl_Obj* fld*/
#define ENC_UCHAR_O_STRUCT_OBJ(itp,fname,dst,fld)	\
	ENC_CHAR_O_STRUCT_OBJ(itp,fname,((char *)(dst)),fld)

/*tmITPt* itp, char* fname, short* dst, Tcl_Obj* fld*/
#define ENC_SHORT_O_STRUCT_OBJ(itp,fname,dst,fld)	\
	tmWsnEncShortOptListObj(itp,fname,dst,fld)
/*tmITPt* itp, char* fname, ushort* dst, Tcl_Obj* fld*/
#define ENC_USHORT_O_STRUCT_OBJ(itp,fname,dst,fld)	\
	ENC_SHORT_O_STRUCT_OBJ(itp,fname,((short *)(dst)),fld)

/*tmITPt* itp, char* fname, int* dst, Tcl_Obj* fld*/
#define ENC_INT_O_STRUCT_OBJ(itp,fname,dst,fld)		\
	tmWsnEncIntOptListObj(itp,fname,dst,fld)
/*tmITPt* itp, char* fname, uint* dst, Tcl_Obj* fld*/
#define ENC_UINT_O_STRUCT_OBJ(itp,fname,dst,fld)	\
	ENC_INT_O_STRUCT_OBJ(itp,fname,((int *)(dst)),fld)

/* Returns the string pointer */
#define ENC_STRING_O_STRUCT_OBJ(itp,fname,fld)	\
	Tcl_GetString(fld)

/************************************************************************
 * 	  DECODING (C->WSN)                       							*
 ************************************************************************/

#define DEC_START()			tmWsnDecStart()
/* Reset WBUF */

#define DEC_SET_VAR(itp,var)	tmTclSet(itp,var,WBUF)
/* Set variable in TCL interpreter with contents of WBUF */

#define DEC_NOTPRESENT() 	tmWsnDecStr("?")

#define DEC_TYPE(sid)		tmWsnDecStr(tmSidTag(sid))
/* void Xxx(char* fval); */
#define DEC_STRING 			tmWsnDecStr
/* void Xxx(char* fmat,...); */
#define DEC_STRINGF			tmWsnDecStrf

/* void Xxx(char* p, int len); */
#define DEC_HEX(p,len) 	tmWsnDecHex((char*)(p),len)

#define DEC_FLAG(fval,val0,valX) 								 \
	{ (fval==0) ? tmWsnDecStr(val0) : tmWsnDecStr(valX); }

#define DEC_FLAG_OPT(fval,val0,valX) 							 \
	{ if uuInvalid(fval) tmWsnDecStr("?");						 \
	else { (fval==0) ? tmWsnDecStr(val0) : tmWsnDecStr(valX); }  }

#define DEC_STRVAL2(fval,val1,str1,val2,str2)			\
	{ if(fval==val1) tmWsnDecStr(str1);					\
	else if(fval==val2) tmWsnDecStr(str2);				\
	else tmWsnDecStr("?");	}

#define DEC_BIT(fval) 									\
	{ ((fval)==0) ? tmWsnDecStr("0") : tmWsnDecStr("1"); }

#define DEC_BIT_OPT(fval) 										\
	{ if uuInvalid(fval) tmWsnDecStr("?");						\
	else { ((fval)==0) ? tmWsnDecStr("0") : tmWsnDecStr("1"); } }


#define DEC_CHAR 			tmWsnDecChar

#define DEC_CHAR_OPT(fval) 							\
	{ uuInvalid(fval) ? tmWsnDecStr("?") : tmWsnDecChar(fval); }

#define DEC_UCHAR 			tmWsnDecUchar
#define DEC_UCHARX 			tmWsnDecUcharx

#define DEC_UCHAR_OPT(fval) 							\
	{ uuInvalid(fval) ? tmWsnDecStr("?") : tmWsnDecUchar(fval); }
#define DEC_UCHARX_OPT(fval) 							\
	{ uuInvalid(fval) ? tmWsnDecStr("?") : tmWsnDecUcharx(fval); }

#define DEC_SHORT 			tmWsnDecShort

#define DEC_SHORT_OPT(fval) 							\
	{ uuInvalid(fval) ? tmWsnDecStr("?") : tmWsnDecShort(fval); }

#define DEC_USHORT			tmWsnDecUshort
#define DEC_USHORTX			tmWsnDecUshortx

#define DEC_USHORT_OPT(fval) 						\
	{ uuInvalid(fval) ? tmWsnDecStr("?") : tmWsnDecUshort(fval); }
#define DEC_USHORTX_OPT(fval) 						\
	{ uuInvalid(fval) ? tmWsnDecStr("?") : tmWsnDecUshortx(fval); }

#define DEC_INT 			tmWsnDecInt

#define DEC_INT_OPT(fval) 				\
	{ uuInvalid(fval) ? tmWsnDecStr("?") : tmWsnDecInt(fval); }

#define DEC_UINT 			tmWsnDecUint
#define DEC_UINTX 			tmWsnDecUintx

#define DEC_UINT_OPT(fval) \
	{ uuInvalid(fval) ? tmWsnDecStr("?") : tmWsnDecUint(fval); }
#define DEC_UINTX_OPT(fval) \
	{ uuInvalid(fval) ? tmWsnDecStr("?") : tmWsnDecUintx(fval); }

#define DEC_LONG 			tmWsnDecINT
#define DEC_LONG_OPT 		tmWsnDecINT_OPT
#define DEC_ULONG 			tmWsnDecUINT
#define DEC_ULONGX 			tmWsnDecUINTX
#define DEC_ULONG_OPT 		tmWsnDecUINT_OPT
#define DEC_ULONGX_OPT 		tmWsnDecUINTX_OPT

#define DEC_FS_CAT()		tmWsnDecFsCat()

/************************************************************************
 * 	  DECODING (C->WSN) Object version        							*
 ************************************************************************/
/* Create object to contain the new signal */
#define DEC_START_OBJ()			tmWsnDecStartObj()

/* Set global variable in TCL interpreter with contents of tmWsnNewSig */
#define DEC_SET_VAR_OBJ(itp,var)	{	\
	tmTclSetObj(itp,var,tmWsnNewSig,TCL_GLOBAL_ONLY|TCL_LEAVE_ERR_MSG); \
	tmWsnNewSig = NULL; }

#define DEC_NOTPRESENT_OBJ(itp) 	tmWsnDecStrObj(itp,"?")

/* Set local variable in TCL interpreter with contents of tmWsnNewSig */
#define DEC_SET_LOCVAR_OBJ(itp,var)	tmTclSetObj(itp,var,tmWsnNewSig,0)

#define DEC_TYPE_OBJ(itp,sid)		{							\
	char* tag = tmSidTag(sid);									\
	if(tag!=NULL)												\
		tmWsnDecStrObj(itp,tag);								\
	else														\
		tmAbort("DEC_TYPE_OBJ: unknown sid = 0x%08x", sid);}

#define DEC_STRING_OBJ(itp,val)	 	tmWsnDecStrObj(itp,val)

/* void Xxx(tmITPt* itp, char* p, int len); */
/* if len = 0, put "?" in the signal field*/
#define DEC_HEX_OBJ(itp,p,len) 		tmWsnDecHexObj(itp,(char*)(p),len)

/* BINSTR is a binary string as returned by TCL command "binary format" */
#define DEC_BINSTR_OBJ(itp,p,len)	tmWsnDecBinStrObj(itp,(char*)(p),len)

#define DEC_BIT_OBJ(itp,fval) 									\
	{ ((fval)==0) ? tmWsnDecStrObj(itp,"0") : tmWsnDecStrObj(itp,"1"); }

#define DEC_CHAR_OBJ(itp,val)		tmWsnDecIntObj(itp,(char)val)

#define DEC_UCHAR_OBJ(itp,val)		tmWsnDecIntObj(itp,(uchar)val)
#define DEC_UCHAR_OPT_OBJ(itp,fval) \
	{ uuInvalid(fval) ? tmWsnDecStrObj(itp,"?") : tmWsnDecIntObj(itp,(uchar)fval); }

#define DEC_SHORT_OBJ(itp,val)		tmWsnDecIntObj(itp,(short)val)

#define DEC_USHORT_OBJ(itp,val)		tmWsnDecIntObj(itp,(ushort)val)
#define DEC_USHORT_OPT_OBJ(itp,fval) \
	{ uuInvalid(fval) ? tmWsnDecStrObj(itp,"?") : tmWsnDecIntObj(itp,(ushort)fval); }

#define DEC_INT_OBJ(itp,val)		tmWsnDecIntObj(itp,val)

#define DEC_UINT_OBJ(itp,val) 		tmWsnDecUintObj(itp,val)
#define DEC_UINT_OPT_OBJ(itp,fval) \
	{ uuInvalid(fval) ? tmWsnDecStrObj(itp,"?") : tmWsnDecUintObj(itp,(int)fval); }

#define DEC_BOOL_OBJ(itp,val)       tmWsnDecBoolObj(itp, (int)val)
#define DEC_ULONGLONG(itp,val)		tmWsnDecULongLongObj(itp,val)

/***** LIST HANDLING *****/
/* This macros are used for a field of a signal, list or another
 * structure that has a shape as the following:
 * {elem1 elem2 ...}
 * This type of field in WSN is called with the keyword LIST_OF.
*/

/* Common parameters meaning:
 * itp: tmITPt* (pointer to the current TCL interpreter)
 * p: value to be decoded and put in the signal. The type
 * is related to the signal field.
 *
 * dstObj: Tcl_Obj *. Of this parameter use one of the following macros:
 * DEC_STRUCT_PTR or DEC_LIST_PTR.
*/

/* dstObjPtr: Tcl_Obj *. For this parameter use one of the following macros:
 * DEC_SIG_PTR, DEC_LIST_PTR, DEC_STRUCT_PTR.
 * If, for example, the list/structure is the field of a
 * signal, no matter of its position, use DEC_SIG_PTR;
 * if it is the field of a list (list/structure inside a
 * list), use DEC_LIST_PTR(IncludingListId);
 * if, for example, the list/structure is the field of a
 * structure, use DEC_STRUCT_PTR(IncludingStrId).
 *
 * listId: it is a string used by the macro to compose the
 * name of a variable.
 * This name needs to be unique in case of a multi-level
 * list, that is, if a list contains
 * another list, they need to have different listIds
 *
 * strId: it is a string used by the macro to compose the
 * name of a variable.
 * This name needs to be unique in case of a multi-level
 * structure, that is if a structure contains
 * another structure, they need to have different strIds */

/* Example of decoding of a list and a structure
Let's say you need to decode an array of struct defined as
rfcStrT Rfc[5]
struct rfcStrT {
	uchar RfcA
	struct RfcBStrT RfcB
}

struct RfcBStrT {
	char Rfci
	uchar Ipti
}

The Tstm signal is defined as
#define signalFMAT "STRUCT {LIST_OF rfcStrT Rfc}"
#define signalFMAT_IUCS_RFC_B "STRUCT {CHAR Rfci} {UCHAR Ipti}"

DEC_START_LIST_OBJ(Rfc);
for(i=0;i<5;i++)
{
	DEC_UCHAR_FLD_OBJ(tmITP, MSG_DATA.Rfc[i].RfcA, DEC_LIST_PTR(Rfc));

	DEC_START_STRUCT_OBJ(tmITP, RfcB, "IUCS_RFC_B");

	DEC_CHAR_FLD_OBJ(tmITP, MSG_DATA.Rfc[i].Rfci,DEC_STRUCT_PTR(RfcB));
	DEC_UCHAR_FLD_OBJ(tmITP, MSG_DATA.Rfc[i].Ipti,DEC_STRUCT_PTR(RfcB));

	DEC_STOP_STRUCT_OBJ(tmITP, DEC_LIST_PTR(Rfc), RfcB);
}
DEC_STOP_LIST_OBJ(tmITP, DEC_SIG_PTR, Rfc);
*/

#define DEC_SIG_PTR tmWsnNewSig
#define DEC_LIST_PTR(listId) ListPtr##listId
#define DEC_STRUCT_PTR(strId) StrPtr##strId
/* Create object to contain the new list field */
#define DEC_START_LIST_OBJ(listId)	\
	do { Tcl_Obj *ListPtr##listId; tmWsnDecStartListObj(&ListPtr##listId)

#define DEC_STOP_LIST_OBJ(itp, dstObjPtr, listId)	\
	tmWsnDecStopListInListObj(itp, dstObjPtr, ListPtr##listId); }while(0)


/***** STRUCTURE HANDLING *****/
/* This macros are used for a field of a signal, list or another
 * structure that has a shape as the following:
 * {STRUCT_NAME field1 field2 ...}
 * This type of field in WSN is called with the keyword STRUCTURE.
 * Note that in WSN there is also the keyword STRUCT, that has
 * a different meaning.
*/

/* Common parameters meaning: see LIST HANDLING */

/* tmITPt* itp */
/* strId: used to compose a unique name for variable that points Tcl_Obj */
/* char *strType: WSN structure name */
#define DEC_START_STRUCT_OBJ(itp, strId, strType)	\
	do { Tcl_Obj *StrPtr##strId; \
		tmWsnDecStartListObj(&StrPtr##strId); \
		tmWsnDecStrListObj(itp, strType, StrPtr##strId)

#define DEC_STOP_STRUCT_OBJ(itp, dstObjPtr, strId)	\
	tmWsnDecStopListInListObj(itp, dstObjPtr, StrPtr##strId); }while(0)

/***** DECODING MACROS for LIST AND STRUCTURE FIELDS *****/

#define DEC_HEX_FLD_OBJ(itp, p, len, dstObj) 	\
	tmWsnDecHexStructObj(itp,(char*)(p),len, dstObj)
/*example of use:
 * DEC_HEX_FLD_OBJ(itp, p, len, DEC_STRUCT_PTR(StrName))
 */

#define DEC_BIN_FLD_OBJ(itp, p, len, dstObj) 	\
	tmWsnDecBinStructObj(itp,(char*)(p),len, dstObj)

/*this macro uses DecUint for the problem of overflow*/
#define DEC_UINT_FLD_OBJ(itp, val, dstObj) 	\
	tmWsnDecUintListObj(itp, val, dstObj)

#define DEC_INT_FLD_OBJ(itp, val, dstObj) 	\
	tmWsnDecIntListObj(itp, val, dstObj)

#define DEC_ULONGLONG_FLD_OBJ(itp, val, dstObj) \
	tmWsnDecULongLongListObj(itp, val, dstObj)

#define DEC_SHORT_FLD_OBJ(itp, val, dstObj) 	\
	tmWsnDecIntListObj(itp, (short)val, dstObj)

#define DEC_USHORT_FLD_OBJ(itp, val, dstObj) 	\
	tmWsnDecIntListObj(itp, (ushort)val, dstObj)

#define DEC_CHAR_FLD_OBJ(itp, val, dstObj) 	\
	tmWsnDecIntListObj(itp, (char)val, dstObj)

#define DEC_UCHAR_FLD_OBJ(itp, val, dstObj) 	\
	tmWsnDecIntListObj(itp, (uchar)val, dstObj)

#define DEC_BOOL_FLD_OBJ(itp, val, dstObj)	\
	tmWsnDecBoolListObj(itp, (int)val, dstObj)

/* tmITPt* itp, char *str */
#define DEC_STRING_FLD_OBJ(itp, str, dstObj)		\
	tmWsnDecStrListObj(itp,str,dstObj)

#define DEC_NOTPRES_FLD_OBJ(itp,dstObj) \
	tmWsnDecStrListObj(itp,"?",dstObj)

/*Obsolete macros defined for backward compatibility*/
#define DEC_HEX_STRUCT_OBJ DEC_HEX_FLD_OBJ

#define DEC_BIN_STRUCT_OBJ DEC_BIN_FLD_OBJ

#define DEC_UINT_STRUCT_OBJ DEC_UINT_FLD_OBJ

#define DEC_INT_STRUCT_OBJ DEC_INT_FLD_OBJ

#define DEC_USHORT_STRUCT_OBJ DEC_USHORT_FLD_OBJ

#define DEC_CHAR_STRUCT_OBJ DEC_CHAR_FLD_OBJ

#define DEC_UCHAR_STRUCT_OBJ DEC_UCHAR_FLD_OBJ

#define DEC_STRING_STRUCT_OBJ DEC_STRING_FLD_OBJ

#define DEC_NOTPRES_STRUCT_OBJ DEC_NOTPRES_FLD_OBJ

#define DEC_STRING_LIST_OBJ(itp,str,listId)	\
	DEC_STRING_FLD_OBJ(itp,str,DEC_LIST_PTR(listId))

#define DEC_UCHAR_LIST_OBJ(itp,val,listId) \
	DEC_UCHAR_FLD_OBJ(itp,val,DEC_LIST_PTR(listId))
