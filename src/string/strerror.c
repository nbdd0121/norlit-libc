#include <string.h>
#include <errno.h>
#include <locale.h>

char *strerror(int errnum) {
	return strerror_l(errnum, uselocale((locale_t)0));
}