#if !defined(__need_off_t) && \
	!defined(__need_size_t) && !defined(__need_ssize_t)
#ifndef _NORLIT_SYS_TYPES_H
#define _NORLIT_SYS_TYPES_H
#define __need_off_t
#define __need_size_t
#define __need_ssize_t
#endif
#endif

#include <stdint.h>

#ifdef __need_off_t
#undef __need_off_t
typedef int64_t off_t;
#endif

#ifdef __need_ssize_t
#undef __need_ssize_t
typedef intptr_t ssize_t;
#endif

#ifdef __need_size_t
#include <stddef.h>
#endif

