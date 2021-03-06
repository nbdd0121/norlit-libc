Summary
=======

norlit-libc is a C library for x86 and x64.

norlit-libc is designed to conform to ISO C standard as well as those
defined POSIX standard in the standard headers. norlit-libc do not 
intend to support other POSIX-specific headers, but may create stubs
for them since they are not available in freestanding environment.

================== ===============================
Header               Status
================== ===============================
<assert.h>         **Implemented**
<complex.h>        **Not supported** [1]_
<ctype.h>          **Implemented**
<errno.h>          **Implemented**
<fenv.h>           Under consideration
<float.h>          **Implemented** [9]_
<inttypes.h>       **Implemented**
<iso646.h>         **Implemented**
<limits.h>         **Implemented** (ISO C)
<locale.h>         **Implemented**
<math.h>           28/69 (ISO C), 0/6 (POSIX) [4]_
<setjmp.h>         **Implemented** (ISO C) 2/4 (POSIX) [8]_
<signal.h>         Stub
<stdalign.h>       **Implemented**
<stdarg.h>         **Implemented**
<stdatomic.h>      **Freestanding** [2]_
<stdbool.h>        **Implemented**
<stddef.h>         **Implemented**
<stdint.h>         **Implemented**
<stdio.h>          **Implemented** (ISO C) [5]_ 4/22 (POSIX)
<stdlib.h>         **Implemented** (ISO C) [3]_ 4/27 (POSIX) [7]_
<stdnoreturn.h>    **Implemented**
<string.h>         **Implemented**
<tgmath.h>         **Freestanding** [2]_
<threads.h>        **Not supported** [1]_
<time.h>           Stub
<uchar.h>          **Not supported** [6]_
<wchar.h>          Stub [6]_
<wctype.h>         **Not supported** [6]_
================== ===============================

.. [1] Conditional features are not in priority
.. [2] In GCC it is available in freestanding environment, though C11 does not require it
.. [3] ``system`` is a stub and will abort on call
.. [4] Floating point numbers-related functions may have larger margin of error than expected
.. [5] remove, rename, tmpfile and tmpnam not supported. POSIX extension to printf and scanf is not yet supported.
.. [6] Intended, but violate the standard
.. [7] long double <-> string conversion is approximated with double <-> string conversion
.. [8] Current there is only x86 support
.. [9] FLT_ROUND and FLT_EVAL_METHOD are not implemented and will abort when used

TODO List
=========

- Macros in errno.h and signal.h should be system dependent, extract them to include/sys in some way
- stdio.h

wchar and uchar
===============

norlit-libc currently has no need for uchar and legacy wchar support. Related functions are defined but not implemented. Here is the list.

- <uchar.h>, <wchar.h> and <wctype.h>
- mblen, mbtowc, wctomb
- mbstowcs, wcstombs
- From <inttypes.h>: wcstoimax, wcstoumax

Thread-safety and reentrancy
============================

norlit-libc currently has no need for multi-threading, so thread-safe is not concerned. If future support for thread-safety is needed, convert all static variables to thread-local storage or add locks to them. Reentrancy support is also not considered currently.

Locale
======

norlit-libc currently has no need for locale, so only C/POSIX locale is supported. When implementing norlit-libc, functions use current locale will be redirected to \*_l functions by first retrieving locale by uselocale((locale_t)0). \*_l will do the job instead. To support multiple locale, simply reimplement all files under src/locale
