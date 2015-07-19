#include <stdlib.h>

ldiv_t ldiv(long numer, long denom) {
	return (ldiv_t) {numer / denom, numer % denom};
}