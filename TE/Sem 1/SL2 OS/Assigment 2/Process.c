#include <stdio.h>
#include <stdlib.h>
 #include <sys/types.h> 
#include <unistd.h>
int main()
{
    printf("\nI am Main : %d\nMy Parents Bash is %d\n", getpid(), getppid());
    int status = fork();
    if (status != 0) // PARENT
    {
        printf("[ PARENT ] : ID %d\n",getpid());
        printf("[ PARENT ] : Waiting for child to Exit\n");
        //wait();
        while(1);
        printf("[ PARENT ] : Child Exitted , I am Going Byee\n");
        exit(-1);
    }
    else // CHILD
    {
        printf("[ CHILD ] : I am child , My ID is %d\n",getpid());
        int ppid ;
        printf("[ CHILD ] : My Parent is %d\n",ppid=getppid());
        sleep(5);
        if( ppid != getppid())
        {   
            printf("[ CHILD ] : I AM NOW ORPHAN");
            printf("[ CHILD ] : Now My Parent is %d\n",getppid());
        }
        printf("[ CHILD ] : LALALAL, i am singing\n");
        
        printf("[ CHILD ] : My Work is Done i am Exiting , byee\n");
        exit(0);
    }

    return 0;
}
