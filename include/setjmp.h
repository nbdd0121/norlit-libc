#ifndef _NORLIT_LIBC_SETJMP_H
#define _NORLIT_LIBC_SETJMP_H

#include <norlit/header/start.h>
typedef struct {
	unsigned long __gp[sizeof(void*) == 4 ? 4 : 6];
	unsigned long __sp;
	unsigned long __ip;
} jmp_buf[1];

void   longjmp(jmp_buf, int);
int    setjmp(jmp_buf);

// Obsolete XSI
void   _longjmp(jmp_buf, int);
int    _setjmp(jmp_buf);

// CX Extensions
// typedef ??? sigjmp_buf
// void   siglongjmp(sigjmp_buf, int);
// int    sigsetjmp(sigjmp_buf, int);
#include <norlit/header/end.h>

#endif