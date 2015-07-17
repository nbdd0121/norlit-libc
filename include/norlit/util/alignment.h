/**
 * Header file providing utility for alignment
 *
 * @author Gary Guo <nbdd0121@hotmail.com>
 */

#ifndef _NORLIT_UTIL_ALIGNMENT_H
#define _NORLIT_UTIL_ALIGNMENT_H

#include <stddef.h>

static inline size_t alignTo(size_t val, size_t alignment) {
	return ((val + alignment - 1) / alignment) * alignment;
}

static inline size_t alignDown(size_t val, size_t alignment) {
	return val / alignment * alignment;
}

#endif