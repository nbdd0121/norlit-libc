#include "../internal.h"

__attribute__((destructor))
static void closeAllFiles() {
	FILE* f;
	list_forEach(&allFiles, f, FILE, list) {
		fclose(f);
	}
}