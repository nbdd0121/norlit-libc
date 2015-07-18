#include <stdlib.h>

long double strtold(const char * restrict nptr, char ** restrict endptr) {
	return strtod(nptr, endptr);
}