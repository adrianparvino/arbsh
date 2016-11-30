#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


size_t reversestr(char *x)
{ 
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

int getcharval2(const char *s, size_t idx)
{ 
	size_t len = strlen(s);
        if (idx < len)
        	return s[len - idx - 1];
        return 48;
}

int getcharval(const char *s, size_t idx)
{ 
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
	//size_t wa = reversestr(a);
	size_t wb = strlen(b);
	//size_t wb = reversestr(b);
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
		result[i++] = '1'; /* carry + 48 */

        result[i]= 0;

        reversestr(result);
        printf("result = %20s\n", result);
	free(result);

}
void subtract(char *a, char *b)
{
        char result[1000] = { 0 };
	size_t i = 0;
	size_t width = 0;
	int sum = 0;
	int carry = 0;
	size_t wa = strlen(a); 
	size_t wb = strlen(b); 
	char ca = 0;
	char cb = 0;
	
        //width = wa > wb ? wa : wb;
	if ( wa > wb )
		width = wa;
	else
		width = wb;

        for(i=0; i<width; i++){
                ca = getcharval2(a, i);
                cb = getcharval2(b, i); 
		// printf("%d %d\n", ca, cb);
		//sum = a[wa - i - 1] - b[wb - i - 1] + carry + 96; 
                sum = ca - cb + carry + 96;
		
                carry = 0;
                if(sum < 96){
                        carry = -1;
                        sum +=10;

                }
                result[i] = sum - 48;
        }

        //if (carry == -1) 
	//	result[i++] = '1'; /* carry + 48 */

        result[i]= 0;

        reversestr(result);

        printf("result = %20s\n", result);


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
	printf ("answer = %20ld (+) \n", strtol(argv[1], 0, 10) + strtol(argv[2], 0, 10));
	subtract(argv[1], argv[2]);
	printf ("answer = %20ld (-) \n", strtol(argv[1], 0, 10) - strtol(argv[2], 0, 10));
}
