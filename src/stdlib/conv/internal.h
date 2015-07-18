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
__attribute__((visibility("hidden")))
const char* scan_decimal(const char* str, size_t strlen, uint64_t* data, int* overflow, int base);

__attribute__((visibility("hidden")))
const char* scan_space(const char* str);

__attribute__((visibility("hidden")))
int scan_int(const char * restrict nptr, char ** restrict endptr, int base, uint64_t* ret);

#endif