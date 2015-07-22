#include "internal.h"
#include <limits.h>
#include <errno.h>

unsigned long strtoul(const char * restrict nptr, char ** restrict endptr, int base) {
	unsigned long long ret = 0;
	int sign = scan_int(nptr, endptr, base, &ret);
	if (sign < 0) {
		errno = -sign;
		return sign == -ERANGE ? ULONG_MAX : ret;
	}
	if (ret > ULONG_MAX) {
		ret = ULONG_MAX;
	}
	return (unsigned long)(sign ? -ret : ret);
}