#include <stdio.h>
#include <gmp.h> 
#include <assert.h>

int main()
{ 
	char inputStr[1024]; 
	mpq_t n;
	mpq_t j;
	mpq_t ret;
	printf ("Enter your number: ");
	scanf("%1023s" , inputStr); 
	mpq_init(n); 
	mpq_init(ret); 
	mpq_init(j); 
	mpq_set_str(n,inputStr, 10); 
	scanf("%1023s" , inputStr); 
	mpq_set_str(j,inputStr, 10); 
	mpq_add(ret, j, n);
	mpq_out_str(stdout,10, ret);
	printf ("\n");
}
