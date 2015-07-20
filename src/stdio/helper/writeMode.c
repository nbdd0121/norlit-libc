#include "../internal.h"

int writeMode(FILE* f) {
	if (f->bufmode == BUFMODE_WRITE)return 0;
	if (f->bufmode != BUFMODE_WRITE) {
		if (fflush(f) == EOF) {
			return 1;
		}
	}
	f->bufmode = BUFMODE_WRITE;
	return 0;
}
