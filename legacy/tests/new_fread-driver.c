#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	char buffer[4096];
	size_t ret = 0;
	if ( argc > 1 )
	{
		FILE *fp = fopen(argv[1], "r");
		while ( (ret = fread(buffer, 1, 4096, fp)) > 0 )
	
			fwrite(buffer, 1, ret, stdout);
		fclose(fp);
	}


	return 0;
}
