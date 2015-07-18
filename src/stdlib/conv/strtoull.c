#include "internal.h"
#include <limits.h>
#include <errno.h>

unsigned long long strtoull(const char * restrict nptr, char ** restrict endptr, int base) {
	uint64_t ret = 0;
	int sign = scan_int(nptr, endptr, base, &ret);
	if (sign < 0) {
		errno = -sign;
		return sign == -ERANGE ? ULLONG_MAX : ret;
	}
	return sign ? -ret : ret;
}