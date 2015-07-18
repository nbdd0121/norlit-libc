#include <ctype.h>
#include <locale.h>

int toupper(int c) {
	return toupper_l(c, uselocale((locale_t)0));
}