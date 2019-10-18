/*
Name        : Process control System calls
Auther      : Ayan Naresh Gadpal
Copyright   : GNU public Libraly
Description : Take two Array, One will be sorted by parent and other will be by child
Date        : Fri Oct 18 2019 , 1:37 PM
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> // For pid_t
#include <sys/wait.h> // For wait()

// Input START
int* input(int *array,int *size)
{
       int i;
       
       // Accept the size of array
       printf("Enter the size Array\nSize :");
       scanf("%d",size);
       
       // Allocate memory
       array = malloc(sizeof(int)*(*size));
       
       // Accept the data
       printf("Enter the Data in The Array");
       for(i=0;i<*size;i++)
       {
          printf("\n%d) ",i+1); 
          scanf("%d",&array[i]);
       }
       
       // Return Memory base pointer
       return array;
}
// Input END

// display START
void display(int *array,int size)
{
       int i;
       // Display Each Element from the array
       for(i=0;i<size;i++)
           printf("%d) %d \n",i+1,array[i]);
}
// display END

// Swap Elements
void swap(int *a, int *b)
{
    int c = *b;
    *b = *a;
    *a = c;
}


void bubbleSort(int *array,int size)
{
        int i,j;
        for(i=0;i<size-1;i++)
           for(j=0;j<size-i-1;j++)
               if(array[j]>array[j+1])
                   swap(array+j,array+j+1);
}
// main START
void main(){
       
       // arrayA for parent, arrayB for Child
       int *arrayA,*arrayB;
       int sizeA,sizeB;
       
       // Take input for both Array
       printf("\nEnter the 1st Array\n");
       arrayA = input(arrayA,&sizeA);
       
       printf("\nEnter the 2nd Array\n");
       arrayB = input(arrayB,&sizeB);
       
       // Display the UNSORTED array
       printf("\nARRAY 1 :\n");
       display(arrayA,sizeA);
       
       printf("\nARRAY 2 :\n");
       display(arrayB,sizeB);
       
       pid_t id = fork();
       
       // Validation
       if(id < 0)
                printf("\nFORK FAILED !\n ");
       if(id != 0) // PARENT
       {
                printf("\n [ PARENT ] : Parent Enter\n");
                
                // SORT THE FIRST ARRAY
                printf("\n [ PARENT ] : Parent Sorting\n");
                bubbleSort(arrayA,sizeA);
                
                // WAIT FOR CHILD TO COMPLETE ITS TASK
                printf("\n [ PARENT ] : Parent Waiting for child\n");
                wait(NULL);
                
                // DISPLAY BOTH ARRAY AND EXIT
                printf("\n [ PARENT ] : ARRAY A\n");
                display(arrayA,sizeA);
                
                printf("\n [ PARENT ] : ARRAY B\n");
                display(arrayB,sizeB);
                exit(1);
       }
       else // CHILD
       {
                printf("\n [ CHILD ] :  Enter\n");
               
                // SORT THE SECOND ARRAY
                printf("\n [ CHILD ] :  Sorting\n");
                bubbleSort(arrayB,sizeB);
                
                // EXIT
                printf("\n [ CHILD ] : EXITING\n");
                exit(1);
       }
}
// main END
