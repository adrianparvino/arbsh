

char *nbasename(const char *filename)
{
	char *p = strrchr (filename, '/');
	return p ? p + 1 : (char *) filename;
}










	

char *basename(char *s)
{
        if (!s || !*s)
                return ".";
	
        while (s && *s)
              ++s; 
        //--s;

	for (;s-- && *s == '/' ; )//--s)
                *s = '\0';

        for (;s-- && *s && *(s - 1) != '/';)//--s)
              ;
	
        //return ++s;
	return s;
}

