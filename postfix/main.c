// 조건: Parentheses mismatch일 경우, 출력만 하면 됨. postfix의 결과는 무시함.
// 시간 생기면 다시 고칠 것.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100 /* maximum stack size */
#define MAX_EXPR_SIZE 100 /* max size of expression */
typedef enum { lparen, rparen, plus, minus, times, divide,
mod, eos, operand } precedence;
int evalStack[MAX_STACK_SIZE]; /* global stack */
precedence postfixStack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE]; /* input string */
char result[MAX_EXPR_SIZE];
int et = -1;
int pt = -1;
precedence stack[MAX_STACK_SIZE];
int idx = 0;
static int isp[]= { 0,19,12,12,13,13,13,0};
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

precedence postfixPop()
{
    return postfixStack[pt--];
}

void postfixPush(precedence data)
{
    postfixStack[++pt] = data;
}

int evalPop()
{
    return evalStack[et--];
}

void evalPush(int data)
{
    evalStack[++et] = data;
}

void printToken(precedence token)
{
    switch (token)
    {
    case plus:
        expr[idx++] = '+';
        break;
    case minus:
        expr[idx++] = '-';
        break;
    case times:
        expr[idx++] = '*';
        break;
    case divide:
        expr[idx++] = '/';
        break;
    case mod:
        expr[idx++] = '%';
        break;
    case lparen:
        expr[idx++] = '(';
        break;   
    case rparen:
        expr[idx++] = ')';
        break;       
    default:
        break;
    }
}

precedence get_token (char *symbol, int * n)
{
    *symbol = expr[(*n)++];
    switch (*symbol) {
        case '(' : return lparen;
        case ')' : return rparen;
        case '+' : return plus;
        case '-' : return minus;
        case '/' : return divide;
        case '*' : return times;
        case '%' : return mod;
        case '\0' : return eos;
        default : return operand; 
    }
}

int postfix(void)
{
    char symbol;
    precedence token;
    int n = 0;
    pt = 0; idx = 0;
    postfixStack[0] = eos;
    for (token = get_token(&symbol, &n); token != eos; token = get_token(&symbol, &n))
    {
        if (token == operand)
        {
            expr[idx++] = symbol;
        }
        else if (token == rparen)
        {
            while (postfixStack[pt] != lparen)
            {
                if (pt == 0) return 0;
                printToken(postfixPop());
            }
            postfixPop();
        }
        else
        {
            while (isp[postfixStack[pt]] >= icp[token])
            {
                printToken(postfixPop());
            }
            postfixPush(token);
        }
    }
    while ((token = postfixPop()) != eos)
    {
        if (token == lparen)
            return 0;
        printToken(token);
    }
    for (int i = idx; i < MAX_EXPR_SIZE; i++)
        expr[i] = '\0';
    return 1;
}

void eval(void)
{
    precedence token;
    char symbol;
    int op1, op2;
    int n = 0;
    et = 0;
    token = get_token(&symbol, &n);
    while (token != eos)
    {
        if (token == operand)
            evalPush(symbol-'0');
        else
        {
            op2 = evalPop();
            op1 = evalPop();

            switch (token)
            {
            case plus:
                evalPush(op1+op2);
                break;
            case minus:
                evalPush(op1-op2);
                break;
            case times:
                evalPush(op1*op2);
                break;
            case divide:
                evalPush(op1/op2);
                break;
            case mod:
                evalPush(op1%op2);
                break;
            default:
                break;
            }
        }
        token = get_token(&symbol, &n);
    }
    printf("Result: %d\n", evalPop());
}

void execute(char * name)
{
    FILE *f = fopen(name , "r");

    if (!f)
    {
        printf("cannot open file!!");
        exit(1);
    }

    while (!feof(f))
    {
        fscanf(f, "%s", expr);
        printf("Infix: %s\n", expr);
        if (postfix())
        {
            printf("Postfix: %s\n", expr);
            eval();
        }
        else
        {
            printf("Doesn't matter\n");
            printf("...Parentheses mismatch\n");
        }
        puts("");
    }

    fclose(f);
}

int main()
{
    execute("infix.txt");

    return 0;
}