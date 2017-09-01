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

size_t objectsize()
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
	free(o);
	return tmp;
}

object *initlist(size_t i)
{
	object *ptr = verbose_malloc(objectsize());
	if (!(ptr))
		return NULL;
        ptr->i = i;
        ptr->prev = ptr->next = NULL;
	return ptr;
}

object *addhead(object *head, object *tail, size_t i)
{ 
	object *ptr = initlist(i); 
	ptr->next = head;
	head->prev = ptr;
	head = ptr;
	return head;
} 

object *addtail(object *head, object *tail, size_t i)
{
	object *ptr = initlist(i); 
	tail->next = ptr;
	ptr->prev = tail;
	tail = ptr; 
	return tail;
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
        {
                printf("free(%zu)--> ", hold->i);
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
	size_t i = 0;

	object *head = NULL;
	object *tail = NULL;
	object *o;
	tail = head = initlist(i);

	for (i =1; i <= 20; i++) 
		tail = addtail(head, tail, i);
	
	listforward(head);
	listbackward(tail);

	for (i=30; i <= 40; i++)
		head = addhead(head, tail, i); 

	listforward(head);
	listbackward(tail); 
	
        for(i=0,o = head;o;o = o->next,++i)
                if (i >3 && i < 13)
			o = deletenode(o); 

	listforward(head);
	listbackward(tail); 
	
        for(i=0,o = head;o;o = o->next,++i)
                if (i >3 && i < 13)
			o = insertnode(o, i);
               
        for(i=0,o = tail;o;o = o->prev,++i)
                if (i == 10 || i == 11)
			o = insertnode(o, i);

	listforward(head);
	listbackward(tail);

	freeobj(head);
	return 0; 
}
