double atan2(double y, double x) {
	asm("fpatan":"=t"(x):"0"(x), "u"(y):"st(1)");
	return x;
}