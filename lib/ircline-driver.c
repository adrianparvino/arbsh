#include <unistd.h>
#include <string.h> 
#include <stdio.h> 
#include <stdint.h>

/* gshline() */
#include <stdlib.h>
#include <limits.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "../lib/hexen.h"
#include "../lib/ircline.h"


int main(void)
{
        char *userline = malloc(BUFSIZ * sizeof(char));
	size_t len = 0;

	
        while ( 1 )
        {
		userline[0] = '\0'; 
                len = gshline(userline, "[ircline]>> ", 12); 
		//len = gshline(userline, "", 0);
		printf ("Finished line was: \n%s\n", userline);
		gsh_history(userline, len); 
        }
	free(hist);
        return 0;
}


