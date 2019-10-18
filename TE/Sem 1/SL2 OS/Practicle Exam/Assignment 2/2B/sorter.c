/*
Name        : Process control System calls
Auther      : Ayan Naresh Gadpal
Copyright   : GNU public Library
Description : Take an Array, Parent will sort it and child will pass it to program via execve() for      searching
Date        : Fri Oct 18 2019 , 3:20 PM
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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

int main(){
     
     int *array,size,i;
     char *rst;
     array = input(array,&size);
     
     char *args[size+1];
        
     bubbleSort(array,size);
     
     // Convert to String
     for(i=0;i<size;i++)
     {
        rst = malloc(sizeof(int));
        sprintf(rst,"%d",array[i]);
        args[i] = malloc(sizeof(int));
        args[i] = rst;
     }
     
     printf("Forking...\n");   
     
     // VERY VERY ,SUPER VERY IMPORTANT
     args[size] = NULL;
        
     pid_t id=fork();
     
     if (id <0)
        printf("\nFORK FAILED\n");
     else if( id != 0)
     {
        wait(NULL);
        printf("\nEXIT\n");
        exit(0);
     }
     else
     {
        // Execute the process here
        if( -1 == execvp("./b.out", args))
        {
          printf("\nFAILED\n");
        }
        exit(0);
     }
     return (0);
}
