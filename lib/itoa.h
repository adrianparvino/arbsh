size_t uintostrbase(char *s, size_t n, int base)
{
        static size_t i = 0;

        if ( n == 0 )
        {
                s[i] = '0';
                return 1;
        }

        if (n / base )
        {
                i = 0;
                uintostrbase(s, n / base, base);
        }

        if (n % base + '0' > '9')
                s[i] = (n % base + '0' + 39);
        else

                s[i] = (n % base + '0');
       
        return ++i;
}

size_t intostrbase(char *s, int n, int base)
{
	
        static size_t i = 0;
	static int toggle = 0;

	/* toggle */
	if ( n < 0 )
	{
		n = -n;
		s[i++] = '-'; 
		toggle = 1;
	}

        if ( n == 0 )
        {
                s[i] = '0';
                return 1;
        }

        if (n / base )
        {
                i = toggle;
                intostrbase(s, n / base, base);
        }

        if (n % base + '0' > '9')
                s[i] = (n % base + '0' + 39);
        else

                s[i] = (n % base + '0');
       
        return ++i;
}



	




