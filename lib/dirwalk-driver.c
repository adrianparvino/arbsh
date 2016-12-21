#include <stdio.h>
#include <dirent.h>
#include <fnmatch.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include "dirwalk.h"

int find_pattern(char *, size_t, size_t);

int main(int argc, char *argv[])
{
	if (argc > 1)
		find_pattern(argv[1], strlen(argv[1]), 0);
	else
		find_pattern(".", 1, 0);
	return 0;
}

