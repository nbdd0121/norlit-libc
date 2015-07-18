#include <ctype.h>
#include <locale.h>

int isxdigit(int c) {
	return isxdigit_l(c, uselocale((locale_t)0));
}