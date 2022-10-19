#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE_STACK 100

typedef struct {
    short int vert;
    short int horiz;
} offsets ;

typedef struct {
    short int row;
    short int col;
    short int dir;
} element ;

offsets move[4] = {{-1, 0}, {0,1}, {1, 0}, {0, -1}};
element stack[MAX_SIZE_STACK];
int **maze, **mark;
int row ,col;
int start_row, start_col;
int exit_row, exit_col;
int top = -1;

void push(element e)
{
    stack[++top] = e;
}

element pop()
{
    return stack[top--];
}

void path()
{
    mark[start_row+1][start_col+1] = 1; top = 0;
    stack[0].row = start_row+1; stack[0].col = start_col+1; stack[0].dir = 0;
    int found = 0;
    element position;
    int row, col, dir;
    int nextRow, nextCol;

    while (top > -1 && !found)
    {
        if (dir == 4)
            mark[row][col] = 2;
        position = pop();
        row = position.row;
        col = position.col;
        dir = position.dir;
        while (dir < 4 && !found)
        {
            nextRow = row + move[dir].vert;
            nextCol = col + move[dir].horiz;
            if (nextRow == exit_row+1 && nextCol == exit_col+1)
                found = 1;
            else if (!mark[nextRow][nextCol] && !maze[nextRow][nextCol])
            {
                mark[nextRow][nextCol] = 1;
                position.row = row;
                position.col = col;
                position.dir = ++dir;
                push(position);
                row = nextRow; col = nextCol; dir = 0;
            }
            else ++dir;
        }
    }
    if (found)
        printf("The path is\n");
    else 
        printf("No path!!\n");
}

void printMaze()
{
    for (int i = 1; i < row+1; i++)
    {
        for (int j = 1; j < col+1; j++)
            printf("%3d", maze[i][j]);
        puts("");
    }
    puts("");
}

void printResult()
{
    for (int i = 1; i < row+1; i++)
    {
        for (int j = 1; j < col+1; j++)
        {
            if (i == start_row+1 && j == start_col+1)
                printf("%3c", 'S');
            else if (i == exit_row+1 && j == exit_col+1)
                printf("%3c", 'F');
            else if (mark[i][j] == 1)
                printf("%3c", 'X');
            else
                printf("%3d", maze[i][j]);
        }
        puts("");
    }
    puts("");
}

void execute(char * name)
{
    char line[100];
    char *ptoken;
    char *delimiter = " ";

    FILE *f1 = fopen(name , "r");
    if (!f1)
    {
        fprintf(stderr, "cannot open file!\n");
        exit(1);
    }
    fgets(line, 100, f1);
    sscanf(line, "%d %d", &row, &col);

    maze = (int **) malloc(sizeof(int *) * (row+2));
    for (int i = 0; i < row+2; i++)
        maze[i] = (int *)malloc(sizeof(int) * (col+2));

    mark = (int **) malloc(sizeof(int *) * (row+2));
    for (int i = 0; i < row+2; i++)
        mark[i] = (int *)malloc(sizeof(int) * (col+2));

    for (int i = 0; i < row+2; i++)
        for (int j = 0; j < col+2; j++)
            mark[i][j] = 0;
    int j = 1;
    for (int i = 1; i < row+1; i++)
    {
        fgets(line, 100, f1);
        ptoken = strtok(line, delimiter);
        j = 1;
        while (ptoken != NULL)
        {
            maze[i][j] = atoi(ptoken);
            if (j == col)
                j = 1;
            else
                j++;
            ptoken = strtok(NULL, delimiter);
        }
    }
    for (int i = 0; i < row+2; i++)
    {
        maze[i][0] = 1;
        maze[i][col+1] = 1;
    }
    for (int i = 0; i < col+2; i++)
    {
        maze[0][i] = 1;
        maze[row+1][i] = 1;
    }
    fgets(line, 100, f1);
    sscanf(line, "%d %d %d %d", &start_row, &start_col, &exit_row, &exit_col);
    printf("MAZE\n");
    printMaze();
    path();
    printResult();

    fclose(f1);
    free(mark);
    free(maze);
}


int main()
{
    execute("maze1.txt");
    execute("maze2.txt");
    execute("maze3.txt");
    execute("maze4.txt");

    return 0;
}

