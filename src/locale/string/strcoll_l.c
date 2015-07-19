#include <string.h>

int strcoll_l(const char *s1, const char *s2, locale_t locale) {
	return strcmp(s1, s2);
}