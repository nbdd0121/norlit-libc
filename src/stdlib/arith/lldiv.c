#include <stdlib.h>

lldiv_t lldiv(long long numer, long long denom) {
	return (lldiv_t) {numer / denom, numer % denom};
}