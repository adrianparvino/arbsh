

/* very crude hypothetical routines, add floating point support */

double addition(double x, double y)
{
	return (x + y);
}

double multiplication(double x, double y)
{
	size_t bulk = y;
	double hold = x;
	size_t i = 1;
	
	while ( i < y )
	{
		++i;
		
		x+=hold;
		
		
	}

	return x;
	
}

