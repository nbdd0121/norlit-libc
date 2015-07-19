#include <stdint.h>

#if UINTPTR_MAX == UINT64_MAX
#error x64 not supported yet
#else
__asm__(
    ".global longjmp\n"
    ".global _longjmp\n"
    ".type longjmp,@function\n"
    ".type _longjmp,@function\n"
    "longjmp:\n"
    "_longjmp:\n"
    "	mov  4(%esp),%edx\n"
    "	mov  8(%esp),%eax\n"
    "	test    %eax,%eax\n"
    "	jnz 1f\n"
    "	inc     %eax\n"
    "1:\n"
    "	mov   (%edx),%ebx\n"
    "	mov  4(%edx),%esi\n"
    "	mov  8(%edx),%edi\n"
    "	mov 12(%edx),%ebp\n"
    "	mov 16(%edx),%esp\n"
    "	mov 20(%edx),%ecx\n"
    "	jmp *%ecx\n"
);
#endif