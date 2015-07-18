#include <ctype.h>
#include <locale.h>

int iscntrl(int c) {
	return iscntrl_l(c, uselocale((locale_t)0));
}