#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <inttypes.h>

enum {
	FLAG_LEFT = 1,
	FLAG_PLUS = 2,
	FLAG_SPACE = 4,
	FLAG_ALT_FORM = 8,
	FLAG_ZERO = 16,
	FLAG_LITTLE = 32
};

static int formatUnsigned(uintmax_t num, char *str, uint8_t radix, int flags) {
	const char *index = (flags & FLAG_LITTLE) ? "0123456789abcdefghijklmnopqrstuvwxyz" : "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i = 0;
	while (num) {
		str[i++] = index[num % radix];
		num /= radix;
	}
	for (int j = 0; j < i / 2; j++) {
		char temp = str[j];
		str[j] = str[i - 1 - j];
		str[i - 1 - j] = temp;
	}
	str[i] = 0;
	return i;
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

static int pad(FILE* f, char pad[8], int count) {
	if (count == 0) return 0;
	while (count > 8) {
		if (!fwrite(pad, 8, 1, f))return EOF;
		count -= 8;
	}
	if (!fwrite(pad, count, 1, f))return EOF;
	return 0;
}

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

static intmax_t loadQualiferD(va_list* arg, int qualifier) {
	switch (qualifier) {
		case 'H':
			return va_arg(*arg, int);
		case 'h':
			return va_arg(*arg, int);
		case 'l':
			return va_arg(*arg, long);
		case 'L':
			return va_arg(*arg, long long);
		case 'j':
			return va_arg(*arg, intmax_t);
		case 'z':
			return va_arg(*arg, size_t);
		case 't':
			return va_arg(*arg, ptrdiff_t);
		default:
			return va_arg(*arg, int);
	}
}

static uintmax_t loadQualiferU(va_list* arg, int qualifier) {
	switch (qualifier) {
		case 'H':
			return va_arg(*arg, int);
		case 'h':
			return va_arg(*arg, int);
		case 'l':
			return va_arg(*arg, unsigned long);
		case 'L':
			return va_arg(*arg, unsigned long long);
		case 'j':
			return va_arg(*arg, uintmax_t);
		case 'z':
			return va_arg(*arg, size_t);
		case 't':
			return va_arg(*arg, ptrdiff_t);
		default:
			return va_arg(*arg, unsigned);
	}
}


int vfprintf(FILE * restrict f, const char * restrict format, va_list args) {
	size_t totalCount = 0;

	for (;; format++) {
		// Skip ordinary characters
		const char* endptr = strchr(format, '%');
		if (!endptr) {
			size_t rest = strlen(format);
			if (rest && !fwrite(format, rest, 1, f)) return EOF;
			return totalCount + rest;
		}
		if (!fwrite(format, endptr - format, 1, f)) return EOF;
		totalCount += endptr - format;
		format = endptr;

		// %% -> %
		if (format[1] == '%') {
			if (fputc('%', f)) return EOF;
			totalCount++;
			format++;
			continue;
		}

		int flags = 0;
		while (1) {
			switch (*(++format)) {
				case '-': flags |= FLAG_LEFT; continue;
				case '+': flags |= FLAG_PLUS; continue;
				case ' ': flags |= FLAG_SPACE; continue;
				case '#': flags |= FLAG_ALT_FORM; continue;
				case '0': flags |= FLAG_ZERO; continue;
			}
			break;
		}

		int width = -1;
		if (*format == '*') {
			width = va_arg(args, int);
			if (width < 0) {
				flags |= FLAG_LEFT;
				width = -width;
			}
			format++;
		} else if (*format >= '0' && *format <= '9') {
			width = scanint((const char**)&format);
		}

		int precision = -1;
		if (*format == '.') {
			format++;
			if (*format == '*') {
				precision = va_arg(args, int);
				if (precision < 0) {
					precision = -1;
				}
				format++;
			} else if (*format >= '0' && *format <= '9') {
				precision = scanint((const char**)&format);
			} else {
				precision = 0;
			}
		}

		// Ignore some flags in certain situtation
		if (flags & FLAG_PLUS) {
			flags &= ~FLAG_SPACE;
		}
		if (flags & FLAG_LEFT) {
			flags &= ~FLAG_ZERO;
		}
		if (precision != -1) {
			flags &= ~FLAG_ZERO;
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

		char buf[sizeof(intmax_t) * 3];

		char *prefix = NULL;
		int   prefixLen = 0;
		char *body = buf;
		int   bodyLen = 0;

		uint8_t base;

		switch (*format) {
			case 'd':
			case 'i': {
				intmax_t val = loadQualiferD(&args, qualifier);
				if (val < 0) {
					prefix = "-";
					prefixLen = 1;
					val = -val;
				} else if (flags & FLAG_SPACE) {
					prefix = " ";
					prefixLen = 1;
				} else if (flags & FLAG_PLUS) {
					prefix = "+";
					prefixLen = 1;
				}
				bodyLen = formatUnsigned(val, buf, 10, 0);
				if (precision == -1)
					precision = 1;
				break;
			}
			case 'p':
				base = 16;
				prefix = "0x";
				prefixLen = 2;
				if (precision < (int)sizeof(uintptr_t) * 2)
					precision = sizeof(uintptr_t) * 2;
				goto unsignedFormatting;
			case 'o':
				base = 8;
				if (flags & FLAG_ALT_FORM) {
					prefix = "0";
					prefixLen = 1;
				}
				goto unsignedFormatting;
			case 'x':
				flags |= FLAG_LITTLE;
			case 'X':
				base = 16;
				if (flags & FLAG_ALT_FORM) {
					prefix = flags & FLAG_LITTLE ? "0x" : "0X";
					prefixLen = 2;
				}
				goto unsignedFormatting;
			case 'u':
				base = 10;
unsignedFormatting: {
					uintmax_t val = loadQualiferU(&args, qualifier);
					bodyLen = formatUnsigned(val, buf, base, flags);
					if (precision == -1)
						precision = 1;
				}
				break;
			case 'f':
			case 'F':
			case 'e':
			case 'E':
			case 'g':
			case 'G':
			case 'a':
			case 'A':
				assert(0);
				break;
			case 'c': {
				if (qualifier == 'l') {
					assert(0);
				}
				buf[0] = (char)va_arg(args, int);
				bodyLen = 1;
				// 0 for %c is ignored
				flags &= ~FLAG_ZERO;
				precision = -1;
				break;
			}
			case 's': {
				if (qualifier == 'l') {
					assert(0);
				}
				body = va_arg(args, char*);
				if (!body) body = "(null)";
				bodyLen = precision == -1 ? strlen(body) : strnlen(body, precision);
				// 0 for %s is ignored
				flags &= ~FLAG_ZERO;
				precision = -1;
				break;
			}
			case 'n':
				storeQualifierD(va_arg(args, void*), qualifier, totalCount);
				continue;
			default:
				// Undefined behavior
				//   Write as is
				if (fputc('%', f) || fputc(*format, f)) return EOF;
				totalCount += 2;
				continue;
		}

		// Calculate zeros according to precision.
		//   If precision == -1, we are not dealing with numbers
		int zeroLPadCount = 0;
		if (precision != -1) {
			zeroLPadCount = bodyLen > precision ? 0 : precision - bodyLen;
		}

		// Calculate paddings
		int currentWidth = bodyLen + prefixLen + zeroLPadCount;
		int padCount = currentWidth > width ? 0 : width - currentWidth;
		int spaceLPadCount = (flags & FLAG_LEFT) || (flags & FLAG_ZERO) ? 0 : padCount;
		zeroLPadCount += flags & FLAG_ZERO ? padCount : 0;
		int spaceRPadCount = flags & FLAG_LEFT ? padCount : 0;

		if (
		    pad(f, "        ", spaceLPadCount) ||
		    (prefixLen && !fwrite(prefix, 1, prefixLen, f)) ||
		    pad(f, "00000000", zeroLPadCount) ||
		    (bodyLen && !fwrite(body, 1, bodyLen, f)) ||
		    pad(f, "        ", spaceRPadCount)
		)
			return EOF;

		totalCount += currentWidth + padCount;
	}
}