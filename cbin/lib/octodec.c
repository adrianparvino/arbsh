
// this needs improved
int octodec(int n)
{
        int i, j, k;
        i = j = k = 0;

        while ( n != 0 )
        {
                k = n % 10;
                n /= 10;
                j += k * pow(8, i);
                ++i;
        }
        return j;
}

