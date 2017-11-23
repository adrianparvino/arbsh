#include <arbprec/arbprec.h>

int main(int argc, char *argv[])
{
        if (argc < 5)
        {
                printf("needs 4 args: bignum bignum   base  scale\n");
                return 0;
        }
        int base = strtol(argv[3],0,  10);
        int scale =  strtol(argv[4],0,  10);
        fxdpnt *a = ccarb_new_num(12, scale);
        fxdpnt *b = ccarb_new_num(12, scale);
        fxdpnt *c = ccarb_new_num(12, scale);
        a = ccarb_str2fxdpnt(argv[1]);
        b = ccarb_str2fxdpnt(argv[2]);
        c = ccarb_divide(a, b, c, base, scale);
        ccarb_print(c);
        return 0;
}
   
