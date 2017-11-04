#include <stdio.h>
#include <gmp.h> 
#include <assert.h>

int main(int argc, char *argv[])
{ 
	argc = argc;
	mpf_t n;
	mpf_t j;
	mpf_t a;
	mpf_init(n); 
	mpf_init(j); 
	mpf_init(a); 
	mpf_set_str(n,argv[1], 50); 
	mpf_set_str(a,argv[2], 50); 
	gmp_printf("%.100Ff\n", n); 
	mpf_sqrt(j, n);
	gmp_printf("gmp sqrt %.100Ff\n", j); 
	
	mpf_div(j, a, n);
	gmp_printf("gmp mpf_div %.100Ff\n", j); 

	printf ("\n");
}
