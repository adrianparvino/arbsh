
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
        fxdpnt *a = arb_new_num(12, scale);
        fxdpnt *b = arb_new_num(12, scale);
        fxdpnt *c = arb_new_num(12, scale);
        fxdpnt *d = arb_new_num(12, scale);

        a = arb_str2fxdpnt(argv[1]);
        b = arb_str2fxdpnt(argv[2]);

        a = arb_add_precision(a, scale);
        b = arb_add_precision(b, scale);


        printf("perform the division\n");     

        c = arb_divide(a, b, c, base, scale);
        arb_print(c);

	printf("Check the work using multiplication, this will by nature be .00....01 less\n");
        d = arb_mul(b, c, d, base);
        arb_printold(d);

	//printf("perform Graff division, this is much slower than Knuth's\n");
        //c = NULL;
        //c = arb_division(a, b, c, base, scale);
        //arb_printold(c);

        printf("==============\n");
        return 0;
}
   
