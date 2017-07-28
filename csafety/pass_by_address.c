#include <stdlib.h>
#include <stdio.h>

/*
	C does not support "pass by reference" nonetheless by passing a
	the value of an address to a function accepting a pointer to a 
	pointer to a type we can modify a value in C similiar to C++'s
	"pass by reference". The canonical example of this is getline()
	from the C standard library.

	Presented below is the function pass_bappt() (Pass by address of a
	pointer to a pointer to a type).
*/

struct c { 
        char *rp; 
} c;

typedef struct{ 
        char *rp; 
} bb;

bb d[10]; 

void does_not_work(void *a) 
{
	/* Doesn't work! (obviously) */
	a = "Does not work!";
}

void pass_bappt(void **a) 
{ 
	/*
		"pass by value of an address by a pointer to a pointer to a type"
	*/
	*a = "hello world";
}

int main(void)
{ 
	bb *ff;
	ff = malloc(sizeof(bb));
	ff->rp = malloc(1000);

	ff->rp = "This string should be overwritten with a new pointer to \"hello world\" ";

     	printf("%s\n", ff->rp);

        pass_bappt((void**)&(ff->rp));
   
    	printf("%s\n", ff->rp);
     
      	does_not_work(ff->rp);  /* Doesn't work! (obviously) */
	
	printf("%s\n", ff->rp);
	
	return 0; 
}
