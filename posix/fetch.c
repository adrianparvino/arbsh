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
#include "../legacy/lib/cutils.h" 

/* 
	Copyright 2015, C. Graff  "fetch"
	Usage: fetch http://www.gnu.org/index.html
*/

void parseurl(char *);
void fetch(char *, char *, char *);
void writeout(int, int);

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
	/* break apart the user's arg string and get the various parts */
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

	/* allocate memory for the message */
	if (!( message = malloc(PATH_MAX * 2)))
		cutilerror("Insufficient memory", 1);

	/* initialise the addrinfo networking structure */
	memset(&hints, 0, sizeof(hints));
	
	/* ensure that the user is actually requesting http */
	if ( strcmp(type, "http") == 0)
		/* create the message we will send to the remote server */
		sprintf(message, "GET /%s HTTP/1.0\r\nHost: %s\r\n\r\n", page, host); 
	else
		cutilerror("Protocol not supported", 0);
	
	/* set some addrinfo networking structure values */
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	/* invoke getaddrinfo() and pass the network structure in */
	if ((getaddrinfo(host, type, &hints, &res)) != 0)
		cutilerror("getaddrinfo() failed", 1);

	/* create the socket over which we will communicate */
	if ((sck = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
		cutilerror("socket() failed", 1);

	/* perform the actual connection */
	if ( (connect(sck, res->ai_addr, res->ai_addrlen) ) == -1 )
		cutilerror("connect() failed", 1);

	/* communicate our request to the remote server */
	write(sck, message, strlen(message)); 

	/* create the output file on the host */
	if ((output = open(basename(page), O_CREAT|O_RDWR, S_IRUSR|S_IWUSR)) == -1 )
		cutilerror("open() failed", 1);

	/* write all of the data into the output file */
	writeout(sck, output);

	/* free up any unneeded resources */
	freeaddrinfo(res);
	close(sck);
	free(message);
}

void writeout(int sck, int output)
{
	/*
		This function writes data to the user's file after
		stripping the http header at "\n\r"  
	*/
	size_t i;
	size_t n; 
	int lever; 
    	char *buf;
	char *luf;

	if (!(buf = malloc(BUFSIZ) ))
		cutilerror("Insufficient memory", -1);
   
	/* override */
	i = n = lever = 0;

	while ( (n = read(sck, buf, BUFSIZ)) > 0 )
	{
		i = 0;
		if (lever == 0)
		{
			/* detect the http header */
			if ((luf = strstr(buf, "\n\r")))
			{
				/* strip the http header off */
				i = (luf - buf); 
				i += 3;
			}
			lever = 1;
		} 
		/* actually write the data out to the file */
		write(output, buf + i, n - i);
	}
	free(buf);
}


