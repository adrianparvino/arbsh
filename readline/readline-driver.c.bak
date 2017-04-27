#include <unistd.h>
#include <string.h> 
#include <stdio.h> 
#include <stdint.h>

/* gshline() */
#include <stdlib.h>
#include <limits.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "../hexen.h"
#include "../readline.h"


int main(void)
{
        char *userline = malloc(BUFSIZ * sizeof(char));
	size_t len = 0;

	
        while ( 1 )
        {
		userline[0] = '\0'; 
                len = greadline(userline, "[greadline]>> ", 14);
		printf ("Finished line was: \n%s\n", userline);
		gread_history(userline, len); 
        }
	free(hist);
        return 0;
}


