#include <ctype.h>
#include <locale.h>

int isalpha(int c) {
	return isalpha_l(c, uselocale((locale_t)0));
}