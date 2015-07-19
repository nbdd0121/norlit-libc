#include <stdint.h>

#if UINTPTR_MAX == UINT64_MAX
__asm__(
    ".section .init				\n"
    ".globl   _init				\n"
    ".type    _init,@function	\n"
    "_init:						\n"
    "	pushq %rbp				\n"
    "	movq  %rsp, %rbp		\n"
    ".section .fini				\n"
    ".globl   _fini				\n"
    ".type    _fini,@function	\n"
    "_fini:						\n"
    "	pushq %rbp				\n"
    "	movq  %rsp, %rbp		\n"
);
#else
__asm__(
    ".section .init				\n"
    ".globl   _init				\n"
    ".type    _init,@function	\n"
    "_init:						\n"
    "	pushl %ebp				\n"
    "	movl  %esp, %ebp		\n"
    ".section .fini				\n"
    ".globl   _fini				\n"
    ".type    _fini,@function	\n"
    "_fini:						\n"
    "	pushl %ebp				\n"
    "	movl  %esp, %ebp		\n"
);
#endif
