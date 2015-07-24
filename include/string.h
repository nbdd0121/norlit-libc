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

#ifndef _NORLIT_LIBC_STRING_H
#define _NORLIT_LIBC_STRING_H

#define __need_locale_t
#include <norlit/alltypes.h>

#define __need_size_t
#define __need_NULL
#include <stddef.h>

#include <norlit/header/start.h>
void    *memchr(const void *, int, size_t);
int      memcmp(const void *, const void *, size_t);
void    *memcpy(void *__restrict, const void *__restrict, size_t);
void    *memmove(void *, const void *, size_t);
void    *memset(void *, int, size_t);
char    *strcat(char *__restrict, const char *__restrict);
char    *strchr(const char *, int);
int      strcmp(const char *, const char *);
int      strcoll(const char *, const char *);
char    *strcpy(char *__restrict, const char *__restrict);
size_t   strcspn(const char *, const char *);
char    *strerror(int);
size_t   strlen(const char *);
char    *strncat(char *__restrict, const char *__restrict, size_t);
int      strncmp(const char *, const char *, size_t);
char    *strncpy(char *__restrict, const char *__restrict, size_t);
char    *strpbrk(const char *, const char *);
char    *strrchr(const char *, int);
size_t   strspn(const char *, const char *);
char    *strstr(const char *, const char *);
char    *strtok(char *__restrict, const char *__restrict);
size_t   strxfrm(char *__restrict, const char *__restrict, size_t);

// XSI Extensions
void    *memccpy(void *__restrict, const void *__restrict, int, size_t);

// CX Extensions
char    *stpcpy(char *__restrict, const char *__restrict);
char    *stpncpy(char *__restrict, const char *__restrict, size_t);
int      strcoll_l(const char *, const char *, locale_t);
char    *strdup(const char *);
char    *strerror_l(int, locale_t);
int      strerror_r(int, char *, size_t);
char    *strndup(const char *, size_t);
size_t   strnlen(const char *, size_t);
char    *strsignal(int);
char    *strtok_r(char *__restrict, const char *__restrict, char **__restrict);
size_t   strxfrm_l(char *__restrict, const char *__restrict,
                   size_t, locale_t);

// GLIBC Extensions
void    *memrchr(const void *, int, size_t);
#include <norlit/header/end.h>

#endif