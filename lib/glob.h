int rglob(const char *p, const char *s) 
{
	return
		*p=='*'  ? rglob(p+1,s) || (*s && rglob(p,s+1)) :
		*p=='?'  ? *s && rglob(p+1,s+1) :
		*s==*p++ && (!*s++ || rglob(p,s));
}

int gglob(const char *p, const char *s)
{
	/* Similiar to FNM_PERIOD of fnmatch() */
        if ( s[0] == '.' && p[0] != '.' )
                return 0;
        return rglob(p, s);
}


