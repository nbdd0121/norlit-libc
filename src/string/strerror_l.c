#include <string.h>

char *strerror_l(int errnum, locale_t locale) {
	return stderror(errnum);
}