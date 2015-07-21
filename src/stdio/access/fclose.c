#include "../internal.h"
#include <stdlib.h>

int fclose(FILE* f) {
	fflush(f);
	if (f->close(f)) {
		return EOF;
	}
	freeFile(f);
	return 0;
}