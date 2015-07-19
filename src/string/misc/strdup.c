#include <string.h>
#include <stdlib.h>

char *strdup(const char *s) {
	size_t len = strlen(s) + 1;
	char *ret = malloc(len);
	if (!ret) {
		return NULL;
	}
	memcpy(ret, s, len);
	return ret;
}