#include <string.h>
#include <locale.h>

size_t strxfrm(char * restrict s1, const char * restrict s2, size_t n) {
	return strxfrm_l(s1, s2, n, uselocale((locale_t)0));
}