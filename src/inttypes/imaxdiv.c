#include <inttypes.h>

imaxdiv_t imaxdiv(intmax_t numer, intmax_t denom) {
	return (imaxdiv_t) {numer / denom, numer % denom};
}