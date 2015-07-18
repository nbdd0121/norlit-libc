#include <stdint.h>

float copysignf(float x, float y) {
	union {
		float f;
		uint32_t i;
	} ux = {
		x
	}, uy = {
		y
	};
	ux.i &= 0x7FFFFFFFUL;
	ux.i |= uy.i & 0x80000000UL;
	return ux.f;
}