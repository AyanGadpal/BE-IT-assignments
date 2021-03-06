/*====================================================
Auther : Ayan N Gadpal K11 33308
Code : Assignment 2 Part B Array Sort Main Process
Date : Jun 8 2019
Copyright : GNU public Library
=====================================================*/

// NOTE : COMPILE THE PROGRAM "subP.c" AS OUTPUT "b.out" BEFORE EXECUTING THIS CODE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
// Display Array
void displayArray(int *A, int n)
{
    int i;
    printf("\n");
    for (i = 0; i < n; i++)
        printf(" %d ", *(A + i));
    printf("\n");
}

// Swap Elements
void swap(int *a, int *b)
{
    int c = *b;
    *b = *a;
    *a = c;
}

// Print a line for output formatting
void line()
{
    printf("\n==============================================\n");
}

// Bubble Sort Algorithm is used for sorting
void bubbleSort(int *A, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
        {
            if (A[j] > A[j + 1])
                swap(A + j, A + j + 1);
        }
}

int main()
{
    int *array, n, i, status = -1;
    char *a[20], *rst;

    // TAKING THE ARRAY AS INPUT FROM USER
    line();
    printf("Enter the Size of array : ");
    scanf("%d", &n);
    line();
    array = malloc(n * sizeof(int));
    printf("Enter the elements of array\n");
    for (i = 0; i < n; i++)
    {
        printf("\n%d) ", i + 1);
        scanf("%d", array + i);
    }

    // SORTING ARRAY
    line();
    printf("Sorting Array.... \n");
    bubbleSort(array, n);
    line();
    printf("Sorting Completed !\nSorted Array : ");
    displayArray(array, n);
    line();


    // COVERTING to STRING
    for (i = 0; i < n; i++)
    {
        rst = malloc(sizeof(int));
        sprintf(rst, "%d", array[i]);
        a[i] = malloc(sizeof(int));
        a[i] = rst;
    }

    // CREATING NEW PROCESS
    printf("Forking...\n");
    status = fork();

    if (status != 0) // PARENT
    {
        line();
        printf("[ PARENT ] : Waiting for Child \n");
        wait(NULL);
        line();
        printf("[ PARENT ] : Child Arrived, Exiting\n");
        exit(0);
    }
    else // CHILD
    {
        line();
        printf("[ CHILD ] : Child Proccess running\n");

        // CREATING NEW PROCESS AND PASSING THE STRING AS AGRUMENT
        execvp("./b.out", a);
        printf("\n[ CHILD ] : Operation Completed");
        exit(0);
    }

    return (0);
}
