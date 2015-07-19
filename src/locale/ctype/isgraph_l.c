#include <ctype.h>
#include <assert.h>

int isgraph_l(int c, locale_t loc) {
	return !iscntrl_l(c, loc) && c != ' ';
}