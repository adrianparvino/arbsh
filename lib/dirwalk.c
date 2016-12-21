#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

char *depths[100];



/* overflow safe tree traversal */

void printdir(char *dir, int depth)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	int spaces = depth*4;

	if((dp = opendir(dir)) == NULL) {
		fprintf(stderr,"cannot open directory: %s\n", dir);
		return;
	}
	chdir(dir);
	while((entry = readdir(dp)) != NULL) { 
		if ( entry->d_type == DT_DIR )
		{
			if(strcmp(".",entry->d_name) == 0 || 
			strcmp("..",entry->d_name) == 0)
				continue;
			printf("%*s%s/\n",spaces,"",entry->d_name);
			// add a path depth
			//depths[depth] = dir;
			// print all depths
			//size_t i = 0;
			//while ( i < depth)
			//	printf("%s", depths[i++]);
			/* Recurse at a new indent level */
			printdir(entry->d_name,depth+1);
			
		}
		else {
			size_t j = 0;
                        //while ( j < depth)
                        //        printf("%s/", depths[j++]);
			//printf("%s\n",entry->d_name);
			printf("%*s%s\n",spaces,"",entry->d_name);
		}
	}
	chdir("..");
	closedir(dp);
}

/*  Now we move onto the main function.  */

int main(int argc, char* argv[])
{
	char *topdir, pwd[2]=".";
	if (argc != 2)
		topdir=pwd;
	else
		topdir=argv[1];

	printf("Directory scan of %s\n",topdir);
	printdir(topdir,0);
	printf("done.\n");

	return 0;
}
