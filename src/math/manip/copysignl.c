#include <stdint.h>

long double copysignl(long double x, long double y) {
	union {
		long double f;
		struct {
			uint64_t i;
			uint16_t e;
		};
	} ux = {
		x
	}, uy = {
		y
	};
	ux.e &= 0x7FFF;
	ux.e |= uy.e & 0x8000;
	return ux.f;
}