long double log10l(long double x) {
	asm("fldlg2; fxch; fyl2x":"=t"(x):"0"(x):"st(1)");
	return x;
}