#include "../internal.h"

int checkFile(FILE* f) {
	if (f->bufpolicy == 0) {
		setvbuf(f, NULL, f->bufmode, BUFSIZ);
	}
	return 1;
}