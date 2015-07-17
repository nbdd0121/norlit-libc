/**
 * Header file providing utility for log2
 *
 * @author Gary Guo <nbdd0121@hotmail.com>
 */

#ifndef _NORLIT_UTIL_LOG2_H
#define _NORLIT_UTIL_LOG2_H

#include <stddef.h>

static inline size_t log2_int(size_t num) {
	size_t ret;
	asm volatile("bsr %1, %0":"=r"(ret):"r"(num):"cc");
	return ret;
}

static inline size_t log2_int_ceiling(size_t num) {
	size_t ret;
	asm volatile("bsr %1, %0":"=r"(ret):"r"(num - 1):"cc");
	return ret + 1;
}

#endif


