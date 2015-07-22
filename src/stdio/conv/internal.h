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