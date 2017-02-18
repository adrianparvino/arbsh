#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/klog.h> 

/* (Copyright) 2014, , "dmesg.c", C. Graff */ 

int main(int argc, char *argv[])
{ 

	size_t logleng = klogctl(10, NULL, 0); 
	size_t c = 0; 
	int o, clrbuf = 0;

	while ((o = getopt (argc, argv, "hcs:")) != -1)
                switch (o) { 
			case 'c': clrbuf = 1; continue;
                        case 's': logleng = atoi(optarg); continue;
			case 'h': printf("Usage:  dmesg [OPTION]\n");
				  printf(" -c  clear the ring buffer\n");
				  printf(" -s  buffer size (1 = 1 char)\n");
				  exit(0);
                        default: break;
                }
        

	char buffer[logleng];
	klogctl(3, buffer, logleng);

	while ( buffer[c] != '\0' )
	{
		printf("%c", buffer[c]);
		if ( buffer[c] == '\n' )
                       c += 3;
		c++;
	}

	if ( clrbuf == 1 )
		klogctl(5, NULL, logleng);

	return 0; 
}

