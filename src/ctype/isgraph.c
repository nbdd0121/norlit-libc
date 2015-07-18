#include <ctype.h>
#include <locale.h>

int isgraph(int c) {
	return isgraph_l(c, uselocale((locale_t)0));
}