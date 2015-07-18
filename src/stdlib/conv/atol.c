#include <stdlib.h>
#include <errno.h>

long atol(const char *nptr) {
	int errno_bak = errno;
	long ret = strtol(nptr, NULL, 10);
	errno = errno_bak;
	return ret;
}