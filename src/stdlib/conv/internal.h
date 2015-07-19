#ifndef _NORLIT_LIBC_STDLIB_CONV_INTERNAL_H
#define _NORLIT_LIBC_STDLIB_CONV_INTERNAL_H

#include <stdint.h>
#include <stddef.h>

/**
 * str: string to be scanned
 * strlen: length of str
 * data: output, will *not* be cleared before use
 * overflow: will be incremented for every one digit overflown
 * base: radix
 * return: last char processed + 1
 */
__attribute__((visibility("internal")))
const char* scan_decimal(const char* str, unsigned long long* data, int* len, int* overflow, int base);

__attribute__((visibility("internal")))
const char* scan_space(const char* str);

__attribute__((visibility("internal")))
int scan_int(const char * restrict nptr, char ** restrict endptr, int base, unsigned long long* ret);

__attribute__((visibility("internal")))
void desemble_double(double v, uint64_t* s, int* n, int* k);

__attribute__((visibility("internal")))
double assemble_double(uint64_t s, int n, int k);

__attribute__((visibility("internal")))
double assemble_double_hex(uint64_t s, int n, int k);

__attribute__((visibility("internal")))
const char* scan_float(const char* ptr, double* data);

#endif