#ifndef _NORLIT_LIBC_WCHAR_H
#define _NORLIT_LIBC_WCHAR_H

#define __need_NULL
#include <stddef.h>

#define __need_FILE
#define __need_locale_t
#define __need_mbstate_t
#define __need_size_t
#define __need_va_list
#define __need_wchar_t
#define __need_wctype_t
#define __need_wint_t
#include <norlit/alltypes.h>

#include <stdint.h>

#define WEOF ((wint_t)-1)

#include <norlit/header/start.h>

struct tm;

wint_t        btowc(int);
wint_t        fgetwc(FILE *);
wchar_t      *fgetws(wchar_t *restrict, int, FILE *restrict);
wint_t        fputwc(wchar_t, FILE *);
int           fputws(const wchar_t *restrict, FILE *restrict);
int           fwide(FILE *, int);
int           fwprintf(FILE *restrict, const wchar_t *restrict, ...);
int           fwscanf(FILE *restrict, const wchar_t *restrict, ...);
wint_t        getwc(FILE *);
wint_t        getwchar(void);
size_t        mbrlen(const char *restrict, size_t, mbstate_t *restrict);
size_t        mbrtowc(wchar_t *restrict, const char *restrict, size_t,
                      mbstate_t *restrict);
int           mbsinit(const mbstate_t *);
size_t        mbsrtowcs(wchar_t *restrict, const char **restrict, size_t,
                        mbstate_t *restrict);
wint_t        putwc(wchar_t, FILE *);
wint_t        putwchar(wchar_t);
int           swprintf(wchar_t *restrict, size_t,
                       const wchar_t *restrict, ...);
int           swscanf(const wchar_t *restrict,
                      const wchar_t *restrict, ...);
wint_t        ungetwc(wint_t, FILE *);
int           vfwprintf(FILE *restrict, const wchar_t *restrict, va_list);
int           vfwscanf(FILE *restrict, const wchar_t *restrict, va_list);
int           vswprintf(wchar_t *restrict, size_t,
                        const wchar_t *restrict, va_list);
int           vswscanf(const wchar_t *restrict, const wchar_t *restrict,
                       va_list);
int           vwprintf(const wchar_t *restrict, va_list);
int           vwscanf(const wchar_t *restrict, va_list);
size_t        wcrtomb(char *restrict, wchar_t, mbstate_t *restrict);
wchar_t      *wcscat(wchar_t *restrict, const wchar_t *restrict);
wchar_t      *wcschr(const wchar_t *, wchar_t);
int           wcscmp(const wchar_t *, const wchar_t *);
int           wcscoll(const wchar_t *, const wchar_t *);
wchar_t      *wcscpy(wchar_t *restrict, const wchar_t *restrict);
size_t        wcscspn(const wchar_t *, const wchar_t *);
size_t        wcsftime(wchar_t *restrict, size_t,
                       const wchar_t *restrict, const struct tm *restrict);
size_t        wcslen(const wchar_t *);
wchar_t      *wcsncat(wchar_t *restrict, const wchar_t *restrict, size_t);
int           wcsncmp(const wchar_t *, const wchar_t *, size_t);
wchar_t      *wcsncpy(wchar_t *restrict, const wchar_t *restrict, size_t);
wchar_t      *wcspbrk(const wchar_t *, const wchar_t *);
wchar_t      *wcsrchr(const wchar_t *, wchar_t);
size_t        wcsrtombs(char *restrict, const wchar_t **restrict,
                        size_t, mbstate_t *restrict);
size_t        wcsspn(const wchar_t *, const wchar_t *);
wchar_t      *wcsstr(const wchar_t *restrict, const wchar_t *restrict);
double        wcstod(const wchar_t *restrict, wchar_t **restrict);
float         wcstof(const wchar_t *restrict, wchar_t **restrict);
wchar_t      *wcstok(wchar_t *restrict, const wchar_t *restrict,
                     wchar_t **restrict);
long          wcstol(const wchar_t *restrict, wchar_t **restrict, int);
long double   wcstold(const wchar_t *restrict, wchar_t **restrict);
long long     wcstoll(const wchar_t *restrict, wchar_t **restrict, int);
unsigned long wcstoul(const wchar_t *restrict, wchar_t **restrict, int);
unsigned long long
wcstoull(const wchar_t *restrict, wchar_t **restrict, int);

size_t        wcsxfrm(wchar_t *restrict, const wchar_t *restrict, size_t);
int           wctob(wint_t);
wchar_t      *wmemchr(const wchar_t *, wchar_t, size_t);
int           wmemcmp(const wchar_t *, const wchar_t *, size_t);
wchar_t      *wmemcpy(wchar_t *restrict, const wchar_t *restrict, size_t);
wchar_t      *wmemmove(wchar_t *, const wchar_t *, size_t);
wchar_t      *wmemset(wchar_t *, wchar_t, size_t);
int           wprintf(const wchar_t *restrict, ...);
int           wscanf(const wchar_t *restrict, ...);

// Obsolete XSI
int           iswalnum(wint_t);
int           iswalpha(wint_t);
int           iswcntrl(wint_t);
int           iswctype(wint_t, wctype_t);
int           iswdigit(wint_t);
int           iswgraph(wint_t);
int           iswlower(wint_t);
int           iswprint(wint_t);
int           iswpunct(wint_t);
int           iswspace(wint_t);
int           iswupper(wint_t);
int           iswxdigit(wint_t);
wint_t        towlower(wint_t);
wint_t        towupper(wint_t);
wctype_t      wctype(const char *);

// XSI Extensions
int           wcswidth(const wchar_t *, size_t);
int           wcwidth(wchar_t);

// CX Extensions
size_t        mbsnrtowcs(wchar_t *restrict, const char **restrict,
                         size_t, size_t, mbstate_t *restrict);
FILE         *open_wmemstream(wchar_t **, size_t *);
wchar_t      *wcpcpy(wchar_t *restrict, const wchar_t *restrict);
wchar_t      *wcpncpy(wchar_t *restrict, const wchar_t *restrict, size_t);
int           wcscasecmp(const wchar_t *, const wchar_t *);
int           wcscasecmp_l(const wchar_t *, const wchar_t *, locale_t);
int           wcscoll_l(const wchar_t *, const wchar_t *, locale_t);
wchar_t      *wcsdup(const wchar_t *);
int           wcsncasecmp(const wchar_t *, const wchar_t *, size_t);
int           wcsncasecmp_l(const wchar_t *, const wchar_t *, size_t,
                            locale_t);
size_t        wcsnlen(const wchar_t *, size_t);
size_t        wcsnrtombs(char *restrict, const wchar_t **restrict, size_t,
                         size_t, mbstate_t *restrict);
size_t        wcsxfrm_l(wchar_t *restrict, const wchar_t *restrict,
                        size_t, locale_t);

#include <norlit/header/end.h>

#endif