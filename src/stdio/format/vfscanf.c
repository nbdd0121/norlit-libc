#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

static void storeQualifierD(void* ptr, int qualifier, intmax_t data) {
	switch (qualifier) {
		case 'H':
			*(signed char*)ptr = (signed char)data;
			break;
		case 'h':
			*(short*)ptr = (short)data;
			break;
		case 'l':
			*(long*)ptr = (long)data;
			break;
		case 'L':
			*(long long*)ptr = (long long)data;
			break;
		case 'j':
			*(intmax_t*)ptr = data;
			break;
		case 'z':
			*(size_t*)ptr = (size_t)data;
			break;
		case 't':
			*(ptrdiff_t*)ptr = (ptrdiff_t)data;
			break;
		default:
			*(int*)ptr = (int)data;
			break;
	}
}

// FIXME: Use existed replacement
static int scanint(const char **ptr) {
	int res = 0;
	const char *p = *ptr;
	while (*p >= '0' && *p <= '9')
		res = res * 10 + (*(p++) - '0');
	*ptr = p;
	return res;
}

int vfscanf(FILE * restrict f, const char * restrict format, va_list args) {
	size_t totalCount = 0;
	int processedCount = 0;
	int ch;

	char scanset[256];
	void* target;
	int width;
	bool alloc;

	for (; *format; format++) {
		// Match detect whitespace
		if (isspace(*format)) {
			while (isspace(format[1])) format++;
			while (isspace(ch = fgetc(f))) totalCount++;
			ungetc(ch, f);
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

		int qualifier = 0;
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
				while (isspace(ch = fgetc(f))) totalCount++;
				ungetc(ch, f);
				break;
		}

		switch (*format) {
			case 'd':
			case 'i': {
				assert(0);
				break;
			}
			case 'p': {
				assert(0);
				break;
			}
			case 'o':
				assert(0);
			case 'x':
			case 'X':
				assert(0);
			case 'u':
				assert(0);
				break;
			case 'f':
			case 'F':
			case 'e':
			case 'E':
			case 'g':
			case 'G':
			case 'a':
			case 'A': {
				assert(0);
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
				int len;

				// if m is set, we need to allocate memory
				if (alloc) {
					if (width == -1) {
						len = 9;
						dest = malloc(10);
					} else {
						dest = malloc(width + 1);
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
	}

	return processedCount;
fail:
	if (ch < 0)
		return EOF;
	return processedCount;
format_err:
	errno = EINVAL;
	return processedCount;
}