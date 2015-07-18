#include <ctype.h>
#include <locale.h>

int isspace(int c) {
	return isspace_l(c, uselocale((locale_t)0));
}