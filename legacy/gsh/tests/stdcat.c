#include <stdio.h>
#include <unistd.h> 

/* Copyright 2015, C. Graff, "stdiocat" */ 

void concatenate(int);

int main()
{ 
	concatenate(STDIN_FILENO); 
	return 0; 
} 


void concatenate(int source)
{ 
        size_t n = 0;
        char buf[BUFSIZ];
        while ((n = read(source, buf, BUFSIZ)) > 0)
                write(STDOUT_FILENO, buf, n); 
}

