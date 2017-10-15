#include <stdio.h>

int main(int argc, char *argv[])
{
	int n = 15;


        if ( argc > 1 )
                n = strtol(argv[1], 0, 10);
       
           
	printf("modulo %d\n", n%3);
	printf("ampersand %d\n", n&3);
	return 0;

}
