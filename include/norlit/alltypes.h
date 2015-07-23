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

#ifdef __need_va_list
#undef __need_va_list
#include <stdarg.h>
#endif

#if defined(__need_size_t) || defined(__need_wchar_t)
#include <stddef.h>
#endif

#include <norlit/header/end.h>