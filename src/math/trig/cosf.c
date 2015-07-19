float cosf(float x) {
	asm("fcos":"=t"(x):"0"(x));
	return x;
}