#include "internal.h"
#include <limits.h>
#include <errno.h>

int scan_int_f(FILE* f, int base, unsigned long long* ret, int* sign) {
	int len = 0;
	int ch = fgetc(f);
	int neg = 0;
	if (ch == '-') {
		len++;
		neg = 1;
	} else if (ch != '+') {
		ungetc(ch, f);
	}

	if (base == 0) {
		ch = fgetc(f);
		if (ch == '0') {
			len++;
			ch = fgetc(f);
			if (ch == 'x' || ch == 'X') {
				len++;
				base = 16;
			} else {
				ungetc(ch, f);
				base = 8;
			}
		} else {
			ungetc(ch, f);
			base = 10;
		}
	} else if (base == 16) {
		ch = fgetc(f);
		if (ch == '0') {
			len++;
			ch = fgetc(f);
			if (ch == 'x' || ch == 'X') {
				len++;
			} else {
				ungetc(ch, f);
			}
		} else {
			ungetc(ch, f);
		}
	} else if (base < 2 || base > 36) {
		*ret = 0;
		*sign = -EINVAL;
		return 0;
	}

	int overflow = 0;
	len += scan_decimal_f(f, ret, NULL, &overflow, base);
	if (overflow) {
		*ret = neg;
		*sign = -ERANGE;
		return 0;
	}
	*sign = neg;
	return len;
}