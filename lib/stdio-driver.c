#include <stdio.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define HASLIBM
#include "stdio.h"

void testgvprintf(char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	gvprintf(fmt, args);
	va_end(args);
}

int main()
{
	char string[10] = { 'h', 'e', 'l', 'l', 'o', '\0' };
	size_t zutest = 1234567;
	int dtest = -9879871;
	char string1[1000] = { 0 };
	long ltest = 23459999;
	double ftest = 3123.21317892345;
	char *format = "%zu/%d/%s==%zu / %d / %s%c-%c-%c-%ctt%ld==%f\n";

	gprintf("gdprintf:\n");
	gdprintf(2, format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest); 
	gprintf("gprintf:\n");
	gprintf(format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest); 
	gprintf("gsprintf:\n");
	gsprintf(string1, format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest); 
	printf("%s", string1);
	gprintf("gvprintf:\n");
	testgvprintf(format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest); 
	printf("control:\n");
	printf(format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest); 
	fflush(stdout); 
	
	gputchar('\n');
	gputchar('p');
	gputchar('u');
	gputchar('t');
	gputchar('c');
	gputchar('\n');

	
	GFILE *filepointer = gfopen("none", "r");
	char buffer[1024];
	size_t ret = 0;
	ret = gfread(buffer, 1, 10, filepointer);
	gfwrite(buffer, 1, ret, gstdout);
	//gfwrite("testing\n", 1, 8, filepointer);
	gfclose(filepointer);

	ggetchar();
}

