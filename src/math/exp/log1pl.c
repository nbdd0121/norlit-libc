#include <math.h>

long double log1pl(long double x) {
	if (fabsl(x) >= 1.0 - 0.5 * M_SQRT2)
		return logl(1.0 + x);
	asm("fldln2; fxch; fyl2xp1":"=t"(x):"0"(x):"st(1)");
	return x;
}