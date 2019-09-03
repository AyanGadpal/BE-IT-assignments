#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
    char str[80],str2[80];
    char *filename = "file.txt";
    mkfifo(filename,0666);
    while (1)
    {
        int fd = open(filename, O_WRONLY);
        read(fd, str, 80);
        printf("USER 1 : %s\n", str);
        close(fd);

         fd = open(filename, O_WRONLY);
        fgets(str2, 80, stdin);
        write(fd, str2, strlen(str2) + 1);
        close(fd);
    }

    return 0;
}