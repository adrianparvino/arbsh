#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <libgen.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <time.h>
#include <pwd.h>
#include <grp.h> 

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void octtoperm(int octal)
{
        switch (octal & S_IFMT) {
                case S_IFBLK: printf("b"); break;
                case S_IFCHR: printf("c"); break;
                case S_IFDIR: printf("d"); break;
                case S_IFIFO: printf("p"); break;
                case S_IFLNK: printf("l"); break;
                case S_IFREG: printf("-"); break;
                case S_IFSOCK: printf("S"); break;
                default: printf("?"); break;

        }

        printf( (octal & S_IRUSR) ? "r" : "-");
        printf( (octal & S_IWUSR) ? "w" : "-");
        printf( (octal & S_IXUSR) ? "x" : "-");
        printf( (octal & S_IRGRP) ? "r" : "-");
        printf( (octal & S_IWGRP) ? "w" : "-");
        printf( (octal & S_IXGRP) ? "x" : "-");
        printf( (octal & S_IROTH) ? "r" : "-");
        printf( (octal & S_IWOTH) ? "w" : "-");

        if ( octal & S_ISVTX && octal & S_IXOTH ) printf("t");
        else if (octal & S_ISVTX ) printf("T");
        else if (octal & S_IXOTH ) printf("x");
        else printf("-");

}

void prnfstats(struct stat sb, int i, int j)
{
	struct group *grp;
        struct passwd *pwd;

        printf(" ");
        if ( i == 1)
              printf("%-8ld ", (long) sb.st_ino);
        printf("%-3ld ", (long) sb.st_nlink);
        if ( j == 1)
                printf("%ld %ld ", (long) sb.st_uid, (long) sb.st_gid);
        else {
               grp = getgrgid(sb.st_gid);
               pwd = getpwuid(sb.st_uid);
               printf("%s ", pwd->pw_name);
               printf("%s ", grp->gr_name);
        }
        printf("%8lld ", (long long) sb.st_size);
        printf("%.16s   ", ctime(&sb.st_mtime)); 
}

