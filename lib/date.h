size_t date(char *buf, char *format, size_t max)
{
        size_t n = 0;
        time_t t;
        struct tm *tm;
        if ((t = time(0)) == -1)
                return 0;
        if (!(tm = localtime(&t)))
                return 0;
        if ((n = strftime(buf, max, format, tm)) == 0)
                return 0;
        return n;
}

