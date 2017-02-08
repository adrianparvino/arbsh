#include "../stddef/stddef.h"
#include "../string/string.h"

static int arb_str_verbosity = 0;
char *mirror;
char *tmpmir;

char *add(char *, char *, char *);
char *addition(char *, char *, char *);
void die(char *);
int getcharval(char *, size_t);
char *multiply(char *, char *, char *);
void print_real(char *, char *);
size_t reversestr(char *);
void setsign(char *);
void *strallocate(size_t);
char *subtract(char *, char *, char *);
char *subtraction(char *, char *, char *);
char *arb_str_divide(char *, char *, char *);
