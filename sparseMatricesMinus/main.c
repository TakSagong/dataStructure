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

void minus(term a[], term b[], term c[])
{
    int sa = 1, sb = 1;
    c[0].row = a[0].row;
    c[0].col = a[0].col;
    int i = 1;
    while (sa <= a[0].value && sb <= b[0].value)
    {
        if (a[sa].row == b[sb].row && a[sa].col == b[sb].col)
        {
            c[i].row = b[sb].row;
            c[i].col = b[sb].col;
            c[i].value = a[sa].value-b[sb].value;
            i++;
            sb++; sa++;
        }
        else if (a[sa].row == b[sb].row && a[sa].col > b[sb].col)
        {
            c[i].row = b[sb].row;
            c[i].col = b[sb].col;
            c[i].value = -b[sb].value;
            i++;
            sb++;
        }
        else if (a[sa].row == b[sb].row && a[sa].col < b[sb].col)
        {
            c[i].row = a[sa].row;
            c[i].col = a[sa].col;
            c[i].value = a[sa].value;
            i++;
            sa++;            
        }
        else if (a[sa].row < b[sb].row)
        {
            c[i].row = a[sa].row;
            c[i].col = a[sa].col;
            c[i].value = a[sa].value;
            i++;
            sa++;   
        }
        else
        {
            c[i].row = b[sb].row;
            c[i].col = b[sb].col;
            c[i].value = -b[sb].value;
            i++;
            sb++;
        }
    }
    for (; sa <= a[0].value; sa++)
    {
        c[i].row = a[sa].row;
        c[i].col = a[sa].col;
        c[i].value = a[sa].value;
        i++;
        sa++;
    }
    for (; sb <= b[0].value; sb++)
    {
        c[i].row = b[sb].row;
        c[i].col = b[sb].col;
        c[i].value = -b[sb].value;
        i++;
        sb++;
    }
    c[0].value = i-1;
}

void printMatrix(term *a)
{
    for (int i = 0; i <= a[0].value; i++)
        printf("(%4d%4d%4d)\n", a[i].row, a[i].col, a[i].value);
    puts("");
}

int main(void)
{
    term a[MAX];
    term b[MAX];
    term c[MAX];

    printf("[Matrix A]\n");
    execute("a2.txt", a);
    printMatrix(a);
    printf("[Matrix B]\n");
    execute("b2.txt", b);
    printMatrix(b);

    minus(a,b,c);
    printMatrix(c);
    return 0;
}