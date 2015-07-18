#include <ctype.h>
#include <locale.h>

int isprint(int c) {
	return isprint_l(c, uselocale((locale_t)0));
}