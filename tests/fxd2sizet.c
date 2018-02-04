#include <arbprec/arbprec.h>

int main(int argc, char *argv[])
{
	if (argc < 4 )
		arb_error("Needs 3 args, such as: 123 base scale");


	int base = strtol(argv[3], 0, 10);

	fxdpnt *a = arb_str2fxdpnt(argv[1]);
	

	size_t ret = fxd2sizet(a, 10);
	printf("%zu\n", ret);
	return 0;
}

