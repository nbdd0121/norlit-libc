#include <ctype.h>
#include <assert.h>

int iscntrl_l(int c, locale_t loc) {
	if (c < 0x80) {
		return (unsigned)c < 0x20 || c == 0x7F;
	}
	assert(0); // Unicode not yet supported
}