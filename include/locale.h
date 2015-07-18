#if !defined(__need_locale_t)
#define __need_locale_t
#define __need_others
#endif

#ifdef __need_locale_t
#undef __need_locale_t
#ifndef _NORLIT_LIBC_LOCALE_H_LOCALE_T
#define _NORLIT_LIBC_LOCALE_H_LOCALE_T
// CX Extension
typedef void* locale_t;
#endif
#endif

#ifdef __need_others
#undef __need_others
#ifndef _NORLIT_LIBC_LOCALE_H_OTHERS
#define _NORLIT_LIBC_LOCALE_H_OTHERS

#define __need_NULL
#include <stddef.h>

#define LC_CTYPE    0
#define LC_NUMERIC  1
#define LC_TIME     2
#define LC_COLLATE  3
#define LC_MONETARY 4
#define LC_MESSAGES 5
#define LC_ALL      6

struct lconv {
	char    *currency_symbol;
	char    *decimal_point;
	char     frac_digits;
	char    *grouping;
	char    *int_curr_symbol;
	char     int_frac_digits;
	char     int_n_cs_precedes;
	char     int_n_sep_by_space;
	char     int_n_sign_posn;
	char     int_p_cs_precedes;
	char     int_p_sep_by_space;
	char     int_p_sign_posn;
	char    *mon_decimal_point;
	char    *mon_grouping;
	char    *mon_thousands_sep;
	char    *negative_sign;
	char     n_cs_precedes;
	char     n_sep_by_space;
	char     n_sign_posn;
	char    *positive_sign;
	char     p_cs_precedes;
	char     p_sep_by_space;
	char     p_sign_posn;
	char    *thousands_sep;
};

struct lconv *localeconv(void);
char         *setlocale(int, const char *);

// CX Extensions
#define LC_GLOBAL_LOCALE ((locale_t)-1)

#define LC_CTYPE_MASK    (1<<LC_CTYPE)
#define LC_NUMERIC_MASK  (1<<LC_NUMERIC)
#define LC_TIME_MASK     (1<<LC_TIME)
#define LC_COLLATE_MASK  (1<<LC_COLLATE)
#define LC_MONETARY_MASK (1<<LC_MONETARY)
#define LC_MESSAGES_MASK (1<<LC_MESSAGES)
#define LC_ALL_MASK      0x7FFFFFFF

// CX Extensions
locale_t      duplocale(locale_t);
void          freelocale(locale_t);
locale_t      newlocale(int, const char *, locale_t);
locale_t      uselocale(locale_t);

#endif
#endif