#include "internal.h"
#include <unistd.h>

void quick_exit(int status) {
	for (int i = quick_exit_reg_count - 1; i >= 0 ; i--) {
		quick_exit_register[i]();
	}
	_exit(status);
}