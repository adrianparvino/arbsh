
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
int concatenate(int);
size_t date(char *, char *, size_t);
void datewrite(int, char *, size_t, int);

int main(int argc, char *argv[])
{

        if ( argc == 1 )
                concatenate(1);
        while  (*++argv)
                concatenate(open(*argv, O_RDONLY));

	int o;
        size_t n;
	char buf[256];
	char *format;
	/* POSIX specifies this format as date's default */
	char *fallback = "%a %b %e %H:%M:%S %Z %Y"; 

	format = fallback; 
	
	if (!setlocale(LC_CTYPE, ""))
		datewrite(2, "Unable to set locale", 20, 1);


	while ((o = getopt (argc, argv, "u")) != -1)
                switch (o) {
                        case 'u': /* POSIX specifies that -u should set TZ to UTC0 */
                                if((setenv("TZ", "UTC0", 1)) == -1)
					datewrite(2, "Unable to set setenv\n", 21, 1);
    				tzset();
                                break;
			default:
				datewrite(2, "Invalid\n", 8, 1);
				break;
			}

	argv += optind;
        argc -= optind; 

	if ( *argv )
	{
		if ( **argv == '+' )
		{
			++*argv;
			format = *argv;
		}
		else
			datewrite(2, "Date format error?\n", 19, 1);
	} 

	if ((n = date(buf, format, 100)) == 0)
		datewrite(2, "Unable to obtain date\n", 22, 1);

	datewrite(1, buf, n, 0); 
	

	return 0;
}
