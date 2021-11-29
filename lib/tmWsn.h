/*********************************************************************
  Title: Weak-Typed Syntax Notation - tmWsn.h
 ---------------------------------------------------------------------
  $URL: http://memo.prisma/svn/fw/fw-3/3.0.5/fwsrc/com/fwtstm/tmWsn.h $

  $Author: roger $
  $Date: 2011-09-16 09:51:49 +0200 (Fri, 16 Sep 2011) $

  $Rev: 768 $
 *********************************************************************/


#ifndef tmWsnDEFINED
#define tmWsnDEFINED

#include "tm.h"


/*
 * @alex
 * This predicate is TRUE if `obj' is VOID ('?')
 */
#define  tmWsnIsVoid(obj) tmUu_IsVoid(obj)

void tmWsnInit(char *mem, uint maxsiglen, uint maxfldno);
/* Inits the module (use tmWsnMem to compute tthe required mem)
 *
 *	mem;		 user allocated memory
 *	maxsiglen;	 max. length of tmWsn signals
 *	maxfldno;	 max. no. of fields per signal
 */

void tmWsnAdd(tmITPt* itp);
/* Add WSN support commands to an interpreter */

void tmWsnAddTypedefCmd(tmITPt* itp);
/* Add WSN typedef command to an interpreter */

void tmWsnUtilsAdd(tmITPt* itp);
/* Add WSN utils to an interpreter */

void tmWsnTypedef(char* type, char* fmat);
/* Define WSN types */

/* int tmWsnMem(uint maxsiglen, uint maxfldno) */
#define tmWsnMem(maxsiglen,maxfldno) 	\
	(((maxsiglen)+(maxfldno*sizeof(char*)))*2)

/******************************************************************
 * Var pubbliche che non sembrano essere usate all'esterno (@alex)
 ******************************************************************/
//extern uint tmWsnMaxSigLen;
//extern uint tmWsnMaxFldNo;
//extern int   tmWsnBufp;		/* index for tmWsnBuf */
//extern uchar *tmWsnFsBuf;	/* buffer for FLDSTR to be decoded */
//extern char  **tmWsnFsFp;	/* pointers to FLDSTR subfields */
/************************************************************/

extern uchar *tmWsnBuf;		/* buffer for signal to be decoded */
extern char  **tmWsnFp;		/* pointer to signal fields */

extern Tcl_Obj *tmWsnNewSig; /*pointer to the input signal*/
extern Tcl_Obj **EncSigPtr;  /* pointer to the object list containing
								the output signal */


/*------------------------------------------------------------------*
 |	WSN CODEC         												|
 *------------------------------------------------------------------*/

void tmWsnDecStart(void);
void tmWsnDecStr(char* val);
void tmWsnDecStrf(char* fmat, ...);
void tmWsnDecChar(int val);
void tmWsnDecUchar(uint val);
void tmWsnDecShort(int val);
void tmWsnDecUshort(uint val);
void tmWsnDecInt(int val);
void tmWsnDecUint(uint val);
void tmWsnDecIntx(int val);
void tmWsnDecCharx(int val);
void tmWsnDecShortx(int val);
#define tmWsnDecUintx tmWsnDecIntx
#define tmWsnDecUcharx tmWsnDecCharx
#define tmWsnDecUshortx tmWsnDecShortx
void tmWsnDecHex(char *data, int len);
void tmWsnDecFsCat(void);

void tmWsnDecStartObj(void);
void tmWsnDecStrObj(tmITPt* itp, char* val);
void tmWsnDecStrObj2(tmITPt* itp, Tcl_Obj* strObj); // argument is already a Tcl_Obj (string object)
void tmWsnDecIntObj(tmITPt* itp, int val);
void tmWsnDecUintObj(tmITPt* itp, uint val);
void tmWsnDecULongLongObj(tmITPt* itp, unsigned long long int val);
void tmWsnDecBoolObj(tmITPt* itp, int val);
void tmWsnDecBinStrObj(tmITPt* itp, char *data, int len);
void tmWsnDecHexObj(tmITPt* itp, char *data, int len);

void  tmWsnDecStartListObj(Tcl_Obj **pObj);
void tmWsnDecStopListObj(tmITPt* itp, Tcl_Obj *ListPtr);
void tmWsnDecIntListObj(tmITPt* itp, int val, Tcl_Obj *ListPtr);
void tmWsnDecUintListObj(tmITPt* itp, uint val, Tcl_Obj *ListPtr);
void tmWsnDecULongLongListObj(tmITPt* itp, unsigned long long val, Tcl_Obj *ListPtr);
void tmWsnDecBoolListObj(tmITPt* itp, int val, Tcl_Obj *ListPtr);
void tmWsnDecStrListObj(tmITPt* itp, char *str, Tcl_Obj *ListPtr);
void tmWsnDecStrListObj2(tmITPt* itp, Tcl_Obj* strObj, Tcl_Obj *ListPtr);

void tmWsnDecStopListInListObj(tmITPt* itp, Tcl_Obj *ListOutPtr, Tcl_Obj *ListInPtr);
void tmWsnDecHexStructObj(tmITPt* itp, char *data, int len, Tcl_Obj *ListPtr);
void tmWsnDecBinStructObj(tmITPt* itp, char *data, int len, Tcl_Obj *ListPtr);

int tmWsnEncStart(tmITPt* itp, char* var);
int tmWsnEncPrintFields(void);
int tmWsnEncInt(char *val, char* fieldname);
int tmWsnEncIntDef(char *val, char* fieldname, int defval);
char* tmWsnEncStr(char *val,char* fieldname);
char* tmWsnEncStrDef(char *val,char* fieldname,char* defval);
int tmWsnEncHex(char* dst,char *val,char* fieldname);
int tmWsnEncFsStart(uint n);

int tmWsnEncStartObj(tmITPt* itp, char* var);
int tmWsnEncStartListObj(tmITPt* itp, Tcl_Obj *ListPtr, Tcl_Obj ***pElemPtr);

int tmWsnEncBinStrListObj(char* dst, char* fieldname, Tcl_Obj* ObjPtr);
char* tmWsnEncStrDefObj(uint val, char* defval);
char* tmWsnEncStrListObj(char* fieldname, Tcl_Obj *ObjPtr);
char* tmWsnEncCharOptListObj(tmITPt* itp, char* fieldname, char* dst, Tcl_Obj *ObjPtr);
short* tmWsnEncShortOptListObj(tmITPt* itp, char* fieldname, short* dst, Tcl_Obj *ObjPtr);
int* tmWsnEncIntOptListObj(tmITPt* itp, char* fieldname, int* dst, Tcl_Obj *ObjPtr);
int tmWsnStructFieldPresObj(Tcl_Obj *ObjPtr);

int tmWsnEncIntListObj(tmITPt* itp, char* fieldname, Tcl_Obj *ObjPtr);
int tmWsnEncIntListDefObj(tmITPt* itp, char* fieldname, Tcl_Obj *ObjPtr, int defval);
long long int tmWsnEncLongLongListObj(tmITPt* itp, char* fieldname, Tcl_Obj *ObjPtr);
long long int tmWsnEncLongLongListDefObj(tmITPt* itp, char* fieldname, Tcl_Obj *ObjPtr, long long int defval);
int tmWsnEncBoolListObj(tmITPt* itp, char* fieldname, Tcl_Obj *ObjPtr);
int tmWsnHexFldLenListObj(Tcl_Obj *ObjPtr);
int tmWsnEncHexListObj(char* dst, Tcl_Obj *ObjPtr);

#define tmWsnEncBinStrObj(dst, val, fieldname) \
	({tmWsnEncBinStrListObj(dst, fieldname, EncSigPtr[val]); })

#define tmWsnEncStrObj(val, fieldname) \
	({ tmWsnEncStrListObj(fieldname, EncSigPtr[val]); })

#define tmWsnEncHexObj(dst, val, fieldname) \
	({ tmWsnEncHexListObj(dst, EncSigPtr[val]); })

#define tmWsnEncIntObj(itp, val, fieldname) \
	({ tmWsnEncIntListObj(itp, fieldname, EncSigPtr[val]); })

#define tmWsnEncIntDefObj(itp, val, fieldname, defval) \
	({ tmWsnEncIntListDefObj(itp, fieldname, EncSigPtr[val], defval); })

#define tmWsnEncBoolObj(itp, val, fieldname) \
	({ tmWsnEncBoolListObj(itp, fieldname, EncSigPtr[val]); })

#define tmWsnEncLongLongObj(itp, val, fieldname) \
	({ tmWsnEncLongLongListObj(itp, fieldname, EncSigPtr[val]); })

#define tmWsnEncLongLongDefObj(itp, val, fieldname, defval) \
	({ tmWsnEncLongLongListDefObj(itp, fieldname, EncSigPtr[val], defval); })

#define tmWsnEncCharOptObj(itp, val,fieldname, dst) \
	({ tmWsnEncCharOptListObj(itp, fieldname, dst, EncSigPtr[val]); })

#define tmWsnEncShortOptObj(itp, val, fieldname, dst) \
	({ tmWsnEncShortOptListObj(itp, fieldname, dst, EncSigPtr[val]) })

#define tmWsnEncIntOptObj(itp, val, fieldname, dst) \
	({ tmWsnEncIntOptListObj(itp, fieldname, dst, EncSigPtr[val]); })

/*
 * @@ DA FARE :
 * EncInthex		aabbccdd -> int
 * DecInthex		int -> aabbccdd ->
 * e simili
 */

#endif
