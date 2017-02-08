#include "arb_str.h" 

void print_real(char *s, char *realname)
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

int getcharval(char *s, size_t idx)
{ 
	size_t len = gstrlen(s);
        if (idx < len)
        	return s[len - idx - 1] - 48;
        return 0;
} 
void *strallocate(size_t len)
{
	void *ret;
	if(!(ret = gmalloc(len)))
		die("malloc failed\n"); 
	return ret;
} 

void die(char *message)
{
	//gfprintf(gstdout, "%s", message);
	gprintf("%s", message);
	//exit(1);
}



size_t reversestr(char *x)
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

