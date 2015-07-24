#ifndef _NORLIT_LIBC_ICONV_H
#define _NORLIT_LIBC_ICONV_H

#define __need_size_t
#include <stddef.h>

#include <norlit/header/start.h>
typedef void* iconv_t;

size_t  iconv(iconv_t, char **__restrict, size_t *__restrict,
              char **__restrict, size_t *__restrict);
int     iconv_close(iconv_t);
iconv_t iconv_open(const char *, const char *);
#include <norlit/header/end.h>

#endif