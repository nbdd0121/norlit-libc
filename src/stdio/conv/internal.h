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

#ifndef _NORLIT_LIBC_STDIO_CONV_INTERNAL_H
#define _NORLIT_LIBC_STDIO_CONV_INTERNAL_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

/**
 * f: file to be scanned
 * strlen: length of str
 * data: output, will *not* be cleared before use
 * overflow: will be incremented for every one digit overflown
 * base: radix
 */
__attribute__((visibility("internal")))
int scan_decimal_f(FILE* f, int maxlen, unsigned long long* data, int* len, int* overflow, int base);

__attribute__((visibility("internal")))
int scan_space_f(FILE* f);

__attribute__((visibility("internal")))
int scan_string_f(FILE* f, int maxlen, char* str);

__attribute__((visibility("internal")))
int scan_int_f(FILE* f, int maxlen, int base, unsigned long long* ret, int* sign);

__attribute__((visibility("internal")))
int scan_float_f(FILE* f, int maxlen, double* data);

// This struct is the diy_fp in Florian Loitsch's paper
typedef struct {
	uint64_t frac;
	int16_t exp;
} LongDouble;

__attribute__((visibility("internal")))
uint8_t count_leading_zeros(uint64_t);

__attribute__((visibility("internal")))
LongDouble construct_long_double(double val);

__attribute__((visibility("internal")))
uint8_t count_digits(uint64_t n);

__attribute__((visibility("internal")))
void desemble_double(double v, uint64_t* s, int* n, int* k);

__attribute__((visibility("internal")))
double assemble_double(uint64_t s, int n, int k);

__attribute__((visibility("internal")))
double assemble_double_hex(uint64_t s, int n, int k);

#endif