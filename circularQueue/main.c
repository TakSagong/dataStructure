#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int data;
} element;

element *queue;
int size, front = 0, rear = 0;

void print()
{
    if (front < rear)
    {
        printf("Circular queue:");
        for (int i = front+1; i <= rear; i++)
            printf("%2d", queue[i].data);
    }
    else if (rear < front)
    {
        printf("Circular queue:");
        for (int i = front+1; i < size; i++)
            printf("%2d", queue[i].data);
        for (int i = 0; i <= rear; i++)
            printf("%2d", queue[i].data);
    }
    puts("");
}

void push(element data)
{
    rear = (rear+1) % size;
    queue[rear] = data;
}

void pop()
{
    front = (front + 1) % size;
    if (front == rear)
        printf("Circular queue is empty");
}

void execute(char * name)
{
    front = 0;
    rear = 0;
    FILE *f = fopen(name, "r");
    char op;
    int num;
    element newEle;

    if (!f)
    {
        fprintf(stderr, "cannot open file!!");
        exit(-1);
    }
    fscanf(f, "%d", &size);
    queue = (element *) malloc (sizeof(element) * size);
    printf("Queue size: %d\n", size);
    while (!feof(f))
    {
        fscanf(f, "%c", &op);
        if (op == 'a')
        {
            if (front == (rear + 1) % size)
            {
                printf("queue full: cannot add\n");
                break;
            }
            fscanf(f, "%d", &num);
            newEle.data = num;
            push(newEle);
            print();
        }
        else if (op == 'd')
        {
            if (front == rear)
            {
                printf("queue full: cannot delete\n");
                break;
            }
            pop();
            print();
        }
    }
    puts("");
    fclose(f);
    free(queue);
}

int main()
{
    execute("in1.txt");
    execute("in2.txt");
    execute("in3.txt");

    return 0;
}