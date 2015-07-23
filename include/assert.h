#ifndef _NORLIT_LIBC_ASSERT_H
#define _NORLIT_LIBC_ASSERT_H

#ifndef __cplusplus
#define static_assert _Static_assert
#endif

#include <norlit/header/start.h>
_Noreturn
void __norlit_libc_assertion_failure(const char *file, int line, const char *func, const char *expr);
#include <norlit/header/end.h>

#endif

#undef assert

#ifdef NDEBUG
#define assert(ignore) ((void)0)
#else
#define assert(cond) ((cond)?(void)0:__norlit_libc_assertion_failure(__FILE__, __LINE__, __func__, #cond))
#endif
