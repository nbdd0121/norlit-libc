#include <math.h>

long double asinl(long double x) {
	return atan2l(x, sqrtl(1 - x * x));
}