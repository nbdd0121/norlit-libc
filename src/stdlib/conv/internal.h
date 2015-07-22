#ifndef _NORLIT_LIBC_STDLIB_CONV_INTERNAL_H
#define _NORLIT_LIBC_STDLIB_CONV_INTERNAL_H

__attribute__((visibility("internal")))
int scan_int(const char * restrict nptr, char ** restrict endptr, int base, unsigned long long* ret);

__attribute__((visibility("internal")))
const char* scan_float(const char* ptr, double* data);

__attribute__((visibility("internal")))
const char* scan_space(const char* str);

#endif