#include <stdlib.h>
#include <stdio.h>
/*
C does not support "pass by reference" nonetheless by passing the value of an 
address to a function which accepts a pointer to a pointer to a type we can 
modify a value in C similar to C++'s "pass by reference".  The canonical 
example of this is getline() from the C standard library.

Presented below is the function pass_bappt() (Pass by address of a pointer 
to a pointer to a type).
*/
	typedef struct{ 
	        char *rp;
	} object;
	
	void does_not_work(char *a) 
	{
		/* Doesn't work! */
		a = "Does not work!";
	}

	void pass_bappt(char **a) 
	{
		*a = "hello world";
	}

	int main(void)
	{ 
		object *o;
		if(!(o = malloc(sizeof(object))))
			return 1;
		o->rp = "Pointer to a string literal"; 
	     	printf("%s\n", o->rp); 
	        pass_bappt(&(o->rp)); /* note the '&' */ 
	    	printf("%s\n", o->rp); 
	      	does_not_work(o->rp);  /* Doesn't work! (obviously) */ 
		printf("%s\n", o->rp);
		free(o);
		return 0; 
	}
