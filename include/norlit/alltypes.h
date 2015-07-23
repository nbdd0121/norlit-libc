#include <norlit/header/start.h>

#ifdef __need_FILE
#undef __need_FILE
struct _FILE;
typedef struct _FILE FILE;
#endif

#ifdef __need_locale_t
#undef __need_locale_t
typedef void* locale_t;
#endif

#ifdef __need_mbstate_t
#undef __need_mbstate_t
typedef int mbstate_t;
#endif

#ifdef __need_wctype_t
#undef __need_wctype_t
typedef int wctype_t;
#endif

#ifdef __need_wint_t
#undef __need_wint_t
typedef int wint_t;
#endif

#ifdef __need_clock_t
#undef __need_clock_t
typedef __UINT64_TYPE__ clock_t;
#endif

#ifdef __need_time_t
#undef __need_time_t
typedef __UINT64_TYPE__ time_t;
#endif

#ifdef __need_clockid_t
#undef __need_clockid_t
typedef int clockid_t;
#endif

#ifdef __need_timer_t
#undef __need_timer_t
typedef int timer_t;
#endif

#ifdef __need_pid_t
#undef __need_pid_t
typedef int pid_t;
#endif

#ifdef __need_va_list
#undef __need_va_list
#include <stdarg.h>
#endif

#if defined(__need_size_t) || defined(__need_wchar_t)
#include <stddef.h>
#endif

#include <norlit/header/end.h>