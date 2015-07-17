#ifndef _NORLIT_LIBC_STRING_H
#define _NORLIT_LIBC_STRING_H

#define __need_size_t
#define __need_NULL
#include <stddef.h>

#define __need_locale_t
#include <locale.h>

void    *memchr(const void *, int, size_t);
int      memcmp(const void *, const void *, size_t);
void    *memcpy(void *restrict, const void *restrict, size_t);
void    *memmove(void *, const void *, size_t);
void    *memset(void *, int, size_t);
char    *strcat(char *restrict, const char *restrict);
char    *strchr(const char *, int);
int      strcmp(const char *, const char *);
int      strcoll(const char *, const char *);
char    *strcpy(char *restrict, const char *restrict);
size_t   strcspn(const char *, const char *);
char    *strerror(int);
size_t   strlen(const char *);
char    *strncat(char *restrict, const char *restrict, size_t);
int      strncmp(const char *, const char *, size_t);
char    *strncpy(char *restrict, const char *restrict, size_t);
char    *strpbrk(const char *, const char *);
char    *strrchr(const char *, int);
size_t   strspn(const char *, const char *);
char    *strstr(const char *, const char *);
char    *strtok(char *restrict, const char *restrict);
size_t   strxfrm(char *restrict, const char *restrict, size_t);

// XSI Extensions
void    *memccpy(void *restrict, const void *restrict, int, size_t);

// CX Extensions
char    *stpcpy(char *restrict, const char *restrict);
char    *stpncpy(char *restrict, const char *restrict, size_t);
int      strcoll_l(const char *, const char *, locale_t);
char    *strdup(const char *);
char    *strerror_l(int, locale_t);
int      strerror_r(int, char *, size_t);
char    *strndup(const char *, size_t);
size_t   strnlen(const char *, size_t);
char    *strsignal(int);
char    *strtok_r(char *restrict, const char *restrict, char **restrict);
size_t   strxfrm_l(char *restrict, const char *restrict,
                   size_t, locale_t);

#endif