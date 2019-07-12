#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

void binarySearch(int n,int array[],int key)
{
    int i=0,fs,ls,m;
    fs= 0;
    ls = n-1;
    m = (fs+ls)/2;
    while(1)
    {
       
        i++;
        if(i==10)
         break;
        if(key == array[m])
        {
            printf("Found at position %d!\n",m);
            break;
        }
        else if(key < array[m])
        {
            if(ls==m)
            {
                printf("\nNOT FOUND !\n");
                break;
            }
            ls = m;
            m = (fs+ls)/2;
        }
        else if(key > array[m])
        {
            if(m==fs)
            {
                printf("\nNOT FOUND !\n");
                break;
            }
            fs = m;
            m = (fs+ls)/2;
        }
    }      

}

int main(int argc, char *argv[])
{
    int i,key,*array;
    array = (int *) malloc(sizeof(int)*argc);
    printf("\nEnter the element you want to search : ");
    scanf("%d",&key);
    for(i=0;i<argc;i++)
    {
        *(array+i) = atoi(argv[i]);
    }
    binarySearch(argc,array,key);
    return(0);
}
