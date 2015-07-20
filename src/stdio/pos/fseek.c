#include <stdio.h>

int fseek(FILE *f, long off, int dir) {
	return fseeko(f, off, dir);
}