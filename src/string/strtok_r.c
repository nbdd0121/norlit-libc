#include <string.h>

char *strtok_r(char *str, const char *delim, char **saveptr) {
	if (str) {
		*saveptr = str;
	}
	size_t len = 0;
	while (!len) {
		str = *saveptr;
		if (!str) {
			return NULL;
		}
		len = strcspn(str, delim);
		if (str[len] == 0) {
			*saveptr = NULL;
			continue;
		}
		str[len] = 0;
		*saveptr = str + len + 1;
	}
	return str;
}