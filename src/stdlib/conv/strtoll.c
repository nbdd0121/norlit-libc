#include "internal.h"
#include <limits.h>
#include <errno.h>

long long strtoll(const char * restrict nptr, char ** restrict endptr, int base) {
	unsigned long long ret = 0;
	int sign = scan_int(nptr, endptr, base, &ret);
	if (sign < 0) {
		errno = -sign;
		return sign == -ERANGE ? (ret ? LLONG_MIN : LLONG_MAX) : ret;
	}
	if (sign) {
		if (ret > -(unsigned long long)LLONG_MIN) {
			errno = ERANGE;
			return LLONG_MIN;
		}
		return (long long) - ret;
	} else if (ret > LLONG_MAX) {
		errno = ERANGE;
		return LLONG_MAX;
	}
	return (long long)ret;
}