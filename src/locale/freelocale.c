#include <locale.h>
#include <stdlib.h>

void freelocale(locale_t locobj) {
	free(locobj);
}