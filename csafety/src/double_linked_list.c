#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
	int item;
	struct node *prev;
	struct node *next;
} node;

node *head, *tail;

void inserthead(int item)
{ 
	node *ptr = malloc(sizeof(node));
	ptr->item = item;
	ptr->prev = ptr->next = NULL;

	if (NULL == head) {
		head = tail = ptr; 
	} else {
		ptr->next = head;
		head->prev = ptr;
		head = ptr;
	}
} 
void inserttail(int item)
{ 
	node *ptr = malloc(sizeof(node));
	ptr->item = item;
	ptr->prev = ptr->next = NULL;

	if (NULL == head) {
		head = tail = ptr;
	} else {
		tail->next = ptr;
		ptr->prev = tail;
		tail = ptr;
	} 
} 



void listbackward(node *ptr)
{ 
	while (NULL != ptr)
	{
		printf("%d ", ptr->item);
		ptr = ptr->prev;
	} 
	printf("\n");
}
void listforward(node *ptr)
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
	size_t i;
	for (i = 1; i <= 10; i++)
		inserthead(i);

	listforward(head);
	listbackward(tail);
	
	for (; i <= 20; i++)
		inserttail(i);

	listforward(head);
	listbackward(tail);
}
