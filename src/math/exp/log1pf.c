#include <math.h>

float log1pf(float x) {
	if (fabsf(x) >= 1.0 - 0.5 * M_SQRT2)
		return logf(1.0 + x);
	asm("fldln2; fxch; fyl2xp1":"=t"(x):"0"(x):"st(1)");
	return x;
}