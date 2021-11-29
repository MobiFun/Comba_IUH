/*********************************************************************
  $URL: http://memo.prisma/svn/tm/IuhCsComba_Tm/tags/IuhCsComba_Tm-1.2.0/src/tm_compat.h $

  $Author: roger $
  $Date: 2012-07-19 18:45:02 +0200 (Thu, 19 Jul 2012) $

  $Rev: 53339 $
 *********************************************************************/

#ifndef tm_compatINCLUDED
#define tm_compatINCLUDED

#include "fwBasic.h"
#include <tcl.h>

// avoid include of following definitions if tm.h is already included
#ifndef tmDEFINED

/* tmTcl.h */
typedef Tcl_Interp tmITPt;

/* tm.c */
void tmAbort(char* fmat, ...);
void    tmLog(char* fmat, ...);
void tmLogscr(char* fmat, ...);

#endif

/* tmTcl.c */
int tmTclErrObj(tmITPt* itp, char* fmat, ...);
void tmTclCmdNewObj(tmITPt* itp, char* cmd, Tcl_ObjCmdProc *func);
void tmTclSetObj(tmITPt* itp, char* name, Tcl_Obj *val, int Flags);

/* tmSid.c */
char* tmSidTag(uint sid);
void tmSidStatic(uint sid, char* tag);
uint tmSidId(char* tag);

// keep tmWsn.h in this position because it uses some previous definitions
#include "tmWsn.h"

#include "tmWsnCodec.h"

/* tm_compat.c */
ushort l2b_short (ushort little_val);

// numbits: number of bits to be converted. If 0 means 32.
void l2b_int (uint little_val, char *dst, int numbits);

// MSB are bits in element 0, LSB in element 3.
// Bits to be converted are put in most significant bits of dst.
// big_val: big endian value stored in a 4 bytes array
// numbits: number of bits to be converted. If 0 means 32.
uint b2l_int (unsigned char *big_val, int numbits);

tmITPt *tm_compatITP(void);

#endif
