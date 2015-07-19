#include <ctype.h>
#include <assert.h>

int iscntrl_l(int c, locale_t loc) {
	return (unsigned)c < 0x20 || c == 0x7F;
}