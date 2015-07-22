#include "internal.h"
#include <limits.h>
#include <errno.h>

int scan_int_f(FILE* f, int maxlen, int base, unsigned long long* ret, int* sign) {
	int len = 0;

	if (len >= maxlen) return len;
	int ch = fgetc(f);
	int neg = 0;
	if (ch == '-') {
		len++;
		neg = 1;
	} else if (ch != '+') {
		ungetc(ch, f);
	}

	if (base == 0) {
		if (scan_string_f(f, maxlen - len, "0")) {
			printf(")\n");
			len++;
			if (scan_string_f(f, maxlen - len, "X")) {
				len++;
				base = 16;
			} else {
				ungetc(ch, f);
				base = 8;
			}
		} else {
			base = 10;
		}
	} else if (base == 16) {
		if (scan_string_f(f, maxlen - len, "0X")) {
			len += 2;
		}
	} else if (base < 2 || base > 36) {
		*ret = 0;
		*sign = -EINVAL;
		return 0;
	}

	int overflow = 0;
	len += scan_decimal_f(f, maxlen - len, ret, NULL, &overflow, base);
	if (overflow) {
		*ret = neg;
		*sign = -ERANGE;
		return 0;
	}
	*sign = neg;
	return len;
}