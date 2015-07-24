#include <stdint.h>
#include <assert.h>

#if UINTPTR_MAX == UINT64_MAX
void setjmp(void) {
    assert(0);
}
#else
__asm__(
    ".global setjmp\n"
    ".global _setjmp\n"
    ".type setjmp,@function\n"
    ".type _setjmp,@function\n"
    "setjmp:\n"
    "_setjmp:\n"
    "   mov 4(%esp),   %eax \n"
    "   mov   %ebx,   (%eax)\n"
    "   mov   %esi,  4(%eax)\n"
    "   mov   %edi,  8(%eax)\n"
    "   mov   %ebp, 12(%eax)\n"
    "   lea 4(%esp),   %ecx \n"
    "   mov   %ecx, 16(%eax)\n"
    "   mov  (%esp),   %ecx \n"
    "   mov   %ecx, 20(%eax)\n"
    "   xor   %eax,    %eax \n"
    "   ret"
);
#endif