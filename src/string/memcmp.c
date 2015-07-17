#include <string.h>

int memcmp(const void *s1, const void *s2, size_t n) {
	const char *p1 = s1, *p2 = s2;
	for (size_t i = 0; i < n; i++, p1++, p2++) {
		int diff = *p1 - *p2;
		if (diff != 0) {
			return diff;
		}
	}
	return 0;
}