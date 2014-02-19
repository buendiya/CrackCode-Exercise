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
	Position TmpCell = (Position)malloc(sizeof(struct Node));
	if (TmpCell == NULL)
		return;
	TmpCell->data = d;
	TmpCell->next = NULL;

	while (L->next != NULL)
		L = L->next;
	L->next = TmpCell;
}

/*
 * Return length of List.
 * Assume use of a header node.
 */
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
 * Assume use of a header node.
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
 * Assume use of a header node.
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

/*
 * Remove duplicates from an unsorted linked list.
 * ¡°current¡± does a normal iteration,
 * while ¡°runner¡± iterates through all prior nodes to check for dups.
 */
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

/*
 * Find the nth to last element of a singly linked list.
 */
Position nthToLast(List L, int n)
{
	Position p1 = L, p2 = L;

	while (n-- > 0)		//skip n-1 head
	{
		if (p1 == NULL)
			return NULL;	//not found since list size < n
		p1 = p1->next;
	}

	while (p1->next != NULL)
	{
		p1 = p1->next;
		p2 = p2->next;
	}

	return p2;
}

/*
 * Add two numbers each represented by linked list and return the sum as a linked list.
 */
List addList(List L1, List L2, int carry)
{
	if (L1 == NULL && L2 == NULL)
		return NULL;

	List result = (List)malloc(sizeof(struct Node));
	int value = carry;
	if (L1 != NULL)
		value += L1->data;
	if (L2 != NULL)
		value += L2->data;

	result->data = value % 10;
	List more = addList(L1 == NULL ? NULL : L1->next,
						L2 == NULL ? NULL : L2->next,
						value / 10);

	result->next = more;
	return result;
}







#endif
