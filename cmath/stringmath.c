#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void subtract(char *, char *);
void subtraction(char *, char *);
void add(char *, char *);
void addition(char *, char *);

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


void addition(char *a, char *b)
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

void subtraction(char *a, char *b)
{
        char result[1000] = { 0 };
	size_t i = 0;
	size_t width = 0;
	int sum = 0;
	int borrow = 0;
	size_t wa = strlen(a); 
	size_t wb = strlen(b); 
	char ca = 0;
	char cb = 0;
	char tens[1000] = {0};
	static char sign = '+';
	
        
	if ( wa > wb ) width = wa;
	else width = wb;

        for(i=0; i<width; i++){
                ca = getcharval2(a, i);
                cb = getcharval2(b, i); 
		// printf("%d %d\n", ca, cb);
		//sum = a[wa - i - 1] - b[wb - i - 1] + borrow + 96; 
                sum = ca - cb + borrow + 96;
		
                borrow = 0;
                if(sum < 96){
                        borrow = -1;
                        sum +=10;

                }
                result[i] = sum - 48;
        }
	/*  Nothing left to borrow */
	if ( borrow == -1)
	{ 
		size_t z = width + 1; 
		memset(tens, '0', z); tens[0] ='1'; tens[z] ='\0'; reversestr(result);
		subtraction(tens, result);
		return;
	}
        //if (borrow == -1) 
	//	result[i++] = '1'; /* borrow + 48 */ 
        result[i]= 0; 
        reversestr(result);
	/* sign bit hack ( relies on 0 places ) */
	//if ( result[0] == '0' && width > 1 )
//		result[0] = '+'; 



        printf("result = %20s\n",  result); 

}




void subtract(char *x, char *y)
{ 
	/* sign bits have a lot of possibilities and rules, this is incomplete */
	if (x[0] == '+')
		++x;
	if ( x[0] == '-' )
	{
		++x;
		add(x, y);
	}else if (y[0] == '+')
	{
		++y;
		subtraction(x, y);
	}
	else if (y[0] == '-')
	{ 
		++y;
		addition(x, y);
		
	} else subtraction(x,y);
}

void add(char *x, char *y)
{ 
	if ( x[0] == '+')
		++x;
	if ( x[0] == '-' )
	{
		++x;
		subtract(x, y);
	}else if (y[0] == '+')
	{
		++y;
		addition(x, y);
	}
	else if (y[0] == '-')
	{ 
		++y;
		subtraction(x, y);
	}else addition(x, y);
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
