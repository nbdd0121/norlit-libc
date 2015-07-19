char* l64a(long value) {
	static char buffer[7] = {};
	unsigned long val = value & 0xFFFFFFFFUL;
	for (int i = 0; i < 6; i++) {
		int digit = (val >> (6 * i)) & 63;
		buffer[i] = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"[digit];
	}
	return buffer;
}