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

int main()
{
    int *array, n, i, status = -1;
    char *a[10], rst;
    printf("Enter the Size of array : ");
    scanf("%d", &n);
    array = malloc(n * sizeof(int));
    printf("Enter the elements of array\n");
    for (i = 0; i < n; i++)
    {
        printf("\n%d) ", i + 1);
        scanf("%d", array + i);
    }
    printf("Sorting Array.... \n");
    bubbleSort(array, n);
    printf("Sorting Completed !\nSorted Array : ");
    displayArray(array, n);
    printf("Forking...");

    // COVERTING to STRING
    for (i = 0; i < n; i++)
    {
        sprintf(&rst, "%d", array[i]);
        a[i] = malloc(sizeof(int));
        *a[i] = rst;
        printf("string %s\n", a[i]);
    }

    status = fork();

    if (status != 0) // PARENT
    {
        printf("watt pahaa \n");
        wait(NULL);
        exit(0);
    }
    else // CHILD
    {
        printf("Child aa gaya\n");
        execvp("./b.out", a);
    }

    return (0);
}