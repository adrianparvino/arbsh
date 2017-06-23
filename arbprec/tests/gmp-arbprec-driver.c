#include <stdio.h>
#include <gmp.h> 
#include <assert.h>

int main(int argc, char *argv[])
{ 
	argc = argc;
	mpf_t n;
	mpf_t j;
	mpf_init(n); 
	mpf_init(j); 
	mpf_set_str(n,argv[1], 10); 
	gmp_printf("%.100Ff\n", n); 
	mpf_sqrt(j, n);
	gmp_printf("gmp sqrt %.100Ff\n", j); 

	printf ("\n");
}
