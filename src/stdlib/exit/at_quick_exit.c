#include "internal.h"

int at_quick_exit(void (*func)(void)) {
	if (quick_exit_reg_count >= QUICK_EXIT_REGISTER_COUNT) {
		return -1;
	}
	quick_exit_register[quick_exit_reg_count++] = func;
	return 0;
}