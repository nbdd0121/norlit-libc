Summary
=======

norlit-libc is desinged to comform to ISO C standar as well as those
defined POSIX standard in the standard headers. norlit-libc do not 
intend to support other POSIX-specific headers, but may create stubs
for them since they are not available in freestanding environemnt.

================== ===============================
Header               Status
================== ===============================
<assert.h>         **Implemented** [1]_
<complex.h>        Under consideration
<ctype.h>          **Implemented** [4]_
<errno.h>          **Implemented**
<fenv.h>           Under consideration
<float.h>          **Freestanding**
<inttypes.h>       Under consideration
<iso646.h>         **Freestanding**
<limits.h>         **Freestanding**
<locale.h>         **Implemented**
<math.h>           11/69 (ISO C), 0/6 (POSIX)
<setjmp.h>         Under consideration
<signal.h>         Under consideration
<stdalign.h>       **Freestanding**
<stdarg.h>         **Freestanding**
<stdatomic.h>      **Freestanding** [2]_
<stdbool.h>        **Freestanding**
<stddef.h>         **Freestanding**
<stdint.h>         **Freestanding**
<stdio.h>          Under consideration
<stdlib.h>         13/39 (ISO C) 2/27 (POSIX)
<stdnoreturn.h>    **Freestanding**
<string.h>         **Implemented** [3]_
<tgmath.h>         **Freestanding** [2]_
<threads.h>        Under consideration
<time.h>           Under consideration
<uchar.h>          Under consideration
<wchar.h>          Under consideration
<wctype.h>         Under consideration
================== ===============================

.. [1] No debug message is available yet
.. [2] In GCC it is available in freestanding environment, though C11 does not require it
.. [3] strsignal are stubbed and will abort on call
.. [4] Unicode support is under consideration, currently non-ASCII code points will cause these functions to abort.

Thread-safety
=============

norlit-libc currently has no need for multi-threading, so thread-safe is not concerned. However, in order to aid furture development, non-thread-safe functions and variables are listed.

- errno
- uselocale
- strtok
- malloc, free, calloc, realloc, aligned_alloc, posix_memalign


Locale
======

norlit-libc currently has no need for locale, so only C/POSIX locale is supported. When implementing norlit-libc, functions use current locale will be redirected to \*_l functions by first retrieving locale by uselocale((locale_t)0). \*_l will do the job instead. Here is the list of \*_l functions

- strcoll_l, strxfrm_l, strerror_l
