#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    int i;
    for(i=0;i<argc;i++)
    {
        printf("%c ",*argv[i]);
    }
    return(0);
}