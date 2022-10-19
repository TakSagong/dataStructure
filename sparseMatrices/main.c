#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct {
    int row;
    int col;
    int value;
} term ;


void transpose(term a[], term b[])
{
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = a[0].value;
    int i, j, rowTerms[MAX], startPos[MAX];
    if (a[0].value > 0)
    {
        for (i = 0; i < a[0].col; i++)
            rowTerms[i] = 0;
        for (i = 1; i <= a[0].value; i++)
            rowTerms[a[i].col]++;
        startPos[0] = 1;
        for (i = 1; i < a[0].col; i++)
            startPos[i] = startPos[i-1] + rowTerms[i-1];
        for (i = 1; i <= a[0].value; i++)
        {
            j = startPos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }
}

void execute(char *name, term* a)
{
    char line[MAX];
    char *ptoken;
    char *delimeter = " ";
    int col = 0, row = 0, cnt = 0;
    int i = 1, temp;
    FILE *f = fopen(name, "r");
    if (!f)
    {
        printf("cannot open file!!\n");
        exit(1);
    }
    fgets(line, MAX, f);
    while (!feof(f))
    {
        ptoken = strtok(line, delimeter);
        col = 0;
        while (ptoken != NULL)
        {
            temp = atoi(ptoken);
            if (temp != 0)
            {
                a[i].row = row;
                a[i].col = col;
                a[i].value = temp;
                i++; cnt++;
            }
            col++;
            ptoken = strtok(NULL, delimeter);
        }
        fgets(line, MAX, f);
        row++;
    }
    a[0].value = cnt;
    a[0].row = row;
    a[0].col = col;
}

void printMatrix(term *a)
{
    for (int i = 0; i <= a[0].value; i++)
        printf("(%3d%3d%3d)\n", a[i].row, a[i].col, a[i].value);
    puts("");
}

int main(void)
{
    term a[MAX];
    term b[MAX];
    term c[MAX];
    term d[MAX];

    printf("[Matrix A]\n");
    execute("a1.txt", a);
    printMatrix(a);
    printf("[Matrix B]\n");
    execute("b1.txt", b);
    printMatrix(b);

    printf("[Transpose A]\n");
    transpose(a, c);
    printMatrix(c);

    printf("[Transpose B]\n");
    transpose(b, d);
    printMatrix(d);
    
    return 0;
}