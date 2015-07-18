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
<ctype.h>          0/14 (ISO C), 0/16 (POSIX)
<errno.h>          **Implemented** [2]_
<fenv.h>           Under consideration
<float.h>          **Freestanding**
<inttypes.h>       Under consideration
<iso646.h>         **Freestanding**
<limits.h>         **Freestanding**
<locale.h>         **Implemented** [6]_
<math.h>           11/69 (ISO C), 0/6 (POSIX)
<setjmp.h>         Under consideration
<signal.h>         Under consideration
<stdalign.h>       **Freestanding**
<stdarg.h>         **Freestanding**
<stdatomic.h>      **Freestanding** [3]_
<stdbool.h>        **Freestanding**
<stddef.h>         **Freestanding**
<stdint.h>         **Freestanding**
<stdio.h>          Under consideration
<stdlib.h>         5/39 (ISO C) 2/27 (POSIX) [4]_
<stdnoreturn.h>    **Freestanding**
<string.h>         **Implemented** [5]_
<tgmath.h>         **Freestanding** [3]_
<threads.h>        Under consideration
<time.h>           Under consideration
<uchar.h>          Under consideration
<wchar.h>          Under consideration
<wctype.h>         Under consideration
================== ===============================

.. [1] No debug message is available yet
.. [2] errno is not thread-safe yet
.. [3] In GCC it is available in freestanding environment, though C11 does not require it
.. [4] Allocation families (malloc, free, calloc, realloc, aligned\_alloc, posix\_memalign) are not thread-safe yet. <sys/wait.h> symbols are not included yet.
.. [5] Locale-related (strcoll, strxfrm, strcoll\_l, strxfrm\_l) functions and strsignal are stubbed and will abort on call
.. [6] Only C/POSIX locale is supported. (Affected: strerror\_l)
