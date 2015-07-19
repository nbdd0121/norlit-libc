#include <stdlib.h>

static void swap(char* dst, char* src, size_t size) {
	if (dst != src) {
		for (int i = 0; i < size; i++) {
			char tmp = dst[i];
			dst[i] = src[i];
			src[i] = tmp;
		}
	}
}

void qsort(void *array, size_t length, size_t elementSize, int (*compar)(const void *, const void *)) {
	if (length <= 1)
		return;

	size_t last = length - 1;
	char* lastPtr = (char*)array + last * elementSize;
	size_t storeIndex = 0;
	char* storeIndexPtr = array;
	size_t i = 0;
	char* iPtr = array;
	for (; i < last; i++, iPtr += elementSize) {
		if (compar(iPtr, lastPtr) < 0) {
			swap(storeIndexPtr, iPtr, elementSize);

			storeIndex++;
			storeIndexPtr += elementSize;
		}
	}
	swap(lastPtr, storeIndexPtr, elementSize);

	qsort(array, storeIndex, elementSize, compar);
	qsort(storeIndexPtr + elementSize, length - storeIndex - 1, elementSize, compar);
}