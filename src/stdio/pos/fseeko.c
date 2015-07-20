#include "../internal.h"

int fseeko(FILE *f, off_t off, int dir) {
	fflush(f);
	if (f->seek(f, off, dir) == -1) {
		return 1;
	}
	return 0;
}