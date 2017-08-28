#include <stdio.h>
#include <stdlib.h>

typedef struct object{ 
	size_t i;
	struct object *next;
} object; 

object *freeobj(object*);

void *safe_free(void *a)
{
        free(a);
        return NULL;
}

object *populate(object *head, size_t i)
{
	object* o;
	if (!(o = malloc(sizeof(object))))
	{
		fprintf(stderr, "Malloc request failed, freeing list\n");
		return head = freeobj(head);/* NULL */
	}
	o->i = i; 
	o->next = head;
	return o; 
}

void iterate(object* head)
{
	object *o;
	for(o = head;o;o = o->next)
		printf("(%zu)-->", o->i); 
	printf("END\n\n");
}

object *freeobj(object* head)
{
        object *o;
	object *hold = NULL;
        for(o = head;o;o = o->next)
	{
		if (hold) 
		{
			printf("free(%zu)-->", hold->i);
                	hold = safe_free(hold); 
		}
		hold = o; 
	}
	if (hold)
	{
		printf("free(%zu)-->", hold->i);
		hold = safe_free(hold);
	}
	if (o == head)
		printf("Nothing to be freed  ");
        printf("END\n\n");
	return hold;
}

int main(int argc, char const *argv[])
{ 
	size_t i;
	object* head = NULL;

	for(i = 0; i<=20; i++) 
		head = populate(head, i);
	head = populate(head, i);
	head = populate(head, i);
	iterate(head);
	iterate(head); 
	head = freeobj(head);
	head = freeobj(head);
	head = freeobj(head);
	return 0;
}
