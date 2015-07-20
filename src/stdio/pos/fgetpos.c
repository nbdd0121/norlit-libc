#include <stdio.h>

int fgetpos(FILE * restrict f, fpos_t * restrict pos) {
	off_t ptr = ftello(f);
	if (ptr == -1) {
		return 1;
	} else {
		*pos = ptr;
		return 0;
	}
}
