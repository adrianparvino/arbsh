#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <netdb.h> 
#include <fnmatch.h> 
#include <sys/types.h>
#include <sys/socket.h> 
#include <limits.h> 
#include <libgen.h> 
#include <fcntl.h>
#include <limits.h> 
#include <fcntl.h>

//#include <linux/limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "lib/cutils.c"




/* 
	Copyright 2015, C. Graff  "fetch" 

	Usage: fetch http://www.gnu.org/index.html

*/ 


void parseurl(char *);
void fetch(char *, char *, char *);
void writeout(int sck, int output); 


int main (int argc, char *argv[])
{ 
	
	/* 
		main() --> parseurl() --> fetch() --> writeout()
	*/ 

	if ( argc == 1 )
		cutilerror("Usage: fetch http://www.some.org/index.html\n", -1); 

	++argv;
	while (*argv) 
		parseurl(*argv++); 

	return 0;
}
void parseurl(char *argv)
{ 
	/* 
                parseurl() --> fetch() --> writeout()
        */

        char *host;
        char *type;
        char *page;

	type = host = page = argv;
	if ( (host = strstr(argv, "://")))
	{
		*host = '\0';
		host += 3;
	}
	if ((page = strstr(host, "/")))
		*page++ = '\0'; 

	printf("Attempting an [%s] protocol on [%s] to retrieve [%s]\n ", type, host, page);
	fetch(type, host, page);
        return;
}

void fetch(char *type, char *host, char *page) 
{
	/*
		fetch() --> writeout()
	*/

        struct addrinfo hints, *res; 
	int sck;
	int output;
	char *message; 


	output = STDOUT_FILENO;

	if (!( message = malloc(PATH_MAX * 2)))
		cutilerror("Insufficient memory", 1);

	memset(&hints, 0, sizeof(hints)); 

	// if ( "http" ) ? 
	if ( strcmp(type, "http") == 0)
        	sprintf(message, "GET /%s HTTP/1.0\r\nHost: %s\r\n\r\n", page, host); 
	else
		cutilerror("Protocol not supported", 0);
        
        hints.ai_family = PF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        if ( ( getaddrinfo(host, type, &hints, &res) ) != 0 )
        	cutilerror("getaddrinfo() failed", 1);

        if ((sck = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
		cutilerror("socket() failed", 1);

        if ( (connect(sck, res->ai_addr, res->ai_addrlen) ) == -1 )
        	cutilerror("connect() failed", 1);

	write(sck, message, strlen(message)); 

	if ((output = open(basename(page), O_CREAT|O_RDWR, S_IRUSR|S_IWUSR)) == -1 )
		cutilerror("open() failed", 1);

	writeout(sck, output);

        freeaddrinfo(res);
        close(sck);
	free(message);
}

void writeout(int sck, int output)
{
	
        size_t i;
	size_t n; 
	int http; 
    	char *buf;
	char *luf;

        if (!(buf = malloc(BUFSIZ) ))
		cutilerror("Insufficient memory", -1);
   
	/* override */
	i = n = http = 0;

	while ( (n = read(sck, buf, BUFSIZ)) > 0 )
        {
                i = 0; 
		if ( http == 0 )
		{
			if ((luf = strstr(buf, "\n\r")))
			{
				i = ( luf - buf ); 
				i += 3;
			}
			http = 1;
		} 
		write(output, buf + i, n - i);
        }
	free(buf);
}


