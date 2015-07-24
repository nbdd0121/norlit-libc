/*
 * Copyright (c) 2015, Gary Guo 
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met: 
 * 
 *  * Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer. 
 *  * Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY 
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
 * DAMAGE. 
 */

#include <stdint.h>
#include <assert.h>

#if UINTPTR_MAX == UINT64_MAX
void longjmp(void) {
    assert(0);
}
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