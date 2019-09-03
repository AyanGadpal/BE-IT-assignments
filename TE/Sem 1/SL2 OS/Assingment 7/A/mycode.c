#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#define SIZE 9

int main()
{
    int FNSender[2], contain[2];

    pipe(FNSender);
    pipe(contain);

    int pid = fork();

    if (pid != 0) // PARENT
    {
        char *filename = "temp.txt";
        char input[SIZE];
        write(FNSender[1], filename, (int)strlen(filename));
        read(contain[0], input, SIZE);
        printf("\n[ PARENT ]: CONTAIN OF FILE : %s", input);
    }
    else // CHILD
    {
        char inputBuffer[9];
        char filename[8];
        read(FNSender[0], filename, 8);
        printf("\n[ CHILD ] : OPENING FILE %s\n", filename);
        int fd = open(filename, O_RDONLY | O_CREAT);
        printf("[ CHILD ] : READING FILE\n");
        read(fd, inputBuffer, SIZE);
        printf("[ CHILD ] : SENDING CONTAIN TO FILE\n");
        write(contain[1], inputBuffer, SIZE);
        close(fd);
    }

    return 0;
}
