#include <stdio.h>

void setbuf(FILE * restrict f, char * restrict buf) {
	if (buf) {
		setvbuf(f, buf, _IOFBF, BUFSIZ);
	} else {
		setvbuf(f, NULL, _IONBF, 0);
	}
}
