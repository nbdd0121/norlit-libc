#include <string.h>

char *strtok(char * restrict str, const char * restrict delim) {
	static char* saveptr = NULL;
	return strtok_r(str, delim, &saveptr);
}