/*
Name        : IPC
Auther      : Ayan Naresh Gadpal
Copyright   : GNU public Library
Description : Reader Writer 
Date        : Fri Oct 19 2019 , 7:38 PM
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>      
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define MAX 100
int main()
{
        printf("READING");
        char str[MAX];
        fflush(stdin);
        char *file = "/tmp/file";
        mkfifo(file,0666);
        int fd = open(file,O_RDONLY);
        read(fd,str,MAX);
        printf("%s",str);
        
        
        close(fd);
        return 0;
}
