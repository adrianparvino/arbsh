#include <stddef.h>

size_t gstrlen(const char *); 
size_t gstrnlen(const char *, size_t); 
int gstrcmp(char *, char *);
char *gstrchr(const char *, int); 
char *gstrcpy(char *, const char *);
char *gstrncpy(char *, const char *, size_t);
char *gstrtok(char *, const char *);
size_t gstrspn(const char *, const char *);
void* gmemset(void *, int, size_t);
void* gmemcpy(void*, const void*, size_t) ;
void *gmemmove(void *, const void *, size_t);
char *gstrdup(const char *);
char *gstrndup(const char *, size_t);
void *gmemchr(const void *, int, size_t);
char *gstrchrnul(const char *, int);

