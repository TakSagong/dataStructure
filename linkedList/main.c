#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int data;
    struct _node * next;
} Node ;

Node * createNode(int data)
{
    Node * newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = (Node*)NULL;

    return newNode;
}

void appendBackNode(Node ** head, Node * newNode)
{
    if (*head == (Node*)NULL)
    {
        *head = newNode;
        return;
    }
    
    Node * cur = *head;
    while (cur->next)
        cur = cur->next;
    cur->next = newNode;
}

void appendFrontNode(Node ** head, Node * newNode)
{
    if (*head == (Node*)NULL)
    {
        *head = newNode;
        return;
    }
    
    newNode->next = *head;
    *head = newNode;
}

void deleteNode(Node **head, int num)
{
    if (*head == (Node*)NULL)
        printf("cannot delete node\n");
    else
    {
        Node * cur = *head;
        if (cur->data == num)
        {
            *head = cur->next;
            free(cur);
        }
        Node * prev = cur;
        cur = prev->next;
        while (cur)
        {
            if (cur->data == num)
            {
                prev->next = cur->next;
                free(cur);
                break;
            }
            prev = prev->next;
            cur = cur->next;
        }

    }
}

void printNode(Node **head)
{
    Node * cur = *head;
    while (cur)
    {
        printf("%3d", cur->data);
        cur = cur->next;
    }
    puts("");
}

int main()
{
    Node *head = NULL;
    Node * cur;

    for (int i = -9; i < 10; i++)
    {
        cur = createNode(i);
        if (i < 0)
            appendBackNode(&head, cur);
        else
            appendFrontNode(&head, cur);
    }
    deleteNode(&head, 1);
    deleteNode(&head, -1);
    deleteNode(&head, 9);

    printNode(&head);
    return 0;
}