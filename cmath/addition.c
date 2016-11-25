

/* very crude hypothetical routines, add floating point support */

double addition(double x, double y)
{
	return (x + y);
}

double multiplication(double x, double y)
{
	size_t bulk = y;
	size_t i = 0;
	while ( i < y )
	{
		x+=y;
		++i;
	}
	return x;
	
}

