/*
NAME : AYAN N GADPAL
BATCH : K11
ROLL NO : 33308
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int binary(int arr1[],int key,int n)
{
	int last=n-1,first=0,mid=0+(n-1)/2;
	while(first<=last)
	{
		mid=(first+last)/2;
		if(key == arr1[mid])
		{
			printf("NUMBER FOUND");
			return arr1[mid];
		}
		else if(key<arr1[mid])
		{
			last=mid-1;		
		}
		else
		{
			first=mid +1;	
		}	
	}
	printf("NUMBER NOT FOUND");
	return -1;
}	

// Print The Array
void output(int n,int *array)
{
	int i =0;
	for(i=0;i<n;i++)
		printf("\n%d):%d ",i+1,*(array+i));
}

int main(int argc,char *argv[])
{
	int i=0;
	int *array,key;
	printf("REACHED THIS PROCESS");
	array = (int *)malloc(sizeof(int)*argc); 

	for(i=0;i<argc-1;i++)
		printf("\n%d):%s ",i+1,argv[i]);

	for(i=0;i<argc-1;i++)
		array[i]=atoi(argv[i]);

	output(argc-1,array);

	printf("\nEnter the key You want to Search : ");
	scanf("%d",&key);
	binary(array,key,argc-1);
	return(EXIT_SUCCESS);
}
