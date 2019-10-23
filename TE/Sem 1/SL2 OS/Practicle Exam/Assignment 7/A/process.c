#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#define SIZE 24 // INPUT SIZE
/*

ALGORITHM 
TODO 
1) CREATE TWO PIPE
2) FORK CHILD
3) PARENT WRITE THE FILENAME TO PIPE1
4) CHILD READ THE FILNAME FROM PIPE1
5) CHILD OPEN THE FILE OF THAT FILE NAME
6) CHILD READ THE CONTAIN OF THAT FILE
7) CHILD WRITE THAT CONTAIN TO PIPE2
8) PARENT READ THE CONTAIN OF PIPE2
9) PARENT DISPLAY IT
10) DONE BOTH EXIT

*/

int main()
{
        int fd[2],fd2[2];
        
        pipe(fd);
        pipe(fd2);
        
        pid_t id = fork();
        if(id<0)
                printf("\nERROR\n");
        if(id!=0)
        {
                // PARENT 
                char *filename = "contain.txt";
                char input[24];
                
                write(fd[1],filename,(int)strlen(filename));
                
                wait(NULL); 
                
                read(fd2[0],input,24);
                printf("\n%s\n",input);
        }
        else   // CHILD
        {       
                char filename[12];
                char input[24];
                read(fd[0],filename,12);
                printf(" CHILD %s\n",filename);
                int fileD = open(filename,O_RDONLY | O_CREAT);
                read (fileD,input,24);
   
                write(fd2[1],input,(int)strlen(input));
                exit(0);                         
        }
        

}
