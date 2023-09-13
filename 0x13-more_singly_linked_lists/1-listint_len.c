#include "lists.h"

/**
* listint_len - returns the number of elements in a linked list
* @h: Pointer to the head of the list
*
* Return: number of elements
*/
size_t listint_len(const listint_t *h)
{
	size_t nnodes = 0;

	while (h != NULL)
	{
	nnodes++;
	h = h->next;
	}

	return (nnodes);
}
