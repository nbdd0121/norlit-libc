#include <string.h>

int strcmp(const char *s1, const char *s2) {
	if (s1 == s2) {
		return 0;
	}
	for (; *s2 != 0; s1++, s2++) {
		int diff = *s1 - *s2;
		if (diff != 0) {
			return diff;
		}
	}
	return *s1;
}