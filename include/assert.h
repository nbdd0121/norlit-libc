#ifndef _NORLIT_LIBC_ASSERT_H
#define _NORLIT_LIBC_ASSERT_H

#define static_assert _Static_assert

_Noreturn
void __norlit_libc_assertion_failure(const char *file, int line, const char *func, const char *expr);

#endif

#ifdef assert
#undef
#endif

#ifdef NDEBUG
#define assert(ignore) ((void)0)
#else
#define assert(cond) ((cond)?(void)0:__norlit_libc_assertion_failure(__FILE__, __LINE__, __func__, #cond))
#endif
