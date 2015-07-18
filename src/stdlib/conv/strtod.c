#include "internal.h"

double strtod(const char * restrict nptr, char ** restrict endptr) {
	double ret;
	const char* finptr = scan_float(nptr, &ret);
	if (endptr)
		*endptr = (char*)finptr;
	return ret;
}