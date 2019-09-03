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
    while(1)
    {
        int fd = open(filename,O_WRONLY);
        fgets(str,80,stdin);
        write(fd,str,strlen(str)+1);
        close(fd);

        fd = open(filename,O_WRONLY);
        read(fd,str2,80);
        printf("USER 2 : %s\n",str2);
        close(fd);
    }

    return 0;
}