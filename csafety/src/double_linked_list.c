#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct object {
	int item;
	struct object *prev;
	struct object *next;
} object;

object *deletenode(object *o)
{ 
	object *tmp = o->prev;
	o->prev->next = o->next;
	o->next->prev = o->prev; 
	free(o);
	return tmp;
}

object *inserthead(object *head, object *tail, int item)
{ 
	object *ptr = malloc(sizeof(object));
	ptr->item = item;
	ptr->prev = ptr->next = NULL;

	if (NULL == head) {
		head = tail = ptr; 
	} else {
		ptr->next = head;
		head->prev = ptr;
		head = ptr;
	}
	return head;
} 

object *inserttail(object *head, object *tail, int item)
{ 
	object *ptr = malloc(sizeof(object));
	ptr->item = item;
	ptr->prev = ptr->next = NULL;

	if (NULL == head) {
		head = tail = ptr;
	} else {
		tail->next = ptr;
		ptr->prev = tail;
		tail = ptr;
	} 
	return tail;
} 

void listbackward(object *ptr)
{ 
	while (NULL != ptr)
	{
		printf("%d ", ptr->item);
		ptr = ptr->prev;
	} 
	printf("\n");
}

void listforward(object *ptr)
{ 
	while (NULL != ptr)
	{
		printf("%d ", ptr->item);
		ptr = ptr->next;
	} 
	printf("\n");
}

int main(int argc, char *argv[])
{
	size_t i = 0;

	object *head = NULL;
	object *tail = NULL;
	tail = head = inserthead(head, tail, i);
	//tail = head = inserttail(tail, head, i); 

	for (i =1; i <= 20; i++) 
		tail = inserttail(head, tail, i); 
	
	
	listforward(head);
	listbackward(tail);

	//for (i=100; i <= 110; i++)
	//	head = inserthead(head, tail, i); 
	

	//listforward(head);
	//listbackward(tail);
	
	object *o;
        for(i=0,o = head;o;o = o->next,++i)
                if (i >3 && i < 13)
			o = deletenode(o);
               

	listforward(head);
	listbackward(tail);
	return 0; 
}
