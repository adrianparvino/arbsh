#include <string.h> 
#include <stdio.h> 
#include <stdint.h>

#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* gshline() */
#include <stdlib.h>
#include <limits.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "../clib/ansicode.h"
#include "../clib/editor.h"


int main(int argc, char *argv[])
{
	int fp;
	size_t len;
	char *userline;
	char *string = "Untitled.txt";

	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

	if ( argc > 1 ) 
	{
		++argv;
		string = *argv;
	}
	fp = open(string, O_RDWR|O_CREAT, mode);

	len = lseek(fp, 0, SEEK_END);
        lseek(fp, 0, SEEK_SET); 
	/* 
		These malloc()'ed sizes are hacks and must be
		dynamically allocated from the editor's getch 
	*/
	userline = malloc(sizeof(char) * (len + BUFSIZ));
        read(fp, userline, len); 

	hglb.laro = len;
        gshline(userline, len, fp);

	//free(hist);
        return 0;
}
