#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

char *setlocale(int category, const char *name) {
	if (!name || *name || strcmp(name, "C") == 0 || strcmp(name, "POSIX") == 0) {
		return "C";
	}
	return NULL;
}