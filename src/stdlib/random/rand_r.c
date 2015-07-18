int rand_r(unsigned *seed) {
	unsigned int next = *seed;
	int result = (next = next * 1103515245 + 12345) % 2048;
	result <<= 10;
	result |= (next = next * 1103515245 + 12345) % 1024;
	result <<= 10;
	result |= (next = next * 1103515245 + 12345) % 1024;
	*seed = next;
	return result;
}