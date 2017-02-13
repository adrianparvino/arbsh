#include <stdio.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define HASLIBM
#include "../stdio.h"

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
	double ftest2 = 0.202309823709099;
	char *format = "%zu/%d/%s==%zu / %d / %s%c-%c-%c-%ctt%ld==%f==%lf\n";

	gprintf("gfprintf:\n");
	gfprintf(gstderr, format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest, ftest2); 

	gprintf("gdprintf:\n");
	gdprintf(2, format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest, ftest2); 
	gprintf("gprintf:\n");
	gprintf(format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest, ftest2); 
	gprintf("gsprintf:\n");
	gsprintf(string1, format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest, ftest2); 
	printf("%s", string1);
	gprintf("gvprintf:\n");
	testgvprintf(format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest, ftest2); 
	printf("control:\n");
	printf(format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest, ftest2); 
	fflush(stdout); 
	return 0;
}
