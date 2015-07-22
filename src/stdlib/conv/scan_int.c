#include "internal.h"
#include <limits.h>
#include <string.h>

#include "../../stdio/internal.h"
#include "../../stdio/conv/internal.h"

int scan_int(const char * restrict nptr, char ** restrict endptr, int base, unsigned long long* ret) {
	nptr = scan_space(nptr);
	FILE f = { .read = s_read, .bufpolicy = _IONBF, .bufpos = -1, .flags = 0, .additionalData = (void*)nptr};
	int sign;
	int len = scan_int_f(&f, INT_MAX, base, ret, &sign);

	if (endptr) {
		*endptr = (char*)(nptr + len);
	}
	return sign;
}