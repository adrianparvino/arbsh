#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
	int item;
	struct node *prev;
	struct node *next;
} node;

node *head, *tail;

void insert(int item, bool at_tail)
{
	node *ptr = malloc(sizeof(node));
	ptr->item = item;
	ptr->prev = ptr->next = NULL;

	if (NULL == head) {
		head = tail = ptr;
	} else if (at_tail) {
		tail->next = ptr;
		ptr->prev = tail;
		tail = ptr;
	} else {
		ptr->next = head;
		head->prev = ptr;
		head = ptr;
	}
} 

void list()
{
	node *ptr = head;

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
		insert(i, i < 6);

	list(); // 10 9 8 7 6 1 2 3 4 5 
}
