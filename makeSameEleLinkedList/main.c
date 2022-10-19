#define _CRT_SECURE_NO_WARNINGS
#define NUM 10
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	int num;
	struct node* next;
} NODE;

typedef NODE* LINK;

LINK createNode(int data)
{
	LINK newNode = (LINK)malloc(sizeof(NODE));
	newNode->next = NULL;
	newNode->num = data;

	return newNode;
}


void printNode(LINK head)
{
	LINK nextNode = head;
	while (nextNode)
	{
		printf("%4d", nextNode->num);
		nextNode = nextNode->next;
	}
	puts("");
}

LINK appendNode(LINK head, LINK cur)
{
	LINK newNode = head;
	if (!head)
	{
		head = cur;
		return head;
	}
	while (newNode->next)
		newNode = newNode->next;
	newNode->next = cur;
	return head;
}

LINK makeAND(LINK head1, LINK head2)
{
	LINK head = NULL, cur;
	while (head1 && head2)
	{
		if (head1->num == head2->num)
		{
			cur = createNode(head1->num);
			head = appendNode(head, cur);
			head1 = head1->next;
			head2 = head2->next;
		}
		else if (head1->num < head2->num)
		{
			head1 = head1->next;
		}
		else
			head2 = head2->next;
	}
	return head;
}

int main()
{
	LINK head1 = NULL,head2 = NULL, head3, cur;
	FILE* f1 = fopen("in3.txt", "r"), *f2 = fopen("in4.txt", "r");
	if (!f1 | !f2)
	{
		puts("cannot open file!!");
		exit(-1);
	}

	int num, idx;
	
	while (!feof(f1))
	{
		fscanf(f1, "%d", &num);
		cur = createNode(num);
		head1 = appendNode(head1, cur);
	}
	printf("[in1.txt]\n");
	printNode(head1);

	while (!feof(f2))
	{
		fscanf(f2, "%d", &num);
		cur = createNode(num);
		head2 = appendNode(head2, cur);
	}
	printf("[in2.txt]\n");
	printNode(head2);

	head3 = makeAND(head1, head2);
	printf("[in1 AND in2]\n");
	if (head3)
		printNode(head3);
	else
		printf("공통된 원소가 없음.\n");

	fclose(f1);
	fclose(f2);

	return 0;
}
