#include "internal.h"

int atexit(void (*func)(void)) {
	if (exit_reg_count >= EXIT_REGISTER_COUNT) {
		return -1;
	}
	exit_register[exit_reg_count++] = func;
	return 0;
}