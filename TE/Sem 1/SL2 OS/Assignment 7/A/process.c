#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>  
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

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
	 
    int FNSender[2], contain[2];
   
    // CREATING TWO PIPE FOR BIDIRECTION APPROCH
 
    if (pipe(FNSender) == -1) // TO SENT FILENAME P -> C
    {
               perror("FNSender ERROR");
               exit(EXIT_FAILURE);
    }
    
    if (pipe(contain) == -1) // TO SENT CONTAIN C -> P
    {
               perror("Contain ERROR");
               exit(EXIT_FAILURE);
    }

    pid_t pid = fork(); // FORKING CHILD PROCESS
    if(pid == -1)
    {
               perror("fork");
               exit(EXIT_FAILURE);
    }


    if (pid != 0) // PARENT
    {
        char *filename = "file.txt";
        char input[SIZE];
        
        // PASS THE NAME OF THE FILE
        printf("\n[ PARENT ]: PASSING THE FILE NAME");
        write(FNSender[1], filename, (int)strlen(filename));
        
        // WAIT FOR CHILD TO READ AND PASS CONTAIN
        printf("\n[ PARENT ]: WAITING FOR CONTAIN");
        read(contain[0], input, SIZE);
        
        // DISPLAY THE CONTAIN
        printf("\n[ PARENT ]: CONTAIN OF FILE : %s", input);
    
    	wait(NULL);                /* Wait for child */
        exit(EXIT_SUCCESS);

    }
    else // CHILD
    {
        char inputBuffer[SIZE];
        char filename[8];
        
        // WAIT FOR FILE NAME
        printf("\n[ CHILD ]: WAITING FOR FILENAME");
        read(FNSender[0], filename, 8);
        
       	// OPEN THE FILE
        printf("\n[ CHILD ] : OPENING FILE %s\n", filename);
        int fd = open(filename, O_RDONLY | O_CREAT);
        
        // READ CONTAIN OF THE FILE
        printf("[ CHILD ] : READING FILE\n");
        read(fd, inputBuffer, SIZE);
        
        // SEND THE CONTAIN TO PARENT
        printf("[ CHILD ] : SENDING CONTAIN TO FILE\n");
        write(contain[1], inputBuffer, SIZE);
       
       	// CLOSE THE FILE
        close(fd);
        
        _exit(EXIT_SUCCESS);
    }

    return 0;
}
