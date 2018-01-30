#include <arbprec/arbprec.h>

/* A work in progress ! */

/*
               75.29
            ________
          \/ 5669.00
             49
             _______
7*20 = 145  | 769
         -    725
             _______
75*20= 1502 |  44 00
          -    30 04
              _______
752*20=15049 | 13 9600
           -   13 5441
                _________
7529*20=150582 |  315900
             -

            23.8 
          _______
        \/5 69.00
          4
         _______       44 * 4 = 176
     43 | 1 69         43 * 3 = 129
          1 29
          ______       469 * 9 = 4221
     468 |  40.00      468 * 8 = 3744
            37.44

	* Get the first number set
	* attempt to find the square of the number set using multiplication
	* push the discovered number onto the answer
	* perform a subtraction and carry down 2 digits from the number that is being squared
	* multiply the answer by 20 and put into temp
	* find how many times temp can go into the carried down sub and its two digits

*/
fxdpnt *arb_long_sqrt(fxdpnt *a, fxdpnt *c, int base, int scale)
{
	
}

