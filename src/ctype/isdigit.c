#include <ctype.h>
#include <locale.h>

int isdigit(int c) {
	return isdigit_l(c, uselocale((locale_t)0));
}