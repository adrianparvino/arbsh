#include <stdio.h>
#include <wchar.h>
#include <locale.h>



int main(void)
{
	setlocale( LC_ALL, "en_US.utf8" ); 

	char *string = "\u0111\u0107"; 

	wchar_t i = 0;
	while ( i++ < 1000000)
		wprintf (L"%lc", i); 

	write(1, "\n\n\n\n", 4); 
	
	write(1, string, 6); 

	return 0;
}

