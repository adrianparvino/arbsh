#include <arb_str/arb_str.h>

void arb_str_print_real(char *s, char *realname)
{
	size_t i = 0;
	printf("------------------------\n");
	printf("name:      %s\n", realname);
	printf("string:    %s\n", s);
	printf("real nums: ");
	
	while (s[i] != '\0')
	{
		printf("|%d", s[i] - '0');
		++i;
	}
	printf("|\n");
	printf("------------------------\n");
}

int arb_str_index(char *s, size_t idx)
{ 
	size_t len = strlen(s);
        if (idx < len)
        	return s[len - idx - 1] - 48;
        return 0;
}

void *arb_str_malloc(size_t len)
{
	void *ret;
	if(!(ret = malloc(len)))
		arb_str_die("malloc failed\n"); 
	return ret;
} 

void arb_str_die(char *message)
{
	dprintf(2, "%s", message);
	exit(1);
}

size_t arb_str_rev(char *x)
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

