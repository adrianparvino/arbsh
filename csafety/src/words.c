#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *fp = fopen(argv[1], "r");
	char buffer[1024], *p, *h;
	
	while ((fgets(buffer, 1024, fp)) != NULL)
	{
		h = buffer;
		for(h = buffer;(p = strchr(h, ' ')) != NULL;h=p)
		{
			*p++ = '\0';
			printf("%s\n", h); 
			h = p; 
		}
	}
	return 0;
}
