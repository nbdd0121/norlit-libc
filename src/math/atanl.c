long double atanl(long double x) {
	asm("fld1;fpatan":"=t"(x):"0"(x):"st(1)");
	return x;
}