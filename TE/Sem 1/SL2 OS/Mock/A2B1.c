/*==============================================
NAME : AYAN N GADPAL
BATCH : K11
ROLL NO : 33308
===============================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void line()
{
	printf("\n==============================================\n");
}

// Accept Array
// n : size 
void input(int n,int *array)
{
	int i =0;
	for(i=0;i<n;i++)
	{
		printf("\n%d) : ",i+1);
		scanf("%d",array+i);
	}
}

// Print The Array
void output(int n,int *array)
{
	int i =0;
	for(i=0;i<n;i++)
		printf("\n%d):%d \n",i+1,*(array+i));
}

// Swap
void swap(int *a,int *b)
{
	int T;
	T = *a;
	*a = *b;
	*b = T;
}

// Bubblesort
void Bubblesort(int n,int *array)
{
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<n-i-1;j++)
		{
			if(array[j]>array[j+1])
				swap(array+j,array+j+1);
		}
	}

	int main()
	{
		int i=0,n,*array;
		char *a[10],*res;
		line();

	// Accept Size of array
		printf("\nEnter the no. of Elements \n");
		scanf("%d",&n);

	// Allocate Memory
		array = (int *)malloc(sizeof(int)*n);
		printf("\nsEnter the Array \n");
		input(n,array);
		line();

	// Display Array
		printf("\nArray Inputted is \n");
		output(n,array);
		line();

	// Sort The Array
		Bubblesort(n,array);
		printf("\nSORTING ARRAY !\n");
		line();

	// Display the Sorted Array
		printf("\nSorted Array \n");
		output(n,array);

	// Covert the Array to String
		for(i=0;i<n;i++)
		{
			res = (char *)malloc(sizeof(char));
			sprintf(res,"%d",array[i]);
			a[i]=(char *)malloc(sizeof(char));
			a[i]=res;
		}
		sleep(5);
	// CREATING Parent and child Proccesses
		pid_t status = fork();

		if(status > 0) // PARENT
		{
			printf("\n[ PARENT ] : WAITNG FOR CHILD \n");
			wait(NULL);
		}
		else if(status < 0 )
			printf("\nPROCESS WENT WRONG\n");
		else // CHILD
		{	
			printf("\n[ CHILD ] : PASSING STRING TO NEXT PROGRAM\n");
			execvp("./second.out",a);
		}


		return(EXIT_SUCCESS);
	}
