#include "arb_str.h" 

void arb_str_print_real(char *s, char *realname)
{
	if ( arb_str_verbosity == 0 )
		return;
	size_t i = 0;
	gprintf("------------------------\n");
	gprintf("name:      %s\n", realname);
	gprintf("string:    %s\n", s);
	gprintf("real nums: ");
	
	while (s[i] != '\0')
	{
		gprintf("|%d", s[i] - '0');
		++i;
	}
	gprintf("|\n");
	gprintf("------------------------\n");
}

int arb_str_index(char *s, size_t idx)
{ 
	size_t len = gstrlen(s);
        if (idx < len)
        	return s[len - idx - 1] - 48;
        return 0;
} 
void *arb_str_malloc(size_t len)
{
	void *ret;
	if(!(ret = gmalloc(len)))
		arb_str_die("malloc failed\n"); 
	return ret;
} 

void arb_str_die(char *message)
{
	//gfprintf(gstdout, "%s", message);
	gprintf("%s", message);
	//exit(1);
}



size_t arb_str_rev(char *x)
{
        size_t i = 0;
        char swap = 0;
        size_t lim = gstrlen(x);
        size_t half = lim / 2;

        for ( ; i < half ; i++)
        {
                swap = x[i];
                x[i] = x[lim - i - 1];
                x[lim - i - 1] = swap;
        }
        return lim;
} 

