#include <unistd.h>



int main()
{
	/*
		The sync utility is just a wrapper for the 
		sync() function 
	*/
	sync();
	return 0;
}
