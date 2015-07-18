#include <stdlib.h>
#include <errno.h>

long long atoll(const char *nptr) {
	int errno_bak = errno;
	long long ret = strtoll(nptr, NULL, 10);
	errno = errno_bak;
	return ret;
}