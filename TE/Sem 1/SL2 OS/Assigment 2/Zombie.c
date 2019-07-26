/*====================================================
Auther : Ayan N Gadpal K11 33308
Code : Assignment 2 Part A Zombie Code 
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
        printf("[ PARENT ] : ID %d\n", getpid());

        // wait();
        while (1)
            ; // INFINITE LOOP

        // THESE INSTRUCTION WILL NEVER GET EXECUTE
        printf("[ PARENT ] : Child Exitted , I am Going Byee\n");
        exit(-1);
    }
    else // CHILD
    {
        printf("[ CHILD ] : I am child , My ID is %d\n", getpid());
        printf("[ CHILD ] : My Parent is %d\n", getppid());
        sleep(3);

        // ANY PROCESS OF CHILD
        printf("[ CHILD ] : LALALAL, i am singing\n");

        printf("[ CHILD ] : My Work is Done i am Exiting , byee\n");
        exit(0);
    }

    return 0;
}
