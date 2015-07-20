#include <stdio.h>

long ftell(FILE* f) {
	return (long)ftello(f);
}