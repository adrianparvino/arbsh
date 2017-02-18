#include <stdio.h> 

void bernoulli(int lim, double *grid)  
{ 
	int j, k, i;
	double l ,m;

	grid[0]=1.0;
	grid[1]=-0.5;
	for (i= 2; i <= lim; i++) 
	{ 
		m=-(1.0/(i+1.0)-0.5);
		for (k=2; k < i; k++) 
		{
			l=1.0;
			for ( j = 2; j <= k; j++) 
				l *= 1.0*(j+i-k)/j;
			m -= l*grid[k];
		} 
		grid[i] = m;
	} 
	for (i=3; i <= lim; i+=2) 
		grid[i] = 0.0;

}


int main()  
{ 
	double b[100];
	int lim = 40; 
	int i; 

	bernoulli(lim, b); 

	for (i=0; i<2; ++i)
                printf("%d %-20.10lf\n", i, b[i]);

	for (i=2; i<=lim; i+=2) 
		printf("%d %-20.10lf\n", i, b[i]);

	return 0;

}



