#include <stdio.h> 
#include <mntent.h> 
#include <sys/vfs.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h> 
#include "lib/cutils.c"
/* Copyright 2015, C. Graff  "df" */

void df_human(unsigned long long);


int main(int argc, char *argv[])
{ 

	int o, human = 0;
	int good, i = 0;
	unsigned long long size, avail, used;
	struct mntent *ent;
        struct statfs fs;
	FILE *f; 

	while ((o = getopt (argc, argv, "h")) != -1)
                switch (o) { 
                        case 'h': 
				human = 1; 
				break;
			case '?': 
				cutilerror("Usage:  df [-h] [PATH(S)]\n", 0); 
				break;
			default:
				break; 
                }

	argv += optind;
        argc -= optind; 

	
	f = setmntent("/etc/mtab", "r");
	if ( !(f) )
		cutilerror("/etc/mtab ", 1);

	printf("%-13s ", "Filesystem");

	if ( human == 1 ) 
		printf("%13s ", "Size");
        else 
		printf("%13s ", "1K-blocks"); 

	printf("%13s ", "Used");
        printf("%13s ", "Available"); 
	printf("%s ", "Use% ");
        printf("%s ", "Mounted on");
	printf("\n");
     
	while ( ( ent = getmntent(f)) ) 
	{ 
		statfs(ent->mnt_dir, &fs); 
		
		size = fs.f_blocks * fs.f_bsize / 1024; 
                avail = fs.f_bavail * fs.f_bsize / 1024; 
		used = fs.f_blocks - fs.f_bfree;
		used *= (fs.f_bsize / 1024); 
		good = 1;
		if ( argc > 0 ) 
			good = 0;
		for (i=0;argc > 0  && i < argc ; ++i)
		{
			basename(argv[i]);
			if (strcmp(argv[i], ent->mnt_dir) == 0)
				good = 1;
		} 
		if ( good == 1)
		{
			printf("%-13s ", ent->mnt_fsname);
			if ( strlen(ent->mnt_fsname) > 13 ) 
				printf("\n%-13s ",""); 
			
			if ( human == 1 ) 		
			{ 
				df_human(size);
				df_human(used);
				df_human(avail);
			}
			else {
				printf("%13llu ", size);
          	     	        printf("%13llu ", used);
               		        printf("%13llu ", avail);
			}
       
			printf("%3.0f%%  ", (100*(float)used)/(size + 1) + .5);
			printf("%-13s ", ent->mnt_dir);
			printf("\n"); 
		}
 	} 
	endmntent(f); 
	return 0;
}


void df_human(unsigned long long value)
{ 
	char string[100];
	int mult = 1;
	char z = 'k'; 
	if( value > 1024 ) 
	{ 
		z = 'M' ; 
		mult *= 1024; 
	}
	if( value > 1024 * 1024 ) 
	{ 
		z = 'G' ; 
		mult *= 1024; 
	} 
	sprintf(string, "%3.1f%c", (float)value / mult, z );
	printf("%13s ", string ); 
} 

