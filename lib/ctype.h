/* ctype.h character types */

/* function prototypes */
int gisalnum(int); 
int gisalpha(int); 
int gisblank(int); 
int giscntrl(int); 
int gisdigit(int); 
int gisgraph(int); 
int gislower(int); 
int gisprint(int); 
int gispunct(int); 
int gisspace(int); 
int gisupper(int); 
int gisxdigit(int); 
int gtolower(int); 
int gtoupper(int);


/* functions */

/*
	These ctype functions are a bit heavy, but designed so that
	ret = 1, can be easily changed to ret =x, or so that new
	char values can be added as needed.
*/

int gisalnum(int x) 
{
	return x;
}
int gisalpha(int x) 
{
	return x;
}
int gisblank(int x) 
{
	int ret = 1;
	switch(x)
	{
		case ' ':
			return ret;
			break;
		case '\t':
			return ret;
			break;
		default:
			ret = 0;
			break;
	}
	return ret;
}
int giscntrl(int x) 
{
	return x;
}
int gisdigit(int x) 
{
	if ( x >= '0' && x <= '9')
		return 1;
	return 0;

}
int gisgraph(int x) 
{
	return x;
}
int gislower(int x) 
{
	/* a table might be faster here */
	if (x >= 'a' && x <= 'z')
		return 1;
	return 0;
}
int gisprint(int x) 
{
	return x;
}
int gispunct(int x) 
{
	return x;
}
int gisspace(int x) 
{
	int ret = 1;
	switch(x)
	{
		case ' ':
			return ret;
			break;
		case '\t':
			return ret;
			break;
		
		case '\n':
			return ret;
			break;
		case '\r':
			return ret;
			break;
		case '\f':
			return ret;
			break;
		case '\v':
			return ret;
			break; 
		default:
			ret = 0;
			break;
	}
	return ret;
}
int gisupper(int x) 
{
	
	return x;
}
int gisxdigit(int x) 
{
	return x;
}
int gtolower(int x)
{
	return x;
}
int gtoupper(int x)
{
	return x;
}




