#include <math.h>

double log1p(double x) {
	if (fabs(x) >= 1.0 - 0.5 * M_SQRT2)
		return log(1.0 + x);
	asm("fldln2; fxch; fyl2xp1":"=t"(x):"0"(x):"st(1)");
	return x;
}