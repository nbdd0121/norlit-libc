#include <math.h>

long double acosl(long double x) {
	return atan2l(sqrtl(1 - x * x), x);
}