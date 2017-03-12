#include <arb_str/arb_str.h>


int main(int argc, char *argv[])
{
	char *string = malloc(1000);
	string[0] = 0;
	string = arb_str_divide(argv[1], argv[2], string);

	printf("%s\n", string);
	return 0;
}
