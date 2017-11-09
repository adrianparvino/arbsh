
#include <arbprec.h>
int main(int argc, char *argv[])
{
        if (argc < 5 )
        {
                printf("needs 4 args: bignum bignum   base  scale\n");
                return 0;
        }

        int base = strtol(argv[3],0,  10);
        int scale =  strtol(argv[4],0,  10);
        fxdpnt *a = toym_new_num(12, scale);
        fxdpnt *b = toym_new_num(12, scale);
        fxdpnt *c = toym_new_num(12, scale);
        fxdpnt *d = toym_new_num(12, scale);

        a = toym_str2fxdpnt(argv[1]);
        b = toym_str2fxdpnt(argv[2]);

        a = toym_add_precision(a, scale);
        b = toym_add_precision(b, scale);


        printf("perform knuth division\n");

        c = toym_divide(a, b, c, base, scale);
        toym_print(c);

        d = toym_mul(b, c, d, base);
        toym_printold(d);

        c = NULL;
        c = toym_division(a, b, c, base, scale);
        toym_printold(c);

        printf("==============\n");
        return 0;
}
   
