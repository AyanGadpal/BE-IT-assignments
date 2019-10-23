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
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAX 100

int main()
{
        char str[MAX];
        fflush(stdin);
      
        char *file = "/tmp/file";
        //char *con = "/tmp/contain.txt";
        
        mkfifo(file,0666);
       // mkfifo(con,0666);
        
        int fd = open(file,0666 | O_WRONLY | O_CREAT);
        printf("Enter the String\n");
        scanf("%s",str);
        printf("%s",str);
        
        write(fd,str,(int)strlen(str));
        close(fd);
        return 0;
}
