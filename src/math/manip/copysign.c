#include <stdint.h>

double copysign(double x, double y) {
	union {
		double f;
		uint64_t i;
	} ux = {
		x
	}, uy = {
		y
	};
	ux.i &= 0x7FFFFFFFFFFFFFFFULL;
	ux.i |= uy.i & 0x8000000000000000ULL;
	return ux.f;
}