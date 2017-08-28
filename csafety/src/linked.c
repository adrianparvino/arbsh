#include <stdio.h>
#include <stdlib.h>

typedef struct object{
	int value;
	struct object *next;
} object; 

object *populate(object *head, int value)
{
	object* o = malloc(sizeof(object));
	o->value = value; 
	o->next = head;
	return o; 
}

void iterate(object* head)
{
	object *o;
	for(o = head;o;o = o->next)
		printf("[%d]-->", o->value); 
	printf("END\n\n");
}

void freeobj(object* head)
{
        object *o;
	object *hold = NULL;
        for(o = head;o;o = o->next)
	{
		if (hold) 
                	free(hold); 
		hold = o; 
	}
	
	free(hold);
        printf("free\n\n");
}
int main(int argc, char const *argv[])
{
	object* head = NULL;
	size_t i;

	object *hold = head;
	for(i = 0; i<=20; i++) 
		head = populate(head, i);

	iterate(head); 
	
	iterate(head); 
	freeobj(head);
	
	return 0;
}
