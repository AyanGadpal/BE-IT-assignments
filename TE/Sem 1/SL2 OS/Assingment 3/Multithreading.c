/*====================================================
Auther : Ayan N Gadpal K11 33308
Code : Matrix Multiplication using multithreading
Date : Jun 16 2019
Copyright : GNU public Library
=====================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int A[3][3], B[3][3], c[3][3] = {0};
int step = 0;

void *multi()
{
    int i, j, k, count = step++;
    printf("\nThread Process Stated NO. %d", count);
    for (i = count; i < count + 1; i++)
        for (j = 0; j < 3; j++)
            for (k = 0; k < 3; k++)
                c[i][j] += A[i][k] * B[k][j];
}

void inputMatrix(int *matrix)
{
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
        {
            printf("\n%d %d : ", i, j);
            scanf("%d", matrix + i * 3 + j);
        }
}

void displayMatrix(int *matrix)
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf(" %d ", *(matrix + i * 3 + j));
        }
        printf("\n");
    }
}

int main()
{
    pthread_t thread_id[4];
    int i;
    printf("Input first Matrix: ");
    inputMatrix((int *)A);
    printf("Input Second Matrix: ");
    inputMatrix((int *)B);

    for (i = 0; i < 4; i++)
        pthread_create(&thread_id[i], NULL, multi, NULL);

    printf("\nMain\n");
    printf("\n===================\n");
    printf("\nA\n");
    displayMatrix((int *)A);
    printf("\nB\n");
    displayMatrix((int *)B);
    printf("\nWaiting for threads");
    for (i = 0; i < 4; i++)
        pthread_join(thread_id[i], NULL);

    printf("\n===================\n");
    displayMatrix((int *)c);
    return 0;
}
