#include <string.h>
#include <locale.h>

int strcoll(const char *s1, const char *s2) {
	return strcoll_l(s1, s2, uselocale((locale_t)0));
}