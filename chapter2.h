#ifndef CHAPTER2_H
#define CHAPTER2_H

#include <stdlib.h>
#include <stdio.h>

struct Node
{
	int data;
	struct Node *next;
};

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

void appendToTail(List L, int d)
{
	Position TmpCell = new struct Node;
	if (TmpCell == NULL)
		return;
	TmpCell->data = d;
	TmpCell->next = NULL;

	while (L->next != NULL)
		L = L->next;
	L->next = TmpCell;
}

int lengthOfList(List L)
{
	int length = 0;
	while (L->next != NULL)
	{
		length++;
		L = L->next;
	}
	return length;
}

/*
 * Return Position d in L, NULL if not found.
 */
Position find(List L, int d)
{
	Position p;

	p = L->next;
	while (p->next != NULL && p->data != d)
		p = p->next;

	return p;
}

/*
 * If d is not found, then next field of returned Position is NULL
 * Assume a header
 */
Position findPrevious(List L, int d)
{
	Position p;

	p = L;
	while (p->next != NULL && p->next->data != d)
		p = p->next;

	return p;
}

/*
 * Return true if p is the last position in L.
 */
bool isLast(List L, Position p)
{
	return p->next == NULL;
}

/*
 * Delete first occurrence of d from a list.
 */
void deleteNode(List L, int d)
{
	Position previous, tmpCell;
	previous = findPrevious(L, d);

	if (!isLast(L, previous))
	{
		tmpCell = previous->next;
		previous->next = tmpCell->next;
		free(tmpCell);
	}
}

void removeDuplicates(List L)
{
	List current, previous, runner, tmpCell;

	if (L == NULL)
		return;

	current = L->next;
	previous = L;

	while (current != NULL)
	{
		runner = L;
		while (runner != current)
		{
			if (runner->data == current->data)
			{
				printf("duplicate: %d\n", current->data);
				tmpCell = current;
                current = current->next;
                previous->next = current;
				free(tmpCell);
				break;
			}
			runner = runner->next;
		}
		if (runner == current)
		{
			previous = previous->next;
			current = current->next;
		}
	}
}

#endif
