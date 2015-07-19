static int charToDigit(char c) {
	if (c == '.')return 0;
	if (c == '/')return 1;
	if (c >= '0' && c <= '9')return c - '0' + 2;
	if (c >= 'A' && c <= 'Z')return c - 'A' + 12;
	if (c >= 'a' && c <= 'z')return c - 'a' + 38;
	return -1;
}

long a64l(const char* s) {
	unsigned long ret = 0;
	for (int i = 0; i < 6; i++) {
		int digit = charToDigit(s[i]);
		if (digit == -1) {
			break;
		}
		ret |= digit << (6 * i);
	}
	return ret & 0xFFFFFFFF;
}