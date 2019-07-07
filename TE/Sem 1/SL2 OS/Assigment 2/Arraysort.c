/*====================================================
Auther : Ayan N Gadpal K11 33308
Code : Sort two arrays using parent and child process
Date : Jun 5 2019
Copyright : GNU public Library
=====================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

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
    printf("================================\n");
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

// MAIN
int main()
{
    // Preproccessing
    int i, *A, *B, n, m, status, zombie = 0;
    printf("Sorting Program Started !\n");
    line();
    // ARRAY 1 INPUT
    printf("\nEnter the size of Array 1 : ");
    scanf("%d", &n);
    // Allocating Memory for First Array
    A = (int *)malloc(n * sizeof(int));

    printf("Enter Data into Array 1");
    for (i = 0; i < n; i++)
    {
        printf("\n%d) ", i + 1);
        scanf("%d", (A + i));
    }
    line();

    // ARRAY 2 INPUT
    printf("\nEnter the size of Array 2 : ");
    scanf("%d", &m);

    // Allocating Memory for Second Array
    B = (int *)malloc(m * sizeof(int));

    printf("Enter Data into Array 2");
    for (i = 0; i < m; i++)
    {
        printf("\n%d) ", i + 1);
        scanf("%d", (B + i));
    }

    // MultiProccessing Starts Here
    line();
    printf("[ CREATING CHILD PROCESS ]\n");
    status = fork(); // Creating child process
    if (status != 0) 
    {
        // THIS IS PARENT code
        line();
        printf("\n[ PARENT ] : ID %d\n", getpid());
        printf("\n[ PARENT ] : My Array is \n");
        displayArray(A, n); // Normal Array
        printf("\n[ PARENT ] : Sorting");
        bubbleSort(A, n);   // Performing Sorting
        printf("\n[ PARENT ] : Sorted Array");
        displayArray(A, n); // Sorted Array
        wait(NULL); // Waiting for child
        printf("[ PARENT ] : BYEE\n");
        exit(0);
        line();
    }
    else if(status <= -1) // Error Handling 
        printf("\n[ SYSTEM ERROR ] : Child not created ! \n");
    else
    {
        // THIS IS Child code
        line();
        printf("\n[ Child ] : ID %d\n", getpid());
        printf("\n[ Child ] : My Array is ");
        displayArray(B, m); // Normal Array
        printf("\n[ Child ] : Sorting ");
        bubbleSort(B, m);   // Performing Sorting
        printf("\n[ Child ] : Sorted Array ");
        displayArray(B, m); // Sorted Array
        printf("\n[ Child ] : Byee\n");
        exit(1); // Exitting
    }

    return 0;
}