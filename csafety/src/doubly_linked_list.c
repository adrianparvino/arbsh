/*
[x] prev <-[o]
           [o]->next = [o]
           [o] = prev<-[o]
                       [o]->next = [o]
                       [o] = prev<-[o]
                                   [o]->next = [o]
                                   [o] = prev<-[o] 
                                               [o]->next = [o]
                                               [o] = prev<-[o]
                                                           [o]->next = [x]
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct object {
	size_t i;
	void *addr;
	struct object *prev;
	struct object *next;
} object;

object *initlist(size_t);

size_t objectsize(void)
{
	return sizeof(object);
}

void *safe_free(void *a)
{
        free(a);
        return NULL;
}

void *verbose_malloc(size_t i)
{
        void *ret;
        if (!(ret = malloc(i)))
                perror("malloc error: ");
        return ret;
}

object *insertnode(object *o, size_t i)
{ 
	object *ptr = initlist(i);
	ptr->prev = o;
	ptr->next = o->next;
	o->next->prev = ptr;
	o->next = ptr; 
	return ptr;
}

object *deletenode(object *o)
{ 
	object *tmp = o->prev;
	o->prev->next = o->next;
	o->next->prev = o->prev; 
	safe_free(o);
	return tmp;
}

object *initlist(size_t i)
{
	object *ptr = verbose_malloc(objectsize());
	if (!(ptr))
		return NULL;
        ptr->i = i;
	/* terminal NODES [x]<--[ ]-->[x] */
        ptr->prev = ptr->next = NULL; 
	return ptr;
}

object *addhead(object *o, size_t i)
{ 
	object *ptr = initlist(i); 
	ptr->next = o;
	o->prev = ptr;
	return ptr;
} 

object *addtail(object *o, size_t i)
{
	object *ptr = initlist(i); 
	ptr->prev = o;
	o->next = ptr;
	return ptr;
} 

void listbackward(object *ptr)
{ 
	for(;ptr;ptr = ptr->prev)
		printf("%zu ", ptr->i); 
	printf("\n\n");
}

void listforward(object *ptr)
{
	for(;ptr;ptr = ptr->next)
		printf("%zu ", ptr->i);
	printf("\n\n");
}

object *placefreeobj(object *hold)
{
        if (hold) 
        	printf("free(%zu)--> ", hold->i);
        return safe_free(hold);
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
	size_t i = 0; 
	object *head = NULL;
	object *tail = NULL;
	object *o;

	/* create */
	tail = head = initlist(i);

	/* add to tail */
	for (i =1; i <= 20; i++) 
		tail = addtail(tail, i); 
	listforward(head);
	listbackward(tail);

	/* add to head */
	for (i=30; i <= 40; i++)
		head = addhead(head, i); 
	listforward(head);
	listbackward(tail); 
	
	/* node deletion */
        for(i=0,o = head;o;o = o->next,++i)
                if (i >3 && i < 13)
			o = deletenode(o); 
	listforward(head);
	listbackward(tail); 

	/* node insertion */
        for(i=0,o = head;o;o = o->next,++i)
                if (i >3 && i < 13)
			o = insertnode(o, i); 
	listforward(head);
	listbackward(tail);

	/* free the list and NULL the root and tail nodes */
	tail = head = freeobj(head); 
	return 0; 
}
