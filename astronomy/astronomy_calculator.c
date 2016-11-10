#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
        double M = 0;
        double m = 0;
        double extinction = 0;
        double parsecs = 0;
        double extinction_divisor = 1000;
        double real_M = 0;
        double m_minus_M = 0;
	double myvar = 0;

        /* (m-M) = distance v*/

        /* log10^d = [(mv - Mv) + 5] / 5 */

        real_M = (M / extinction_divisor);
        m_minus_M = ( m - real_M);




       
      
     
    
   

        myvar = strtod(argv[1], 0);
        //arg2 = atoi(argv[2]);
	
	/* log(pow(10, d)) = [(mv - Mv) + 5] / 5 */

	//if ( argc > 0 )
	

	printf("%lf\n", log(pow(10, myvar)));
        return 0;
}
