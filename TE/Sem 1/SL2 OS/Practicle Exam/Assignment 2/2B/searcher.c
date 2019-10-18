/*
Name        : Process control System calls
Auther      : Ayan Naresh Gadpal
Copyright   : GNU public Library
Description : Take an Array, Parent will sort it and child will pass it to program via execve() for      searching
Date        : Fri Oct 18 2019 , 3:21 PM
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// display START
void display(int *array,int size)
{
       int i;
       // Display Each Element from the array
       for(i=0;i<size;i++)
           printf("%d) %d \n",i+1,array[i]);
}
// display END

// binary search START
void binary(int *array,int size,int key)
{
        int fs,ls,m,i=0;
        fs = 0;
        ls = size -1;
        m = (fs+ls)/2;
        
        while(1)
        {
                i++;
                if(i==size)
                {
                        printf("not found");    
                        break;
                }
                else if(array[m]==key)
                {
                        printf("found");
                        break;
                }
                else if(key < array[m])
                {
                        if(m == ls)
                        {
                         printf("not found");
                         break;
                        }
                        ls = m;
                        m = (fs+ls)/2;
                }
                else if(key > array[m])
                {
                        if(m == fs)
                        {
                         printf("not found");
                         break;
                        }
                        fs = m;
                        m = (fs + ls + 1)/2;
                }
        }
        

}
// binary search END

int main(int argc,char *args[])
{
    printf("\nENTERED IN SEARCHER\n");
    int i,*array,key;
    
    array = malloc(sizeof(int)*(argc));
    
    printf("\n\n\nIN B\n\n");
    for(i=0;i<argc;i++)
        array[i] = atoi(args[i]);
        
    display(array,argc);
    
    printf("\nEnter the key to Search\nKEY : ");
    scanf("%d",&key);
    binary(array,argc,key);
        
    return (0);

}
