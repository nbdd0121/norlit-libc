#include <stdio.h>

int fsetpos(FILE *f, const fpos_t *pos) {
	return fseeko(f, *pos, SEEK_SET);
}