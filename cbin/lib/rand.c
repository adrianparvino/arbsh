

unsigned long int randnext = 1;

int rand(void)
{
	randnext = randnext * 1103515245 + 12345;
	return (unsigned int)( randnext / 65536 ) % 32768;
}

void srand(unsigned int seed)
{
	randnext = seed;
}


