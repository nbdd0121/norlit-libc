#include <ctype.h>
#include <locale.h>

int isalnum_l(int c, locale_t loc) {
	return isalpha_l(c, loc) || isdigit_l(c, loc);
}