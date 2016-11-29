#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct fltglb {
	char *x;
	size_t xlen;
	size_t xmant;
	char *y;
	size_t ylen;
	size_t ymant;
	char *result;
};



size_t reversestr(char *x)
{
        /*
		Reverse a string and return its length.
		Would be nice to also return its floating point 
		position (in a struct) or by setting a global.

		For addition, strings only need be reversed once.
	*/

        size_t i = 0;
        char swap = 0;
        size_t lim = strlen(x);
        size_t half = lim / 2;

        for ( ; i < half ; i++)
        {
                swap = x[i];
                x[i] = x[lim - i - 1];
                x[lim - i - 1] = swap;
        }
        return lim;
}

int getcharval(const char *s, size_t idx) {
	/*
		This test performs the string length differential measurement 
		and returns a zero if it's insufficient.
	*/
	size_t len = strlen(s);
        if (idx < len)
        	return s[len - idx - 1] - 48;

        return 0;
}

void add(char *a, char *b)
{
        char *result;
	size_t i = 0;
	size_t width = 0;
	size_t sum = 0;
	size_t carry = 0;
	size_t wa = strlen(a);
	size_t wb = strlen(b);
	char ca = 0;
	char cb = 0;
	
        //width = wa > wb ? wa : wb;
	if ( wa > wb )
		width = wa;
	else
		width = wb;

	/* for arbitrary precision it makes sense to allocate for math libs */
	if (!(result = malloc (width)))
	{
		fprintf(stderr, "malloc failed\n");
		return;
	}
	

        for(i=0; i<width; i++){
                ca = getcharval(a, i);
                cb = getcharval(b, i); 
		// printf("%d %d\n", ca, cb);
		//sum = a[wa - i - 1] + b[wb - i - 1] + carry - 48 - 48;
                sum = ca + cb + carry;
		
                carry = 0;
                if(sum > 9){
                        carry = 1;
                        sum -= 10;
                }
                result[i] = sum + 48;
        }

        if (carry) 
		result[i++] = carry + 48; /* carry the final '1' */

        result[i]= 0;

        reversestr(result);
        printf("result = %20s\n", result);
	free(result);

}
int main(int argc, char *argv[])
{

        if ( argc != 3)
        {
                fprintf(stderr, "Needs two args\n");
                return 1;
        } 
	printf("\n\n");
        printf("         %20s\n", argv[1]);
        printf("       + %20s\n", argv[2]);
	printf("         %20s\n", "-------------------");
	
	
       
	add(argv[1], argv[2]);
	printf ("answer = %20ld\n", strtol(argv[1], 0, 10) + strtol(argv[2], 0, 10));
}
