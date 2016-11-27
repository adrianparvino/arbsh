#include <stdlib.h>
#include <stdio.h>

/* defines */
#define PASSES 10
#define PLACES 10


/* globals */
size_t count[PLACES]      = { 1000000000, 100000000, 10000000, 1000000, 100000, 10000, 1000, 100, 10, 1 };
double counters[PLACES]   = { .1, .01, .001, .0001, .00001, .000001, .0000001 , .00000001, .000000001, .0000000001};
//size_t imag_count[PLACES] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };

/* functions */
double multiplication(double, double);
double turn_imag(size_t);
size_t turn_real(double);
//void verbose(float, size_t, int, float, float);


int main(int argc, char *argv[])
{
	if ( argc != 3 )
	{
		fprintf(stderr, "2 args\n");
		return 1;
	}
	double x = strtod(argv[1], 0);
	double y = strtod(argv[2], 0);
	double ret = 0;

	//printf("%lf\n", turn_imag(x));
	ret = multiplication(x, y);
	printf("multiplication = %lf\n", ret);
	printf(" x * y = %lf\n", x * y);
	
	return 0;
}



double multiplication(double x, double y)
{

	double xhold = x;
	double ret = 0;
	double i = 1;
	double floored_x = 0;
	double imagine_x = 0;
	double floored_y = 0;
	double imagine_y = 0;

	floored_x = (int)x;
	imagine_x = (x-floored_x);

	floored_y = (int)y;
	imagine_y = (y-floored_y); 
	
	/* deal with whole number part of y */
	for(i=1 ;i <= floored_y; ) /* real y */
	{
		i+=1;
		ret += xhold;
	}
	/* deal with the imaginary part of y */ 
	for (i=1 ;i <= floored_x ;) /* real x */
	{
		i+=1;
		ret += imagine_y;
	}

	/* what remains is imagine_y * imagine_x */
	//printf("imagine_y * imagine_x = %lf\n", (imagine_y * imagine_x));

	//ret += (imagine_y * imagine_x);
	size_t first = turn_real(imagine_y);
	size_t second = turn_real(imagine_x);
	size_t inc = 1;
	size_t hold = first;
	
	/* labor intensive 10's place point calculations ( could reuse mult() .. )*/
	while (inc < second )
	{
		inc++;
		first += hold; 
	}
	
	/* Make the number imaginary again (twice as /10000000000) */
	//ret += (double)first/10000000000/10000000000; 
	first = turn_imag(first);
	ret += turn_imag(first);
	
	return ret;
}



size_t turn_real(double y )
{
	/* disect 10 precision points */ 
	double floored = 0;
	double imagine = 0; 
	int places = 0; 
	double total = 0;
	double movedat = 0; 
	size_t realtot = 0;

	
	/* floor() the fractional number */
	floored = (int)y;
	/* store the fractional part */
	imagine = (y-floored); 

	/* imagine is always less than 1 .... */ 

	/* adjust for empty places */
	while ( counters[places] > imagine )
		++places;

	while ( places < PASSES )
	{ 
		if (( total + counters[places] > imagine ))
		{
			++places; 
			//printf("movedat %lf\n", movedat);
			movedat = 0;
		}
		
		movedat += counters[places];
		realtot += count[places];
		total += counters[places];
		
		if (!(total < imagine)) 
			break; 
	} 

	printf("total %.10lf\n", total);
	printf("realtot %zu\n", realtot); 
	printf ("places  %d\n",  places);
	printf ("floored %lf\n", floored);
	printf ("imagine %lf\n", imagine); 
	return realtot;
}



double turn_imag(size_t y)
{
	int places = 0; 
	size_t total = 0; 
	double realtot = 0; 
	
	/* adjust places counting magnitude */
	while ( count[places] > y )
		++places;

	while ( places < PASSES )
	{ 
		if (( total + count[places] > y )) 
			++places; 

		realtot += counters[places];
		total += count[places]; 
	}
	
	printf("total = %zu\n", total);
	printf("realtot = %lf\n", realtot);

	return realtot;
}


