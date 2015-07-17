#include <locale.h>

static locale_t current = LC_GLOBAL_LOCALE;

locale_t uselocale(locale_t newloc) {
	if (newloc) {
		locale_t ret = current;
		current = newloc;
		return ret;
	}
	return current;
}