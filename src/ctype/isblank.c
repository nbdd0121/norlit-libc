#include <ctype.h>
#include <locale.h>

int isblank(int c) {
	return isblank_l(c, uselocale((locale_t)0));
}