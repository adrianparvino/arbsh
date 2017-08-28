#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct object {
	size_t item; 
	struct object *next;
} object;

object *insert(object *head, size_t item)
{ 
	static object *tail = NULL;
	object *ptr = malloc(sizeof(object));
	ptr->next = NULL;
	ptr->item = item; 
	if (!(head))
		tail = head = ptr;
	else if (tail){
		tail->next = ptr; 
		tail = ptr;
	} 
	return head;
}

void list(object *head)
{ 
	object *ptr = head;
	object *last = NULL;
	while (ptr)
	{
		printf("%zu ", ptr->item); 
		ptr = ptr->next; 
		if (last)
			free(last); 
		last = ptr;
	} 
	if (head)
		free(head);
	printf("\n");
}

int main(int argc, char *argv[])
{
	object *o = NULL;
	for (size_t i = 0; i < 10; i++)
		o = insert(o, i);

	list(o); // 10 9 8 7 6 1 2 3 4 5 
}
