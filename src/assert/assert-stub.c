#include <assert.h>
#include <stdlib.h>

_Noreturn
void __norlit_libc_assertion_failure(const char *file, int line, const char *func, const char *expr) {
	// fprintf(stderr, "Assertion failed: %s, function %s, file %s, line %d.\n", expr, func, file, line);
	abort();
}