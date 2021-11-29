/**********************************************************************
  Definizioni di Base
 ----------------------------------------------------------------------
  $URL: http://memo.prisma/svn/fw/fw-3/3.0.5/fwsrc/com/fwcom/fwBasic.h $
 $Date: 2012-06-19 11:06:23 +0200 (Tue, 19 Jun 2012) $
  $Rev: 1516 $
 **********************************************************************/

#pragma once


#define _GNU_SOURCE


#define fwVERSION   3
#define fwVERSION3


/*************************************************************
 * Per evitare conflitti con i tipi gia' definiti in libreria
 *************************************************************/

#undef   uchar
#undef   uint
#undef   ushort
#undef   ulong

#undef   int8
#undef   int16
#undef   int32
#undef   int64

#undef   uint8
#undef   uint16
#undef   uint32
#undef   uint64


/*****************************************
 * Inclusione delle librerie piu' comuni
 *****************************************/

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>

#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/wait.h>



/*************************************
 * Adesso possiamo ridefinire i tipi
 *************************************/

#define  int8       char
#define  int16      short
#define  int32      int
#define  int64      long long int

#define  uint8      unsigned int8
#define  uint16     unsigned int16
#define  uint32     unsigned int32
#define  uint64     unsigned int64

#define  uchar		unsigned char
#define  ushort		unsigned short
#define  uint		unsigned int

#define  ulong		unsigned long int  // Attenzione: questo puo' essere
                                       // 32 o 64 bits; e' sempre lungo
                                       // quanto un pointer



/**************************************************
 * Per il software sensibile al sistema operativo
 **************************************************/

#if (defined fwPlatform_linux || defined fwPLATFORM_LINUX)

# undef  fwPlatform_linux
# undef  fwPLATFORM_LINUX
# undef  fwPlatform_nto
# undef  fwPLATFORM_NTO
# define fwPlatform_linux   1
# define fwPLATFORM_LINUX   1

#elif (defined fwPlatform_nto || defined fwPLATFORM_NTO)

# undef  fwPlatform_linux
# undef  fwPLATFORM_LINUX
# undef  fwPlatform_nto
# undef  fwPLATFORM_NTO
# define fwPlatform_nto     1
# define fwPLATFORM_NTO     1

#endif



/***************************************************************
 * I costruttori/distruttori per l'utente
 * ------------------------------------------------------------
 * Le macro fwConstructor(prio)/fwDestructor(prio) definiscono
 * riepwttivamente le funzioni:
 *
 *      __attribute__((constructor(prio))) static void
 *      fwConstructor__num__
 * e
 *      __attribute__((destructor(prio))) static void
 *      fwDestructor__num__
 *
 * dove:
 *      num     e' il numero della riga in cui e' definita;
 *
 *      prio    e' un intero che indica la priorita' di esecuzione
 *              (piu' basso prima); deve essere nel range 0..50000
 *
 * NOTA:
 *  la priorita' effettiva dell'utente ha un offset di 10000;
 *  i costruttori usati dalla libreria fw hanno priorita'
 *  1000 .. 9999.
 ****************************************************************/

#define fwConstructor(prio)     fwConstructor_(10000 + (prio))
#define fwDestructor(prio)      fwDestructor_(10000 + (prio))

#define fwConstructor_(absprio) fwXtor__(Con, con, absprio)
#define fwDestructor_(absprio)  fwXtor__(De,  de,  absprio)

#define fwXtor__(nam,typ,prio)          fwXtor1__(nam,typ,prio,__LINE__)
#define fwXtor1__(nam,typ,prio,num)     fwXtor2__(nam,typ,prio,num)
#define fwXtor2__(nam,typ,prio,num)                 \
            __attribute__((typ##structor(prio)))    \
            static void                             \
            fw##nam##structor__$##num##$__(void)





/**********************************
 * Alcune macro di base
 **********************************/

#define likely(cond)        (__builtin_expect(!!(cond), 1))
#define unlikely(cond)      (__builtin_expect(!!(cond), 0))

#define inline__            static __inline


#define fwRdtsc()                       \
   ({                                   \
    uint64 v_;                          \
    asm volatile("rdtsc" : "=A"(v_));   \
    v_;                                 \
    })



/******************************************************
 * Bit swap
 ******************************************************/


/********************
 * Versione dinamica
 ********************/

#define fwSwap32(v)                             \
    ({                                          \
    uint _t = v;                                \
    asm ("bswap\t%0" : "=r" (_t) : "0" (_t));   \
    _t;                                         \
    })


#define fwSwap16(v)                             \
    ({                                          \
    ushort _t = v;                              \
    asm ("rorw\t$8,%0" : "=r" (_t) : "0" (_t)); \
    _t;                                         \
    })




/********************
 * Versione costante
 ********************/

#define fwSwap32c(v)              \
    (                             \
    (((v))              >> 24) |  \
    (((v) & 0x00FF0000) >>  8) |  \
    (((v) & 0x0000FF00) <<  8) |  \
    (((v))              << 24) |  \
    )


#define fwSwap16c(v)                          \
    ((((v) & 0xFF) << 8) | (((v) >> 8) & 0xFF))



/******************************************************
 * Operazioni atomiche
 * ---------------------------------------------------
 * Nelle funzioni che seguono, "type" e' uno qualunque
 * dei tipi interi, segnati o non segnati
 ******************************************************/


/*
 * void  fwAtomicAdd(type *ptr, type val);
 * void  fwAtomicSub(type *ptr, type val);
 */

#define fwAtomicAdd(ptr, val)                   \
   ({                                           \
    __asm__ volatile                            \
       (" "                                     \
        "\n\t lock"                             \
        "\n\t add%z[p]  %[v], %[p]"             \
                                                \
        : [p] "=m" (*(ptr))                     \
        :      "m" (*(ptr)), [v] "ri" (val)     \
       );                                       \
    })


#define fwAtomicSub(ptr, val)                   \
   ({                                           \
    __asm__ volatile                            \
       (" "                                     \
        "\n\t lock"                             \
        "\n\t sub%z[p]  %[v], %[p]"             \
                                                \
        : [p] "=m" (*(ptr))                     \
        :      "m" (*(ptr)), [v] "ri" (val)     \
       );                                       \
    })



/*
 * type fwAtomicTestAndSet(type *ptr, type val);
 * -----------------------------------------------------
 * Il valore restituito e' il valore di *ptr prima
 * dell'operazione
 */

#define fwAtomicTestAndSet(ptr,val)             \
   ({                                           \
    typeof(*(ptr)) v_ = val;                    \
                                                \
    __asm__ volatile                            \
       (" "                                     \
        "\n\t xchg%z[p]  %[p], %[v]"            \
                                                \
        : [p] "=m" (*(ptr)),  [v] "+r" (v_)     \
        :      "m" (*(ptr))                     \
       );                                       \
                                                \
    v_;                                         \
    })




/*
 * type fwAtomicFetchAndAdd(type *ptr, type val);
 * -----------------------------------------------------
 * Il valore restituito e' il valore di *ptr prima
 * dell'operazione
 */

#define fwAtomicFetchAndAdd(ptr,val)            \
   ({                                           \
    typeof(*(ptr)) v_ = val;                    \
                                                \
    __asm__ volatile                            \
       (" "                                     \
        "\n\t lock"                             \
        "\n\t xadd%z[p]  %[v], %[p]"            \
                                                \
        : [p] "=m" (*(ptr)),  [v] "+r" (v_)     \
        :      "m" (*(ptr))                     \
       );                                       \
                                                \
    v_;                                         \
    })



/*
 * type fwAtomicCompareAndSwap(type *ptr, type val);
 * -----------------------------------------------------
 * Il valore restituito e' il valore di *ptr prima
 * dell'operazione
 */

#define fwAtomicCompareAndSwap(ptr,oldv,newv)   \
   ({                                           \
    typeof(*(ptr)) ov_ = oldv;                  \
                                                \
    __asm__ volatile                            \
       (" "                                     \
        "\n\t lock"                             \
        "\n\t cmpxchg%z[p]  %[nv], %[p]"        \
                                                \
        : [ov] "+a" (ov_),  [p] "=m" (*(ptr))   \
        : [nv]  "r" (newv),      "m" (*(ptr))   \
       );                                       \
                                                \
    ov_;                                        \
    })



/***************************************************************
 * Semplici macro per il logging e la segnalazione di errno
 ****************************************************************/

/*
 * void
 * fwLog(void (*pfunc)(char *fmat, ...), char *fmat, ...);
 *
 * void
 * fwErrno(void (*pfunc)(char *fmat, ...), char *fmat, ...);
 *
 * void
 * fwErrno_(void (*pfunc)(char *fmat, ...), int errnum, char *fmat, ...);
 *
 *
 * <pfunc>   e' una funzione printf-like, che riceve <fmat> e zero
 *           o piu' argomenti;
 *
 * <fmat>    e' la stringa di formato printf-like; deve essere una
 *           stringa esplicita (non può essere un puntatore);
 *
 * <errnum>  e' un numero di errore (positivo o negativo).
 *
 * ------------------------------------------------------------------
 * La stringa che viene passata a 'pfunc' da fwLog() e':
 *
 *      file:riga: funzione(): argomenti-formattati-secondo-fmat\n
 *
 * ------------------------------------------------------------------
 * La stringa che viene passata a 'pfunc' da fwErrno_() e' quella
 * generata da fwLog (senza "\n" finale) seguita da:
 *
 *      : errno=valore_di_errno: strerror\n
 *
 * dove 'strerror' e' la decodifica di abs(errnum).
 *
 * ------------------------------------------------------------------
 * La stringa che viene passata a 'pfunc' da fwErrno() e' quella
 * generata da fwErrno_(), con errnum = errno.
 * ------------------------------------------------------------------
 */


#define fwERRNO       strerror(errno)



#define fwLog(pfunc, fmat, args...)            \
    pfunc("%s:%d: %s(): " fmat "\n",           \
          __FILE__, __LINE__, __func__, ##args)


#define fwErrno(pfunc, fmat, args...)          \
    fwErrno_(pfunc, errno, fmat, ##args)


#define fwErrno_(pfunc, errnum, fmat, args...) \
   ({                                          \
    int errno_ = errnum;                       \
    errno_ = (errno_ >= 0)? errno_ : -errno_;  \
    fwLog(pfunc, fmat ": errno=%d: %s",        \
          ##args, errno_, strerror(errno_));   \
    })
