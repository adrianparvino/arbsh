/*
	ctype.h  - character types 

	Copyright 2017, CM Graff, 'ctype.h', a ctype.h
	implementation.

	See grafland/LICENSE for copying details.
	
	This prototype list adhers to the POSIX 2016
	non-xsi text for ctype.h.  
	
	TODO: POSIX conformity: 
		Create locale_t type
	TODO: Algorithm changes 
		Use lookup tables instead of ranges
	TODO: Use ints instead of character constants
*/

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
int gisascii(int); 

/* functions */
int gisalnum(int x)
{ 
	if (gisalpha(x) || gisdigit(x))
		return 1;
	return 0;
}

int gisalpha(int x) 
{ 
	if (gisupper(x) || gislower(x))
		return 1;
	return 0;
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
	if (x >= '\0' && x < ' ' )
		return 1;
	return 0;
}

int gisdigit(int x) 
{
	if ( x >= '0' && x <= '9')
		return 1;
	return 0;
}

int gisgraph(int x) 
{
	if (x == ' ')
		return 0;
	if (gisprint(x))
		return 1;
	return 0;
}

int gislower(int x) 
{
	if (x >= 'a' && x <= 'z')
		return 1;
	return 0;
}

int gisprint(int x)
{
	if ( giscntrl(x))
		return 0;
	if ( x == ' ' )
		return 1;
	if (gisspace(x) == 0)
		return 1;
	return 0;
}

int gispunct(int x)
{
	if (x >= '!' && x <= '/')
		return 1;
	if (x >= ':' && x <= '@')
		return 1;
	if (x >= '[' && x <= '`')
		return 1;
	if (x >= '{' && x <= '~')
		return 1;
	return 0;
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
	if (x >= 'A' && x <= 'Z')
		return 1;
	return 0;
}

int gisxdigit(int x)
{
	if (gisdigit(x))
		return 1;
	if (x >= 'a' && x <= 'f')
		return 1;
	if (x >= 'A' && x <= 'F')
		return 1;
	return 0;
}

int gtolower(int x)
{ 
	if (gisupper(x))
		return ('a' + x - 'A');
	else 
		return x;
}

int gtoupper(int x)
{ 
	if (gislower(x))
		return ('A' + x - 'a');
	else
		return x;
}

int gisascii(int x)
{ 
	if (x >= 0 && x <= 127)
		return 1;
	else 
		return 0; 
}
