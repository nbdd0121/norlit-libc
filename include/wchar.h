/*
 * Copyright (c) 2015, Gary Guo 
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met: 
 * 
 *  * Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer. 
 *  * Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY 
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
 * DAMAGE. 
 */

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
wchar_t      *fgetws(wchar_t *__restrict, int, FILE *__restrict);
wint_t        fputwc(wchar_t, FILE *);
int           fputws(const wchar_t *__restrict, FILE *__restrict);
int           fwide(FILE *, int);
int           fwprintf(FILE *__restrict, const wchar_t *__restrict, ...);
int           fwscanf(FILE *__restrict, const wchar_t *__restrict, ...);
wint_t        getwc(FILE *);
wint_t        getwchar(void);
size_t        mbrlen(const char *__restrict, size_t, mbstate_t *__restrict);
size_t        mbrtowc(wchar_t *__restrict, const char *__restrict, size_t,
                      mbstate_t *__restrict);
int           mbsinit(const mbstate_t *);
size_t        mbsrtowcs(wchar_t *__restrict, const char **__restrict, size_t,
                        mbstate_t *__restrict);
wint_t        putwc(wchar_t, FILE *);
wint_t        putwchar(wchar_t);
int           swprintf(wchar_t *__restrict, size_t,
                       const wchar_t *__restrict, ...);
int           swscanf(const wchar_t *__restrict,
                      const wchar_t *__restrict, ...);
wint_t        ungetwc(wint_t, FILE *);
int           vfwprintf(FILE *__restrict, const wchar_t *__restrict, va_list);
int           vfwscanf(FILE *__restrict, const wchar_t *__restrict, va_list);
int           vswprintf(wchar_t *__restrict, size_t,
                        const wchar_t *__restrict, va_list);
int           vswscanf(const wchar_t *__restrict, const wchar_t *__restrict,
                       va_list);
int           vwprintf(const wchar_t *__restrict, va_list);
int           vwscanf(const wchar_t *__restrict, va_list);
size_t        wcrtomb(char *__restrict, wchar_t, mbstate_t *__restrict);
wchar_t      *wcscat(wchar_t *__restrict, const wchar_t *__restrict);
wchar_t      *wcschr(const wchar_t *, wchar_t);
int           wcscmp(const wchar_t *, const wchar_t *);
int           wcscoll(const wchar_t *, const wchar_t *);
wchar_t      *wcscpy(wchar_t *__restrict, const wchar_t *__restrict);
size_t        wcscspn(const wchar_t *, const wchar_t *);
size_t        wcsftime(wchar_t *__restrict, size_t,
                       const wchar_t *__restrict, const struct tm *__restrict);
size_t        wcslen(const wchar_t *);
wchar_t      *wcsncat(wchar_t *__restrict, const wchar_t *__restrict, size_t);
int           wcsncmp(const wchar_t *, const wchar_t *, size_t);
wchar_t      *wcsncpy(wchar_t *__restrict, const wchar_t *__restrict, size_t);
wchar_t      *wcspbrk(const wchar_t *, const wchar_t *);
wchar_t      *wcsrchr(const wchar_t *, wchar_t);
size_t        wcsrtombs(char *__restrict, const wchar_t **__restrict,
                        size_t, mbstate_t *__restrict);
size_t        wcsspn(const wchar_t *, const wchar_t *);
wchar_t      *wcsstr(const wchar_t *__restrict, const wchar_t *__restrict);
double        wcstod(const wchar_t *__restrict, wchar_t **__restrict);
float         wcstof(const wchar_t *__restrict, wchar_t **__restrict);
wchar_t      *wcstok(wchar_t *__restrict, const wchar_t *__restrict,
                     wchar_t **__restrict);
long          wcstol(const wchar_t *__restrict, wchar_t **__restrict, int);
long double   wcstold(const wchar_t *__restrict, wchar_t **__restrict);
long long     wcstoll(const wchar_t *__restrict, wchar_t **__restrict, int);
unsigned long wcstoul(const wchar_t *__restrict, wchar_t **__restrict, int);
unsigned long long
wcstoull(const wchar_t *__restrict, wchar_t **__restrict, int);

size_t        wcsxfrm(wchar_t *__restrict, const wchar_t *__restrict, size_t);
int           wctob(wint_t);
wchar_t      *wmemchr(const wchar_t *, wchar_t, size_t);
int           wmemcmp(const wchar_t *, const wchar_t *, size_t);
wchar_t      *wmemcpy(wchar_t *__restrict, const wchar_t *__restrict, size_t);
wchar_t      *wmemmove(wchar_t *, const wchar_t *, size_t);
wchar_t      *wmemset(wchar_t *, wchar_t, size_t);
int           wprintf(const wchar_t *__restrict, ...);
int           wscanf(const wchar_t *__restrict, ...);

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
size_t        mbsnrtowcs(wchar_t *__restrict, const char **__restrict,
                         size_t, size_t, mbstate_t *__restrict);
FILE         *open_wmemstream(wchar_t **, size_t *);
wchar_t      *wcpcpy(wchar_t *__restrict, const wchar_t *__restrict);
wchar_t      *wcpncpy(wchar_t *__restrict, const wchar_t *__restrict, size_t);
int           wcscasecmp(const wchar_t *, const wchar_t *);
int           wcscasecmp_l(const wchar_t *, const wchar_t *, locale_t);
int           wcscoll_l(const wchar_t *, const wchar_t *, locale_t);
wchar_t      *wcsdup(const wchar_t *);
int           wcsncasecmp(const wchar_t *, const wchar_t *, size_t);
int           wcsncasecmp_l(const wchar_t *, const wchar_t *, size_t,
                            locale_t);
size_t        wcsnlen(const wchar_t *, size_t);
size_t        wcsnrtombs(char *__restrict, const wchar_t **__restrict, size_t,
                         size_t, mbstate_t *__restrict);
size_t        wcsxfrm_l(wchar_t *__restrict, const wchar_t *__restrict,
                        size_t, locale_t);

#include <norlit/header/end.h>

#endif