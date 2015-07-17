#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

locale_t newlocale(int mask, const char *name, locale_t base) {
	if (*name || strcmp(name, "C") == 0 || strcmp(name, "POSIX") == 0) {
		if (!base) {
			base = malloc(1);
		}
		return base;
	}
	errno = ENOENT;
	return (locale_t)0;
}