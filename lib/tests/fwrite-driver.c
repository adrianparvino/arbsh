#include <stdio.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define HASLIBM
#include "../stdio.h" 
int main()
{
	char buffer[GBUFSIZ] = { 0 };
	int c = 0;
	ssize_t ret = 0;

	GFILE *filepointer = gfopen("README", "r"); 
	while ( (c = ggetc(filepointer)) != GEOF )
		gputc(c, gstderr); 
	gfclose(filepointer);

	filepointer = gfopen("README", "r"); 
	while ( (c = ggetc(filepointer)) != GEOF )
		gputc(c, gstdout); 
	gfclose(filepointer);
	
	filepointer = gfopen("README", "r"); 
	while ( (ret = gfread(buffer, 1, 1000, filepointer)) > 0 )
		gfwrite(buffer, 1, ret, gstdout);
	gfclose(filepointer); 

}

