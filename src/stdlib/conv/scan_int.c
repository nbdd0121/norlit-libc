#include "internal.h"
#include <limits.h>
#include <errno.h>

int scan_int(const char * restrict nptr, char ** restrict endptr, int base, uint64_t* ret) {
	nptr = scan_space(nptr);

	int neg = 0;
	if (*nptr == '+') {
		nptr++;
	} else if (*nptr == '-') {
		neg = 1;
		nptr++;
	}

	if (base == 0) {
		if (*nptr == '0') {
			nptr++;
			if (*nptr == 'x' || *nptr == 'X') {
				nptr++;
				base = 16;
			} else {
				base = 8;
			}
		} else {
			base = 10;
		}
	} else if (base == 16) {
		if (*nptr == '0') {
			nptr++;
			if (*nptr == 'x' || *nptr == 'X') {
				nptr++;
			}
		}
	} else if (base < 2 || base > 36) {
		*ret = 0;
		return -EINVAL;
	}

	int overflow = 0;
	const char* finptr = scan_decimal(nptr, (size_t) - 1, ret, &overflow, base);
	if (endptr) {
		*endptr = (char*)finptr;
	}
	if (overflow) {
		*ret = neg;
		return -ERANGE;
	}
	return neg;
}