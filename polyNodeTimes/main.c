#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _polyNode {
	int coef;
	int expon;
	struct _polyPointer* link;
} polyNode;

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

polyNode* deleteNode(polyNode* head, int coef, int expon)
{
	polyNode* prev = head;
	polyNode* cur = head->link;
	if (prev->expon == expon && prev->coef == coef)
	{
		head = cur;
		free(prev);
	}
	else
	{
		while (cur)
		{
			if (cur->expon == expon && cur->coef == coef)
			{
				prev->link = cur->link;
				free(cur);
				break;
			}
			prev = cur;
			cur = cur->link;
		}
	}
	
	return head;
}

void attach(int coefficient, int exponent, polyNode** ptr, polyNode** ptr2)
{
	polyNode* temp;
	temp = (polyNode*)malloc(sizeof(polyNode));
	temp->coef = coefficient;
	temp->expon = exponent;
	(*ptr2) = (*ptr);
	(*ptr)->link = temp;
	*ptr = temp;
}

polyNode* pmut(polyNode* a, polyNode* b)
{
	polyNode* c, * rear, * temp;
	int mcoef, mexpon, sum;
	rear = (polyNode*)malloc(sizeof(polyNode));
	c = rear;
	polyNode* cur = b, *prev = NULL;

	while (a)
	{
		cur = b;
		while (cur)
		{
			mcoef = a->coef * cur->coef;
			mexpon = a->expon + cur->expon;
			if (rear->expon == mexpon)
			{
				if (rear->coef + mcoef == 0)
				{
					free(rear);
					rear = prev;
				}
				else
				{
					rear->coef = rear->coef + mcoef;
				}
			}
			else
				attach(mcoef, mexpon, &rear, &prev);

			cur = cur->link;
		}
		a = a->link;
	}
	rear->link = NULL;
	temp = c; c = c->link; free(temp);
	return c;
}

void printNode(polyNode* head)
{
	polyNode* Node = head;
	if (head == NULL)
		printf("empty list!!\n");
	else
	{
		while (Node)
		{
			printf("(%2d,%2d) ", Node->coef, Node->expon);
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
	FILE* f1 = fopen("poly1.txt", "r"), * f2 = fopen("poly2.txt", "r");
	if (!f1 | !f2)
	{
		printf("cannot open file!!\n");
		exit(1);
	}
	polyNode* head1 = NULL, * head2 = NULL, * head3 = NULL;

	while (!feof(f1))
	{
		fscanf(f1, "%d %d", &coef, &expon);
		cur = createNode(coef, expon);
		head1 = appendNode(head1, cur);
	}
	printf("[poly1]\n");
	printNode(head1);

	while (!feof(f2))
	{
		fscanf(f2, "%d %d", &coef, &expon);
		cur = createNode(coef, expon);
		head2 = appendNode(head2, cur);
	}
	printf("[poly2]\n");
	printNode(head2);

	head3 = pmut(head1, head2);
	printf("[poly1 x poly2]\n");
	polyNode* prev = head3;
	polyNode* next = prev->link;
	int sum;

	printNode(head3);

	erase(&head1);
	erase(&head2);
	erase(&head3);


	fclose(f1);
	fclose(f2);
	return 0;
}