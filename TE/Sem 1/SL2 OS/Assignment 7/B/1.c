

// NOTE : THIS IS THE FIRST PROCESS

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX 1000

int main()
{
    int fd, ch;

    char *filename = "/tmp/contain1.txt", str[MAX];
    char *stats = "/tmp/contain2.txt";
    mkfifo(filename, 0666);
      mkfifo(stats, 0666);
    fd = open(filename, 0666);
    printf("\nPlease Enter the Data you want to on the file\n");
    scanf("%[^\t]s", str);
    write(fd, str, strlen(str) + 1);
    int fd2 = open(stats, O_RDONLY); 
    // read(fd2, str, MAX);
    // printf("\nREAD : \n %s",str);
    close(fd2);
    close(fd);
    return 0;
}
