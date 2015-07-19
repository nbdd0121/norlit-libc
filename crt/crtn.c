#include <stdint.h>

#if UINTPTR_MAX == UINT64_MAX
__asm__(
    ".section .init \n"
    "	popq	%rbp\n"
    "	ret         \n"
    ".section .fini \n"
    "	popq	%rbp\n"
    "	ret         \n"
);
#else
__asm__(
    ".section .init \n"
    "	popl	%ebp\n"
    "	ret         \n"
    ".section .fini \n"
    "	popl	%ebp\n"
    "	ret         \n"
);
#endif
