#include <stdio.h>
#include <string.h> 

int main(int argc, char *argv[])
{
	FILE *fp;
	char b[1024], *p, *h;

	if (argc != 2 || (fp = fopen(argv[1], "r")) == NULL)
		{ fputs("needs file\n", stderr); return 1; };

	for (;(fgets(b, 1024, fp)) != NULL;)
	{ 
		for(h=b;(p = strchr(h, ' ')) != NULL;h=p)
		{
			*p++ = '\0';
			printf("%s\n", h);
		}
	}
	return 0;
}


