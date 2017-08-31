/*
Singly linked lists can be created such that the ->next members point in either
direction. The simplest possible singly linked list builds this chain backwards
sometimes leading people to believe that it needs to be reversed. Such reversal
is unneeded as the linked list can be simply created going the opposite
direction. Presented below are the functions forpop and backpop which create a
forward and backward populated linked list respectively,
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

	void *verbose_malloc(size_t i)
	{
		void *ret;
		if (!(ret = malloc(i))) 
			perror("malloc error: ");
		return ret;
	}

	object *forpop(object *head, size_t i)
	{
		/* modified linked list shares members forwards */
	        static object *tail = NULL;
	        object *ptr;
		if(!(ptr = verbose_malloc(sizeof(object))))
			return head = freeobj(head);

	        ptr->next = NULL;
	        ptr->i = i;
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
		/* simple linked list shares members backwards */
		object* o;
		if (!(o = verbose_malloc(sizeof(object))))
			return head = freeobj(head);
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

	object *joinobj(object *o)
	{
		object *tmp = o->next; 
		o->next = o->next->next;
		free(tmp);
		return o;
	}

	int main(void)
	{ 
		size_t i;
		object* head = NULL; 
		for(i = 0; i<=20; i++) 
			if (!(head = forpop(head, i)))
				return 1;
	
		iterate(head);
		head = freeobj(head);
	
		for(i = 0; i<=20; i++) 
			if (!(head = backpop(head, i)))
				return 1; 
                       

		iterate(head);

		
       		object *o; 
                for(i=0,o = head;o;o = o->next,++i) 
			if (i == 10)
				o = joinobj(o); 

		iterate(head);
	
		head = freeobj(head); 
		return 0;
	}

