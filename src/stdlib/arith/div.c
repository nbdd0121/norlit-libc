#include <stdlib.h>

div_t div(int numer, int denom) {
	return (div_t) {numer / denom, numer % denom};
}