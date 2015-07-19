float atan2f(float y, float x) {
	asm("fpatan":"=t"(x):"0"(x), "u"(y):"st(1)");
	return x;
}