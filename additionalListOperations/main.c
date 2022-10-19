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

LINK insertNode(LINK head, LINK cur)
{
	LINK nextNode = head->next, prev = head;
	if (cur->num <= head->num)
	{
		cur->next = head;
		head = cur;
		return head;
	}
	else
	{
		while (nextNode)
		{
			if (prev->num <= cur->num && cur->num <= nextNode->num)
			{
				cur->next = nextNode;
				prev->next = cur;
				break;
			}
			else if (nextNode->next == NULL)
			{
				nextNode->next = cur;
				break;
			}
			prev = nextNode;
			nextNode = nextNode->next;
		}
	}
	return head;
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

LINK deleteNode(LINK head, int key)
{
	LINK prev = NULL, cur = head;
	if (head->num == key)
	{
		head = head->next;
		free(cur);
		return head;
	}
	prev = head;
	cur = head->next;
	while (cur) {
		if (cur->num == key) {
			prev->next = cur->next;
			free(cur);
			break;
		}
		prev = cur;
		cur = cur->next;
	}
	if (cur == NULL)
		printf("%d 없음.", key);
	return head;
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
	cur->next = NULL;

	return head;
}

void execute(char *name1, char *name2)
{
	FILE* f1 = fopen(name1, "r"), * f2 = fopen(name2, "r");
	LINK head = NULL, cur;
	int num;

	if (!f1 | !f2)
	{
		puts("cannot open file!!");
		exit(-1);
	}
	while (!feof(f1))
	{
		fscanf(f1, "%d", &num);
		cur = createNode(num);
		head = appendNode(head, cur);
	}
	printf("[original]\n");
	printNode(head);

	while (!feof(f2))
	{
		fscanf(f2, "%d", &num);
		if (num % 2 == 0)
		{
			printf("Insert %d==>", num);
			cur = createNode(num);
			head = insertNode(head, cur);
			printNode(head);
		}
		else
		{
			printf("Delete %d==>", num);
			head = deleteNode(head, num);
			printNode(head);
		}
	}
	puts("");
	fclose(f1);
	fclose(f2);
}

int main()
{
	execute("in3.txt", "in4.txt");
	execute("in3.txt", "in5.txt");
	return 0;
}
