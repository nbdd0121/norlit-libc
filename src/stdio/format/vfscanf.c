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

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include <limits.h>

#include "../conv/internal.h"

#define _limit(val, min, max) (val>max?max:(val<min?min:val))
#define limit(val, limname) _limit(val, limname##_MIN, limname##_MAX)
#define _ulimit(val, max) (val>max?max:val)
#define ulimit(val, limname) _ulimit(val, limname##_MAX)

__attribute__((visibility("internal")))
void storeQualifierD(void* ptr, int qualifier, intmax_t data) {
	switch (qualifier) {
		case 'H':
			*(signed char*)ptr = (signed char)limit(data, SCHAR);
			break;
		case 'h':
			*(short*)ptr = (short)limit(data, SHRT);
			break;
		case 'l':
			*(long*)ptr = (long)limit(data, LONG);
			break;
		case 'L':
			*(long long*)ptr = (long long)limit(data, LLONG);
			break;
		case 'j':
			*(intmax_t*)ptr = data;
			break;
		case 'z':
			*(ssize_t*)ptr = (ssize_t)limit(data, INTPTR);
			break;
		case 't':
			*(ptrdiff_t*)ptr = (ptrdiff_t)limit(data, INTPTR);
			break;
		default:
			*(int*)ptr = (int)limit(data, INT);
			break;
	}
}

static void storeQualifierU(void* ptr, int qualifier, uintmax_t data) {
	switch (qualifier) {
		case 'H':
			*(unsigned char*)ptr = (unsigned char)ulimit(data, UCHAR);
			break;
		case 'h':
			*(unsigned short*)ptr = (unsigned short)ulimit(data, USHRT);
			break;
		case 'l':
			*(unsigned long*)ptr = (unsigned long)ulimit(data, ULONG);
			break;
		case 'L':
			*(unsigned long long*)ptr = (unsigned long long)ulimit(data, ULLONG);
			break;
		case 'j':
			*(uintmax_t*)ptr = data;
			break;
		case 'z':
			*(size_t*)ptr = (size_t)ulimit(data, UINTPTR);
			break;
		case 't':
			*(ptrdiff_t*)ptr = (ptrdiff_t)limit(data, INTPTR);
			break;
		default:
			*(unsigned int*)ptr = (unsigned int)ulimit(data, UINT);
			break;
	}
}

static void storeQualifierF(void* ptr, int qualifier, double data) {
	switch (qualifier) {
		case 'l':
			*(double*)ptr = (double)data;
			break;
		case 'L':
			*(long double*)ptr = (long double)data;
			break;
		default:
			*(float*)ptr = (float)data;
			break;
	}
}

__attribute__((visibility("internal")))
int scanint(const char **ptr) {
	int res = 0;
	const char *p = *ptr;
	while (*p >= '0' && *p <= '9')
		res = res * 10 + (*(p++) - '0');
	*ptr = p;
	return res;
}

int vfscanf(FILE * restrict f, const char * restrict format, va_list args) {
	if (f == stdin) {
		fflush(stdout);
	}

	size_t totalCount = 0;
	int processedCount = 0;
	int ch;

	char scanset[256];
	void* target;
	int width;
	bool alloc;

	uint8_t base;
	int qualifier;

	for (; *format; format++) {
		// Match detect whitespace
		if (isspace(*format)) {
			while (isspace(format[1])) format++;
			totalCount += scan_space_f(f);
			continue;
		}

		// Match ordinary characters
		if (*format != '%' || format[1] == '%') {
			if ((ch = fgetc(f)) == *format) {
				totalCount++;
				continue;
			}
			ungetc(ch, f);
			goto fail;
		}
		format++;

		if (*format == '*') {
			format++;
			target = NULL;
		} else {
			target = va_arg(args, void*);
		}

		if (*format >= '0' && *format <= '9') {
			width = scanint((const char**)&format);
		} else {
			width = -1;
		}

		// POSIX memory allocation specifier
		if (*format == 'm') {
			format++;
			alloc = true;
		} else {
			alloc = false;
		}

		if (!target) {
			alloc = false;
		}

		switch (*format) {
			case 'h':
				if (*(++format) == 'h') {
					format++;
					qualifier = 'H';
				} else {
					qualifier = 'h';
				}
				break;
			case 'l':
				if (*(++format) == 'l') {
					format++;
					qualifier = 'L';
				} else {
					qualifier = 'l';
				}
				break;
			case 'j':
			case 'z':
			case 't':
			case 'L': qualifier = *(format++);
			default: qualifier = 0;
		}

		switch (*format) {
			case 'c':
				if (width < 1) width = 1;
				break;
			case '[':
				break;
			case 'n':
				storeQualifierD(target, qualifier, totalCount);
				continue;
			default:
				totalCount += scan_space_f(f);
				break;
		}

		switch (*format) {
			case 'd':
				base = 10;
				if (0) {
				case 'i':
					base = 0;
				}
				{
					uintmax_t ret = 0;
					int sign;
					int len = scan_int_f(f, width == -1 ? INT_MAX : width, base, &ret, &sign);
					if (len == 0) {
						goto fail;
					}
					totalCount += len;
					if (sign < 0) {
						ret = ret ? INTMAX_MIN : INTMAX_MAX;
					} else if (sign) {
						if (ret > -(uintmax_t)INTMAX_MIN) {
							ret = INTMAX_MIN;
						} else {
							ret = -ret;
						}
					} else if (ret > INTMAX_MAX) {
						ret = INTMAX_MAX;
					}
					if (target)
						storeQualifierD(target, qualifier, ret);
					break;
				}
			case 'p':
			case 'x':
			case 'X':
				base = 16;
				if (0) {
				case 'o':
					base = 8;
				}
				if (0) {
				case 'u':
					base = 10;
				}
				{
					uintmax_t ret = 0;
					int sign;
					int len = scan_int_f(f, width == -1 ? INT_MAX : width, base, &ret, &sign);
					if (len == 0) {
						goto fail;
					}
					if (sign < 0) {
						ret = ULLONG_MAX;
					}
					if (target) {
						if (*format == 'p')
							*(void**)target = (void*)(uintptr_t)ret;
						else
							storeQualifierU(target, qualifier, ret);
					}
					break;
				}
			case 'f':
			case 'F':
			case 'e':
			case 'E':
			case 'g':
			case 'G':
			case 'a':
			case 'A': {
				double val;
				int len = scan_float_f(f, width == -1 ? INT_MAX : width, &val);
				if (len == 0) {
					goto fail;
				}
				totalCount += len;
				if (target)
					storeQualifierF(target, qualifier, val);
				break;
			}
			case 'c': {
				if (qualifier != 'l') {
					memset(scanset, 1, 256);
					goto scanstring;
				}
			}
			case 'C':
				assert(0);
			case 's': {
				if (qualifier != 'l') {
					memset(scanset, 1, 256);
					scanset['\t'] = 0;
					scanset['\n'] = 0;
					scanset['\v'] = 0;
					scanset['\f'] = 0;
					scanset['\r'] = 0;
					scanset[' ' ] = 0;
					goto scanstring;
				}
			}
			case 'S':
				assert(0);
			case '[': {
				bool invert = false;
				if (format[1] == '^') {
					format++;
					invert = true;
				}
				memset(scanset, invert, 256);
				format++;
				do {
					if (!*format) {
						goto format_err;
					}
					if (format[1] == '-' && format[2] != ']') {
						int start = (unsigned char) * format;
						int end = (unsigned char)format[2];
						if (start > end) {
							int tmp = start;
							start = end;
							end = tmp;
						}
						for (int i = start; i <= end; i++) {
							scanset[i] = !invert;
						}
					} else {
						scanset[(unsigned char)*format] = !invert;
					}
				} while (*++format != ']');
			}
scanstring: {
				char* dest;
				int len = 0;

				// if m is set, we need to allocate memory
				if (alloc) {
					if (width == -1) {
						len = 9;
						dest = malloc(10);
					} else {
						dest = malloc(width + 1);
					}
					if (!dest) {
						goto fail;
					}
				} else {
					dest = (char*)target;
				}

				// Scan according to scanset
				int i;
				for (i = 0; width == -1 || i < width; i++) {
					ch = fgetc(f);
					if (ch < 0) {
						if (*format == 'c') {
							goto fail;
						}
						break;
					}
					if (!scanset[ch]) {
						ungetc(ch, f);
						break;
					}

					if (alloc && width == -1 && i >= len) {
						len += 10;
						dest = realloc(dest, len);
						if (!dest)
							goto fail;
					}

					if (dest)
						dest[i] = ch;
				}
				// No trailing '\0' for %c
				if (*format != 'c' && dest)
					dest[i] = 0;
				if (alloc)
					*(char**)target = dest;
				totalCount += i;
				break;
			}
			default:
				goto format_err;
		}

		if (target)
			processedCount++;
	}

	return processedCount;
fail:
	return processedCount ? processedCount : EOF;
format_err:
	errno = EINVAL;
	return processedCount ? processedCount : EOF;
}