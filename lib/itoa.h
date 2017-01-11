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

