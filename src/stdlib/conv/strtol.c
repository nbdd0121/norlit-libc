#include "internal.h"
#include <limits.h>
#include <errno.h>

long strtol(const char * restrict nptr, char ** restrict endptr, int base) {
	unsigned long long ret = 0;
	int sign = scan_int(nptr, endptr, base, &ret);
	if (sign < 0) {
		errno = -sign;
		return sign == -ERANGE ? (ret ? LONG_MIN : LONG_MAX) : ret;
	}
	if (sign) {
		if (ret > -(unsigned long long)LONG_MIN) {
			errno = ERANGE;
			return LONG_MIN;
		}
		return (long) - ret;
	} else if (ret > LONG_MAX) {
		errno = ERANGE;
		return LONG_MAX;
	}
	return (long)ret;
}