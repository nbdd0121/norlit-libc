#include <string.h>
#include <assert.h>

int strerror_r(int errnum, char *strerrbuf, size_t buflen) {
	strncpy(strerrbuf, strerror(errnum), buflen);
	return 0;
}