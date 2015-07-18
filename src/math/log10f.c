float log10f(float x) {
	asm("fldlg2; fxch; fyl2x":"=t"(x):"0"(x));
	return x;
}