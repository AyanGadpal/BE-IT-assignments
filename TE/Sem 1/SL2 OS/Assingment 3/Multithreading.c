/*====================================================
Auther : Ayan N Gadpal K11 33308
Code : Matrix Multiplication using multithreading
Date : Jun 19 2019
Copyright : GNU public Library
=====================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int step = 0;

struct matrix
{
    int A[3][3], B[3][3], c[3][3];
};

// one third Multiply the Matrix
void *multi(void *p)
{
    int i, j, k, count = step++; //Part of multiplication
    struct matrix *m = (struct matrix *)p;
    printf("\nThread Process Started NO. %d", count);
    for (i = count; i < count + 1; i++)
        for (j = 0; j < 3; j++)
            for (k = 0; k < 3; k++)
                m->c[i][j] += m->A[i][k] * m->B[k][j];
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
    pthread_t thread_id[3];
    int i, j;
    struct matrix M, *p;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            M.c[i][j] = 0;

    printf("Input first Matrix: ");
    inputMatrix((int *)M.A);
    printf("Input Second Matrix: ");
    inputMatrix((int *)M.B);
    p = &M;
    for (i = 0; i < 3; i++)
        pthread_create(&thread_id[i], NULL, multi, (void *)p);

    printf("\nMain\n");
    printf("\n===================\n");
    printf("\nA\n");
    displayMatrix((int *)M.A);
    printf("\nB\n");
    displayMatrix((int *)M.B);
    printf("\nWaiting for threads");
    for (i = 0; i < 3; i++)
        pthread_join(thread_id[i], NULL);

    printf("\n===================\n");
    displayMatrix((int *)M.c);
    return 0;
}
