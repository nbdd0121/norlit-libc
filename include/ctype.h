#ifndef _NORLIT_LIBC_CTYPE_H
#define _NORLIT_LIBC_CTYPE_H

#define __need_locale_t
#include <norlit/alltypes.h>

#define _U 0x1
#define _L 0x2
#define _N 0x4
#define _S 0x8
#define _P 0x10
#define _C 0x20
#define _X 0x40
#define _B 0x80

#include <norlit/header/start.h>

int   isalnum(int);
int   isalpha(int);
int   isblank(int);
int   iscntrl(int);
int   isdigit(int);
int   isgraph(int);
int   islower(int);
int   isprint(int);
int   ispunct(int);
int   isspace(int);
int   isupper(int);
int   isxdigit(int);
int   tolower(int);
int   toupper(int);

// CX Extensions
int   isalnum_l(int, locale_t);
int   isalpha_l(int, locale_t);
int   isblank_l(int, locale_t);
int   iscntrl_l(int, locale_t);
int   isdigit_l(int, locale_t);
int   isgraph_l(int, locale_t);
int   islower_l(int, locale_t);
int   isprint_l(int, locale_t);
int   ispunct_l(int, locale_t);
int   isspace_l(int, locale_t);
int   isupper_l(int, locale_t);
int   isxdigit_l(int, locale_t);
int   tolower_l(int, locale_t);
int   toupper_l(int, locale_t);

// OB XSI Extensions
int   isascii(int);
int   toascii(int);
#define _tolower(x) ((x)|0x20)
#define _toupper(x) ((x)&0x5f)

#include <norlit/header/end.h>

#endif