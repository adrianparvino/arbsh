#include <stdio.h> 
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
        char *inpt;
	
        while ( 1 )
        {
                inpt = readline("Enter texts: ");
                add_history(inpt);
                printf("%s\n", inpt);
        }
        return 0;
}
