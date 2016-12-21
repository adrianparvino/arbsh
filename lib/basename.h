



char *gbasename(char *s)
{
	if (!s || !*s) 
		return ".";

	//while (s && *s)
	//	++s;
	//--s;
	size_t i = 0;
	

	while (*s)
	{
		if ( *s == '/' )
			*s = '\0';
		++s;
	}

	//for (;*s != '/';--s)
	//	;
        

	return ++s;
}

	


