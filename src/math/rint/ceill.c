long double ceill(long double x) {
	unsigned short int controlWord;
	unsigned short int newControlWord;
	asm(
	    "fnstcw %1;"
	    "movw %1, %%ax;"
	    "andw $0xF3FF, %%ax;"
	    "orw  $0x8000, %%ax;"
	    "movw %%ax, %2;"
	    "fldcw %2;"
	    "frndint;"
	    "fldcw %1;"
	    :"=t"(x), "=m"(controlWord), "=m"(newControlWord):"0"(x):"ax");
	return x;
}
