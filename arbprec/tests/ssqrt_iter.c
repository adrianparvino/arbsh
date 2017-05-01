#include <stdio.h>



double mysqrt(double x)
{

        /* babylonian method */
        double y;
        int i;

      
            

        y = x;

        for(i=0; i < ((x / y) / 2) || i < 10 ; i++)
        {
                //y = (( y + (x / y) ) / 2);
		double quo = x / y;
		double sum = y+quo;
		double ret = sum / 2;
		y = ret;
		printf("%10.10lf\n", y);
        }

        return y;
}

int main(int argc, char *argv[])
{
	mysqrt(atoi(argv[1]));
}
