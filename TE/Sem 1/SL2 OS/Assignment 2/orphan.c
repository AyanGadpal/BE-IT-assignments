/*====================================================
Auther : Ayan N Gadpal K11 33308
Code : Assignment 2 Part A Orphan Code 
Date : Jun 5 2019
Copyright : GNU public Library
=====================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    // Printing the main ID and its Parent ID
    printf("\nI am Main : %d\nMy Parents Process is %d\n", getpid(), getppid());

    // CREATING NEW CHILD PROCESS
    int status = fork();

    if (status != 0) // PARENT
    {
        // PRINT ID
        printf("[ PARENT ] : ID Ayan%d\n", getpid());

        // THESE INSTRUCTION WILL NEVER GET EXECUTE
        printf("[ PARENT ] : I am exiting without waiting for the child\n");
        exit(-1);
    }
    else // CHILD
    {
        int ppid;
        printf("[ CHILD ] : I am child , My ID is %d\n", getpid());
        printf("[ CHILD ] : My Parent is %d\n", ppid = getppid());
        sleep(5);
        if (ppid != getppid())
        {
            printf("[ CHILD ] : I AM NOW ORPHAN");
            printf("[ CHILD ] : Now My Parent is %d\n", getppid());
        }
        printf("[ CHILD ] : LALALAL, i am singing\n");

        printf("[ CHILD ] : My Work is Done i am Exiting , byee\n");
        exit(0);
    }

    return 0;
}
