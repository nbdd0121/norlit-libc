long double log2l(long double x) {
	asm("fld1; fxch; fyl2x":"=t"(x):"0"(x):"st(1)");
	return x;
}