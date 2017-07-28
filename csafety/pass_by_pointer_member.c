#include <stdlib.h>
#include <stdio.h> 
/*
	C does not support "pass by reference" noentheless by passing a
	pointer to the first member of an object as an argument to a function
	and supplying the address of that member to the function at runtime we 
	can determine a permanent memory address with which to write. 
*/

struct c { 
        char *rp; 
} c;

typedef struct{ 
        char *rp; 
} bb;

bb d[10]; 

void normal_way(void *a) 
{ 
	/* doesn't work ! */
	a = "Does not work!";
}

void pass_bpm(void **a) 
{ 
	free(*a); 
	*a = "hello world";
}

int main(void)
{ 
	bb *ff;
	ff = malloc(sizeof(bb));
	ff->rp = malloc(1000);

        pass_bpm((void**)&(ff->rp));
   
    	printf("%s\n", ff->rp);
     
      	normal_way(ff->rp);  /* doesn't work */
	
	printf("%s\n", ff->rp);
        
	
	return 0; 
}
