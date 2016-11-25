

double addition(double x, double y)
{
	return (x + y);
}

double multiplication(double x, double y)
{
	size_t bulk = y;
	double hold = x;
	double i = 1;
	double imaginary = 0;

	imaginary = (y - floor(y));
	double floored = floor(y);
	double j = 0;
	
	while ( i < floored )
	{
		i+=1;
		
		x += hold; 
	}

	j = .0001;
	hold /= 10;
	while (j<imaginary + .0001 )
	{
		j += .0001;
		x += hold;
	}
	//imaginary =-j;
	j = .01;
        hold /= 10;
        while ( j < imaginary -1 )
        {
                j += .01;
                x += hold;
        }
	


	printf("imaginary %lf\n", imaginary);

	return x;
	
}

