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

void list(node *ptr)
{ 
	while (NULL != ptr) {
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

	list(head); // 10 9 8 7 6 1 2 3 4 5 
	
	for (; i <= 20; i++)
		inserttail(i);

	list(head); // 10 9 8 7 6 1 2 3 4 5 
}
