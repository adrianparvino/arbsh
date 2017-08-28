/*

*/

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

object *forpop(object *head, size_t item)
{
	/* modified linked list "holds hands" forwards */
        static object *tail = NULL;
        object *ptr;
	if(!(ptr = malloc(sizeof(object))))
	{
		fprintf(stderr, "Malloc request failed, freeing list\n");
		return head = freeobj(head);
	}
        ptr->next = NULL;
        ptr->i = item;
        if (!(head))
                tail = head = ptr;
        else if (tail){
                tail->next = ptr;
                tail = ptr;
        }
        return head;
}
object *backpop(object *head, size_t i)
{
	/* simple linked list "holds hands" backwards */
	object* o;
	if (!(o = malloc(sizeof(object))))
	{
		fprintf(stderr, "Malloc request failed, freeing list\n");
		return head = freeobj(head);
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

object *placefreeobj(object *hold)
{
	if (hold)
        {
                printf("free(%zu)-->", hold->i);
                hold = safe_free(hold);
        }
	return hold;
}

object *freeobj(object *head)
{
        object *o;
	object *hold = NULL;
        for(o = head;o;o = o->next)
	{
		hold = placefreeobj(hold);
		hold = o; 
	}
	hold = placefreeobj(hold);

	if (o == head)
		printf("Nothing to be freed  ");
        printf("END\n\n");
	return hold;
}

int main(void)
{ 
	size_t i;
	object* head = NULL; 
	for(i = 0; i<=20; i++) 
		head = forpop(head, i); 
	
	iterate(head);
	head = freeobj(head);
	
	for(i = 0; i<=20; i++) 
		head = backpop(head, i); 
	
	iterate(head);
	head = freeobj(head);
	return 0;
}
