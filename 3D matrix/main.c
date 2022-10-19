#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j, k;
    printf("A[I][J][K]...\n");
    printf("Input I:");
    scanf("%d", &i);
    printf("Input J:");
    scanf("%d", &j);
    printf("Input K:");
    scanf("%d", &k);

    int ***arr = (int ***) malloc (sizeof(int**) * i);
    for (int a = 0; a < i; a++)
    {
        arr[a] = (int **) malloc (sizeof(int*) * j);
        for (int b = 0; b < j; b++)
        {
            arr[a][b] = (int *) malloc (sizeof(int) * k);
            for (int c = 0; c < k; c++)
            {
                arr[a][b][c] = a + b + c;
            }
        }
    }

    for (int a = 0; a < i; a++)
    {
        for (int b = 0; b < j; b++)
        {
            for (int c = 0; c < k; c++)
            {
                printf("A[%d][%d][%d]=%2d", a, b, c, arr[a][b][c]);
            }
            puts("");
            free(arr[a][b]);
        }
        puts("");
        free(arr[a]);
    }
    free(arr);
        
    return 0;
}