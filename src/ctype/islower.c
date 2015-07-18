#include <ctype.h>
#include <locale.h>

int islower(int c) {
	return islower_l(c, uselocale((locale_t)0));
}