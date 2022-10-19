#include <stdio.h>
#include <stdlib.h>
#define MAX_TERM_SIZE 100
typedef struct {
    int coef;
    int expon;
} polynomial;

int avail;
polynomial terms[MAX_TERM_SIZE];

void print(char c, int s, int f)
{
    printf("%c(x):", c);
    printf("%dx^%d  ", terms[s].coef, terms[s].expon);
    for (int i = s+1; i <= f; i++)
        printf("+ %dx^%d ", terms[i].coef, terms[i].expon);
    puts("");
}
int compare(int sa, int sb)
{
    if (terms[sa].expon == terms[sb].expon)
        return 0;
    else if (terms[sa].expon < terms[sb].expon)
        return 1;
    else
        return -1;
}

void attach(int coef, int expon)
{
    if (avail >= MAX_TERM_SIZE)
    {
        printf("Too many terms in polynomial\n");
        exit(1);
    }
    terms[avail].coef = coef;
    terms[avail++].expon = expon;
}

void padd(int sa, int fa, int sb, int fb, int *sc, int *fc)
{
    int coefficient;
    *sc = avail;
    while (sa <= fa && sb <= fb)
    {
        switch(compare(sa, sb))
        {
            case -1:
                attach(terms[sb].coef, terms[sb].expon);
                sb++; break;
            case 1:
                attach(terms[sa].coef, terms[sa].expon);
                sa++; break;
            case 0:
                coefficient = terms[sb].coef + terms[sa].coef;
                if (coefficient)
                    attach(coefficient, terms[sa].expon);
                sa++; sb++; break;
        }
    }
    for (; sa <= fa; sa++)
        attach(terms[sa].coef, terms[sa].expon);
    for (; sb <= fb; sb++)
        attach(terms[sb].coef, terms[sb].expon);
    *fc = avail - 1;
}

void pminus(int sa, int fa, int sb, int fb, int *sc, int *fc)
{
    int coefficient;
    *sc = avail;
    while (sa <= fa && sb <= fb)
    {
        switch(compare(sa, sb))
        {
            case -1:
                attach(-terms[sb].coef, terms[sb].expon);
                sb++; break;
            case 1:
                attach(terms[sa].coef, terms[sa].expon);
                sa++; break;
            case 0:
                coefficient = terms[sa].coef - terms[sb].coef;
                if (coefficient)
                    attach(coefficient, terms[sa].expon);
                sa++; sb++; break;
        }
    }
    for (; sa <= fa; sa++)
        attach(terms[sa].coef, terms[sa].expon);
    for (; sb <= fb; sb++)
        attach(-terms[sb].coef, terms[sb].expon);
    *fc = avail - 1;
}

void execute(char * name1, char * name2)
{
    int coef, expon;
    int sa, fa, sb, fb, sc, fc;

    FILE *f1 = fopen(name1, "r"), *f2 = fopen(name2, "r");
    if (!f1 | !f2)
    {
        printf("cannot open file!!");
        exit(1);
    }
    sa = avail;
    while (!feof(f1))
    {
        fscanf(f1, "%d %d", &coef, &expon);
        terms[avail].coef = coef;
        terms[avail++].expon = expon;
    }
    fa = avail - 1;
    print('A', sa, fa);
    sb = avail;
    while (!feof(f2))
    {
        fscanf(f2, "%d %d", &coef, &expon);
        terms[avail].coef = coef;
        terms[avail++].expon = expon;
    }
    fb = avail - 1;
    print('B', sb, fb);
    padd(sa, fa, sb, fb, &sc, &fc);
    print('C', sc, fc);

    pminus(sa, fa, sb, fb, &sc, &fc);
    print('C', sc, fc);
    fclose(f1);
    fclose(f2);
}

int main(void)
{
    execute("a.txt", "b.txt");
    return 0;
}