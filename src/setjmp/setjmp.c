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