#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include "../../stdlib/conv/internal.h"

enum {
	FLAG_LEFT = 1,
	FLAG_PLUS = 2,
	FLAG_SPACE = 4,
	FLAG_ALT_FORM = 8,
	FLAG_ZERO = 16,
	FLAG_LITTLE = 32,
	FLAG_THOUSANDS = 64,
};

static int formatUnsigned(uintmax_t num, char *str, uint8_t radix, int flags) {
	const char *index = (flags & FLAG_LITTLE) ? "0123456789abcdefghijklmnopqrstuvwxyz" : "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i = 0;
	while (num) {
		if ((flags & FLAG_THOUSANDS) && i % 4 == 3)
			str[i++] = ',';
		str[i++] = index[num % radix];
		num /= radix;
	}
	for (int j = 0; j < i / 2; j++) {
		char temp = str[j];
		str[j] = str[i - 1 - j];
		str[i - 1 - j] = temp;
	}
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

static void reduceSignificantFigures(uint64_t* s, int* n, int* k, int targetFigure, int radix) {
	uint64_t val = *s;
	int power = *n;
	int sigFig = *k;
	if (targetFigure < 0) {
		*s = 0;
		*n = 1;
		*k = 1;
		return;
	}
	while (sigFig > targetFigure + 1) {
		val /= radix;
		sigFig--;
	}
	if (sigFig > targetFigure) {
		val = (val + radix / 2) / radix;
		sigFig--;

		// Dealing with carry
		//   Ex. (5 + 5) / 10 = 1
		power -= sigFig;
		sigFig = 0;

		uint64_t valdup = val;
		while (valdup) {
			valdup /= radix;
			sigFig++;
			power++;
		}
	}

	*s = val;
	*n = power;
	*k = sigFig;
}

static int formatDouble(FILE* f, char* buffer, int format, int flags, int width, int precision, double val) {
	bool upperCase = isupper(format);
	format = tolower(format);

	bool neg = signbit(val);

	if (!isfinite(val)) {
		bool nanFlag = isnan(val);
		int len = (neg || (flags & (FLAG_PLUS | FLAG_SPACE))) + nanFlag ? 3 : 8;
		if (width > len && !(flags & FLAG_LEFT)) if (pad(f, "        ", width - len)) return EOF;

		if (neg) {
			if (fputc('-', f)) return EOF;
		} else if (flags & FLAG_PLUS) {
			if (fputc('+', f)) return EOF;
		} else if (flags & FLAG_SPACE) {
			if (fputc(' ', f)) return EOF;
		}

		if (nanFlag) {
			if (!fwrite("nanNAN" + upperCase * 3, 3, 1, f)) return EOF;
		} else {
			if (!fwrite("infinityINFINITY" + upperCase * 8, 8, 1, f)) return EOF;
		}

		if (width > len && (flags & FLAG_LEFT)) if (pad(f, "        ", width - len)) return EOF;
		return width > len ? width : len;
	}

	if (neg) {
		val = -val;
	}

	uint64_t s; int n; int k;

	int len = 0;

	if (format == 'a') {
		LongDouble pack = construct_long_double(val);
		s = pack.frac;
		n = pack.exp;

		s <<= n % 4;
		n /= 4;

		while (!(s & 0xF)) {
			s >>= 4;
			n++;
		}

		k = 64 / 4 - count_leading_zeros(s) / 4;
		n += k;

		if (precision == -1) {
			precision = k - 1;
		} else {
			reduceSignificantFigures(&s, &n, &k, precision + 1, 16);
		}

		len = 6 + precision + count_digits(abs(n - 1) * 4);
	} else {
		if (val != 0) {
			desemble_double(val, &s, &n, &k);
		} else {
			n = 1;
			k = 1;
		}

		if (precision == -1)
			precision = 6;

		if (format == 'g') {
			if (precision == 0) precision = 1;
			if (precision > n - 1 && n - 1 >= -4) {
				format = 'f';
				precision -= n;
			} else {
				precision--;
			}
		}

		if (format == 'f') {
			reduceSignificantFigures(&s, &n, &k, n + precision, 10);
			len = (n > 0 ? n : 1) + precision + 1;
		} else {
			reduceSignificantFigures(&s, &n, &k, precision + 1, 10);
			len = 4 + precision + count_digits(abs(n - 1));
		}
	}

	if (precision == 0 && !(flags & FLAG_ALT_FORM)) {
		precision = -1;
		len--;
	}

	len += (neg || (flags & (FLAG_PLUS | FLAG_SPACE)));

	if (width > len && !(flags & FLAG_LEFT) && !(flags & FLAG_ZERO))
		if (pad(f, "        ", width - len)) return EOF;

	if (neg) {
		if (fputc('-', f)) return EOF;
	} else if (flags & FLAG_PLUS) {
		if (fputc('+', f)) return EOF;
	} else if (flags & FLAG_SPACE) {
		if (fputc(' ', f)) return EOF;
	}

	if (width > len && !(flags & FLAG_LEFT) && (flags & FLAG_ZERO))
		if (pad(f, "00000000", width - len)) return EOF;


	if (format == 'a') {
		if (fputc('0', f)) return -1;
		if (fputc(upperCase ? 'X' : 'x', f)) return -1;

		formatUnsigned(s, buffer, 16, upperCase ? 0 : FLAG_LITTLE);

		if (fputc(*buffer, f)) return -1;
		if (precision != -1) {
			if (fputc('.', f)) return -1;
			if (!fwrite(buffer + 1, k - 1, 1, f)) return -1;
			if (pad(f, "00000000", precision - (k - 1))) return -1;
		}
		if (fputc(upperCase ? 'P' : 'p', f)) return -1;
		n--;
		if (n < 0) {
			if (fputc('-', f)) return -1;
			n = -n;
		} else {
			if (fputc('+', f)) return -1;
		}
		if (n != 0) {
			int explen = formatUnsigned(n * 4, buffer, 10, 0);
			if (!fwrite(buffer, explen, 1, f)) return -1;
		} else {
			if (fputc('0', f)) return -1;
		}
	} else {
		if (s != 0) {
			formatUnsigned(s, buffer, 10, 0);
		} else {
			buffer[0] = '0';
		}

		if (format == 'f') {
			if (n > 0) {
				if (n >= k) {
					if (!fwrite(buffer, k, 1, f)) return -1;
					if (pad(f, "00000000", n - k)) return -1;
					if (precision == -1) goto ret;
					if (fputc('.', f)) return -1;
					if (pad(f, "00000000", precision)) return -1;
				} else {
					if (!fwrite(buffer, n, 1, f)) return -1;
					if (precision == -1) goto ret;
					if (fputc('.', f)) return -1;
					if (!fwrite(buffer + n, k - n, 1, f)) return -1;
					if (pad(f, "00000000", precision - (k - n))) return -1;
				}
			} else {
				if (fputc('0', f)) return -1;
				if (fputc('.', f)) return -1;
				if (pad(f, "00000000", -n)) return -1;
				if (!fwrite(buffer, k, 1, f)) return -1;
				if (pad(f, "00000000", precision - (k - n))) return -1;
			}
		} else {
			if (fputc(*buffer, f)) return -1;
			if (precision != -1) {
				if (fputc('.', f)) return -1;
				if (!fwrite(buffer + 1, k - 1, 1, f)) return -1;
				if (pad(f, "00000000", precision - (k - 1))) return -1;
			}
			if (fputc(upperCase ? 'E' : 'e', f)) return -1;
			n--;
			if (n < 0) {
				if (fputc('-', f)) return -1;
				n = -n;
			} else {
				if (fputc('+', f)) return -1;
			}
			if (n != 0) {
				int explen = formatUnsigned(n, buffer, 10, 0);
				if (!fwrite(buffer, explen, 1, f)) return -1;
			} else {
				if (fputc('0', f)) return -1;
			}
		}
	}

	if (width > len && (flags & FLAG_LEFT))
		if (pad(f, "        ", width - len)) return EOF;

ret:
	return width > len ? width : len;
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
				case '\'': flags |= FLAG_THOUSANDS; continue;
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

		char buf[sizeof(intmax_t) * 4];

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
				bodyLen = formatUnsigned(val, buf, 10, flags);
				if (precision == -1)
					precision = 1;
				break;
			}
			case 'p': {
				prefix = "0x";
				prefixLen = 2;
				uintmax_t val = (uintptr_t)va_arg(args, void*);
				bodyLen = formatUnsigned(val, buf, 16, 0);
				if (precision < (int)sizeof(uintptr_t) * 2)
					precision = sizeof(uintptr_t) * 2;
				break;
			}
			case 'o':
				base = 8;
				flags &= ~FLAG_THOUSANDS;
				if (flags & FLAG_ALT_FORM) {
					prefix = "0";
					prefixLen = 1;
				}
				goto unsignedFormatting;
			case 'x':
				flags |= FLAG_LITTLE;
			case 'X':
				base = 16;
				flags &= ~FLAG_THOUSANDS;
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
			case 'A': {
				int ret = formatDouble(f, buf, *format, flags, width, precision, qualifier == 'L' ? (double)va_arg(args, long double) : va_arg(args, double));
				if (ret == -1)
					return EOF;
				totalCount += ret;
				continue;
			}
			case 'c': {
				if (qualifier != 'l') {
					buf[0] = (char)va_arg(args, int);
					bodyLen = 1;
					// 0 for %c is ignored
					flags &= ~FLAG_ZERO;
					precision = -1;
					break;
				}
			}
			case 'C':
				assert(0);
			case 's': {
				if (qualifier != 'l') {
					body = va_arg(args, char*);
					if (!body) body = "(null)";
					bodyLen = precision == -1 ? strlen(body) : strnlen(body, precision);
					// 0 for %s is ignored
					flags &= ~FLAG_ZERO;
					precision = -1;
					break;
				}
			}
			case 'S':
				assert(0);
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