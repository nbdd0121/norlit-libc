long double remainderl(long double x, long double y) {
	asm("1: fprem1; fnstsw %%ax; sahf; jp 1b;":"=t"(x):"0"(x), "u"(y):"ax", "cc");
	return x;
}