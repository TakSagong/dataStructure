#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _polyNode {
	int coef;
	int expon;
	struct _polyPointer* link;
} polyNode ;

polyNode* createNode(int coef, int expon)
{
	polyNode* newNode = (polyNode*)malloc(sizeof(polyNode));
	newNode->coef = coef;
	newNode->expon = expon;
	newNode->link = NULL;
	return newNode;
}

polyNode* appendNode(polyNode* head, polyNode* cur)
{
	if (head == NULL)
		head = cur;
	else
	{
		polyNode* Node = head;
		while (Node->link)
			Node = Node->link;
		Node->link = cur;
	}
	return head;
}

int compare(int a, int b)
{
	if (a == b)
		return 0;
	else if (a > b)
		return 1;
	else
		return -1;
}

void attach(int coefficient, int exponent, polyNode** ptr)
{
	polyNode* temp;
	temp = (polyNode*)malloc(sizeof(polyNode));
	temp->coef = coefficient;
	temp->expon = exponent;
	(*ptr)->link = temp;
	*ptr = temp;
}
polyNode* padd(polyNode* a, polyNode* b)
{
	polyNode *c, *rear, *temp;
	int sum;
	rear = (polyNode*)malloc(sizeof(polyNode));
	c = rear;
	while (a && b)
		switch(compare(a->expon, b->expon))
		{
			case -1:
				attach(b->coef, b->expon, &rear);
				b = b->link;
				break;
			case 0:
				sum = a->coef + b->coef;
				if (sum) attach(sum, a->expon, &rear);
				a = a->link; b = b->link; break;
			case 1:
				attach(a->coef, a->expon, &rear);
				a = a->link;
				break;
		}
	for (; a; a = a->link) attach(a->coef, a->expon, &rear);
	for (; b; b = b->link) attach(b->coef, b->expon, &rear);
	rear->link = NULL;
	temp = c; c = c->link; free(temp);
	return c;
}



//void cerase(polyPointer ptr)
//{
//	polyPointer temp;
//	if (*ptr)
//	{
//		temp = (*ptr)->link;
//		(*ptr)->link = avail;
//		avail = temp;
//		*ptr = NULL;
//	}
//}

void printNode(polyNode* head)
{
	polyNode* Node = head;
	if (head == NULL)
		printf("empty list!!\n");
	else
	{
		while (Node)
		{
			printf("<%2d,%2d> ", Node->coef, Node->expon);
			Node = Node->link;
		}
		puts("");
	}
}

void erase(polyNode** ptr)
{
	polyNode* temp;
	while (*ptr)
	{
		temp = *ptr;
		*ptr = (*ptr)->link;
		free(temp);
	}
}

int main()
{
	int coef, expon;
	polyNode* cur;
	FILE* f1 = fopen("padd1.txt", "r"), * f2 = fopen("padd2.txt", "r");
	if (!f1 | !f2)
	{
		printf("cannot open file!!\n");
		exit(1);
	}
	polyNode* head1 = NULL, *head2 = NULL, *head3 = NULL;

	while (!feof(f1))
	{
		fscanf(f1, "%d %d", &coef, &expon);
		cur = createNode(coef, expon);
		head1 = appendNode(head1, cur);
	}
	printf("%10s", "poly A:");
	printNode(head1);

	while (!feof(f2))
	{
		fscanf(f2, "%d %d", &coef, &expon);
		cur = createNode(coef, expon);
		head2 = appendNode(head2, cur);
	}
	printf("%10s", "poly B:");
	printNode(head2);

	head3 = padd(head1, head2);
	printf("%10s", "poly A+B:");
	printNode(head3);

	erase(&head1);
	erase(&head2);
	erase(&head3);
	printf("\nafter erasing...\n");
	printNode(head1);
	printNode(head2);
	printNode(head3);

	fclose(f1);
	fclose(f2);
	return 0;
}