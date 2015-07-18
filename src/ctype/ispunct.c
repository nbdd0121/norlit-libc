#include <ctype.h>
#include <locale.h>

int ispunct(int c) {
	return ispunct_l(c, uselocale((locale_t)0));
}