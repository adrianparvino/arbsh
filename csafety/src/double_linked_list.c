#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
	int item;
	struct node *prev;
	struct node *next;
} node;

node *head, *tail;

node *inserthead2(node *tal, node *hed, int item)
{ 
	node *ptr = malloc(sizeof(node));
	ptr->item = item;
	ptr->prev = ptr->next = NULL;

	if (NULL == hed) {
		hed = tal = ptr; 
	} else {
		ptr->next = hed;
		hed->prev = ptr;
		hed = ptr;
	}
	return hed;
}

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


node *inserttail2(node *hed, node *tal, int item)
{ 
	node *ptr = malloc(sizeof(node));
	ptr->item = item;
	ptr->prev = ptr->next = NULL;

	if (NULL == hed) {
		hed = tal = ptr;
	} else {
		tal->next = ptr;
		ptr->prev = tal;
		tal = ptr;
	} 
	return tal;
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

	node *hed = NULL;
	node *tal = NULL;
	tal = hed = inserthead2(tal, hed, 0);
	for (i = 1; i <= 10; i++)
		hed = inserthead2(tal, hed, i);
	listforward(hed);
	listbackward(tal);


	for (i; i <= 20; i++)
		tal = inserttail2(hed, tal, i);
	listforward(hed);
	listbackward(tal);

	return 0;
	for (i = 1; i <= 10; i++)
		inserthead(i);

	listforward(head);
	listbackward(tail);
	
	for (; i <= 20; i++)
		inserttail(i);

	listforward(head);
	listbackward(tail);
}
