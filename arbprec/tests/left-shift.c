#include <arbprec/arbprec.h>

int main(int argc, char *argv[])
{ 
	fxdpnt *a;

	a = arb_str2fxdpnt(argv[1]);
	
	arb_leftshift(a, 3, 0);
	arb_print(a); 
	arb_leftshift(a, 1, 0);
	arb_print(a); 
	return 0;
}

