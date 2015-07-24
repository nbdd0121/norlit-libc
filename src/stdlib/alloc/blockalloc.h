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

#ifndef _NORLIT_LIBC_STDLIB_BLOCKALLOC_H
#define _NORLIT_LIBC_STDLIB_BLOCKALLOC_H

#include <stddef.h>

typedef struct allocator_t allocator_t;

__attribute__((visibility("internal")))
allocator_t *allocator_create(void);
__attribute__((visibility("internal")))
void allocator_free(allocator_t *al, void *addr);
__attribute__((visibility("internal")))
void *allocator_malloc(allocator_t *al, size_t size);
__attribute__((visibility("internal")))
void *allocator_calloc(allocator_t *al, size_t nmemb, size_t size);
__attribute__((visibility("internal")))
void *allocator_realloc(allocator_t *al, void *addr, size_t size);
__attribute__((visibility("internal")))
void *allocator_aligned_alloc(allocator_t *al, size_t alignment, size_t size);

__attribute__((visibility("internal")))
allocator_t* allocator_get_global();

#endif