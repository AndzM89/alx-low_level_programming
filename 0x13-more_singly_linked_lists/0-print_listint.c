#include "lists.h"
#include <stdio.h>

/**
* print_listint - prints all the elements of a linked list
* @h: Pointer to the head of the list
*
* Return: number of nodes
*/
size_t print_listint(const listint_t *h)
{
	size_t nnodes = 0;

	while (h != NULL)
	{
		nnodes++;
		printf("%d\n", h->n);
		h = h->next;
	
	}

	return (nnodes);
}
