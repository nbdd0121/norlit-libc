#include <stdlib.h>

static unsigned seed;

void srand(unsigned s) {
	seed = s;
}

int rand(void) {
	return rand_r(&seed);
}