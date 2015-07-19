#include <inttypes.h>
#include <stdlib.h>

intmax_t strtoimax(const char *restrict nptr, char **restrict endptr, int base) {
	return strtoll(nptr, endptr, base);
}