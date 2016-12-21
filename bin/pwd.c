#include <unistd.h>
#include "../lib/limits.h"
#include "../lib/string.h"

/* 
        Copyright 2015, C. Graff  `pwd`
*/

int pwd(void);

int main(void)
{
        if(pwd())
		return 1;
	return 0;
}

int pwd(void)
{
        char pwd[GPATH_MAX - 1];
        size_t i = 0;

        if ((getcwd(pwd, GPATH_MAX - 2) ) )
        {
                i = gstrlen(pwd);
                pwd[i] = '\n';
                write(1, pwd, i + 1);
                return 0;
        }
        return 1;
}

