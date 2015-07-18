#include <ctype.h>
#include <locale.h>

int tolower(int c) {
	return tolower_l(c, uselocale((locale_t)0));
}