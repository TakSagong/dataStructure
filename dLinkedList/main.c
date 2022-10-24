#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int data;
    struct _node * llink;
    struct _node * rlink;
} NODE ;

NODE * dcreate(int data)
{
    NODE * new = (NODE*)malloc(sizeof(NODE));
    new->data = data;
    new->llink = NULL;
    new->rlink = NULL;

    return new;
}

NODE * dappend(NODE * head, NODE* newnode)
{
    if (head == NULL)
    {
        head = newnode;
        return head;
    }
    else
    {
        NODE * cur = head;
        while (cur->rlink)
            cur = cur->rlink;
        newnode->rlink = cur->rlink;
        cur->rlink = newnode;
        newnode->llink = cur;

        return head;
    }
}
NODE * dinsert(NODE * node, NODE* newnode)
{
    newnode->rlink = node->rlink;
    newnode->llink = node;
    node->rlink->llink = newnode;
    node->rlink = newnode;
    return node;
}

void dprint(NODE* head)
{
    NODE* cur = head;
    while (cur->rlink)
    {
        printf("%3d", cur->data);
        cur = cur->rlink;
    }
    while (cur)
    {
        printf("%3d", cur->data);
        cur = cur->llink;
    }
}

NODE * ddelete(NODE* node, NODE* deleted)
{
    if (deleted == node)
    {
        printf("deletion of header node not permitted\n");
        return node;
    }
    else
    {
        deleted->rlink->llink = deleted->llink;
        deleted->llink->rlink = deleted->rlink;
        free(deleted);
        return node;
    }
}

int main()
{
    int num;
    NODE *head = NULL, *cur;
    FILE *f = fopen("in1.txt", "r");
    if (!f)
    {
        printf("cannot open file!!!\n");
        exit(1);
    }
    while (!feof(f))
    {
        fscanf(f, "%d", &num);
        cur = dcreate(num);
        head = dappend(head, cur);
    }
    dprint(head);

    fclose(f);

    return 0;
}