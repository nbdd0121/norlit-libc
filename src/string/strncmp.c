#include <string.h>

int strncmp(const char *s1, const char *s2, size_t n) {
	if (s1 == s2) {
		return 0;
	}
	size_t i;
	for (i = 0; *s2 != 0 && i < n; i++, s1++, s2++) {
		int diff = *s1 - *s2;
		if (diff != 0) {
			return diff;
		}
	}
	if (i >= n)
		return 0;
	return *s1 - *s2;
}