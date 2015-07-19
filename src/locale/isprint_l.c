#include <ctype.h>
#include <assert.h>

int isprint_l(int c, locale_t loc) {
	return !iscntrl_l(c, loc);
}