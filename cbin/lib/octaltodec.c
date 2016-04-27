int octal(char *s)
{
        int r = 0;
        char c;

        while (c = *s++ )
        {
                if ( ! (isoctal(c)))
                        break;
                r = (r << 3) | (c - '0');
        }

        return r;
}

