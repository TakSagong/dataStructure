#ifndef __LIST_H__
#define __LIST_H__

#define _CRT_SECURE_NO_WARNINGS
#define NUM 10
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	int num;
	struct node* next;
} NODE;

typedef NODE* LINK;


void erase(NODE ** ptr)
{
    NODE * temp;
    while (*ptr)
    {
        temp = *ptr;
        *ptr = (*ptr)->next;
        free(temp);
    }
} //head의 주소값읇 받아서 끝까지 노드를 free시킨다.

NODE * invert(NODE * lead)
{
    NODE * middle, *trail;
    middle = NULL;
    while (lead)
    {
        trail = middle;
        middle = lead;
        lead = lead->next;
        middle->next = trail;
    }
    return middle; // middle이 head가 된다.
}

NODE * concatenate(NODE *ptr1, NODE* ptr2)
{
    NODE * temp;
    
    if (!ptr1) return ptr2;
    if (!ptr2) return ptr1;

    for (temp = ptr1; temp != NULL; temp = temp->next);

    temp->next = ptr2;

    return ptr1;
}

#endif