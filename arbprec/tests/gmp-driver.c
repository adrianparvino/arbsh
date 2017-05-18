#include <stdio.h>
#include <gmp.h> 
#include <assert.h>

int main()
{ 
	char inputStr[1024]; 
	mpf_t n;

	printf ("Enter your number: ");
	scanf("%1023s" , inputStr); 
	mpf_init(n); 
	mpf_set_str(n,inputStr, 10); 
	//mpf_out_str(stdout,10,20, n);
	gmp_printf("%.100Ff\n", n);
	printf ("\n");
}
