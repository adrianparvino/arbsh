#include <gstdio.h>

void simple_copy(char *src, char *dest)
{
	int c = 0;
	GFILE *fpsrc = gfopen(src, "r");
	GFILE *fpdest = gfopen(dest, "w");
	while ((c = ggetc(fpsrc)) != EOF) 
		gputc(c, fpdest);
	gfclose(fpsrc);
	gfclose(fpdest);
}

void simplecat(char *file)
{
	int c = 0;
	GFILE *fp = gfopen(file, "r+");
	while ((c = ggetc(fp)) != EOF)
		gputc(c, gstdout);
	gfclose(fp);
}

void testgvprintf(char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	gvprintf(fmt, args);
	va_end(args);
}

int main(int argc, char *argv[])
{

	char string[10] = { 'h', 'e', 'l', 'l', 'o', '\0' };
	size_t zutest = 1234567;
	int dtest = -9879871;
	char string1[1000] = { 0 };
	long ltest = 23459999;
	double ftest = 3123.21317892345;
	double ftest2 = 0.202309823709099;
	char *format = "%zu/%d/%s==%zu / %d / %s%c-%c-%c-%ctt%ld==%f==%lf\n";
	

	if ( argc == 2 ) 
		simplecat(argv[1]); 
	else if ( argc == 3) 
		simple_copy(argv[1], argv[2]); 
	else {

		gfprintf(gstdout, "decimal value of 987654         %d\n", 987654);
		gfprintf(gstdout, "octal value of 987654           %o\n", 987654);
		gfprintf(gstdout, "hexadecimal value of 987654     %x\n", 987654);
		gfprintf(gstdout, "The string literal \"987654\"     %s\n", "987654");
		gfprintf(gstdout, "decimal value of -987654        %d\n", -987654);

		
		gdprintf(1, "decimal value of 987654         %d\n", 987654);
		gdprintf(1, "octal value of 987654           %o\n", 987654);
		gdprintf(1, "hexadecimal value of 987654     %x\n", 987654);
		gdprintf(1, "The string literal \"987654\"     %s\n", "987654");
		gdprintf(1, "decimal value of -987654        %d\n", -987654);


		//gprintf("gfprintf:\n");
		//gfprintf(gstderr, format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest, ftest2);

		//gprintf("gdprintf:\n");
		//gdprintf(2, format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest, ftest2);
		gprintf("gprintf:\n");
		gprintf(format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest, ftest2);
		gprintf("gsprintf:\n");
		gsprintf(string1, format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest, ftest2);

		gprintf("gvprintf:\n");
		testgvprintf(format, zutest, dtest, string, zutest, dtest, string, 'a', 'b', 'c', 'd', ltest, ftest, ftest2);


	
		gprintf("%f\n", 43.6565123987324987132479183478173408712409710471249999);
		gprintf("%f\n", 21.111111111111111111111111111111111111111111111111111111);

		gprintf("%f\n", 3.1);
		//gprintf("%s\n", "a");

		gprintf("P\n");

		double two = 2;
		gprintf("%f\n", two);

		gprintf("%ld\n", 10);
		gprintf("%d\n", 0);
		gprintf("%zu\n", 11);

	}
	return 0;
}





