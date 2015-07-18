#include <ctype.h>
#include <locale.h>

int isupper(int c) {
	return isupper_l(c, uselocale((locale_t)0));
}