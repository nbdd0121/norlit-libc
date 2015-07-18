#include <ctype.h>
#include <locale.h>

int isalnum(int c) {
	return isalnum_l(c, uselocale((locale_t)0));
}