/*====================================================
Auther : Ayan N Gadpal K11 33308
Code : Matrix Multiplication using multithreading
Date : Sep 6 2019
Copyright : GNU public Library
=====================================================*/

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

    char *filename = "/tmp/contain.txt", str[MAX];
    char *stats = "/tmp/stats.txt";
    mkfifo(filename, 0666);
    mkfifo(stats, 0666);
    fd = open(filename, 0666);
    printf("\nPlease Enter the Data you want to on the file\n");
    scanf("%[^\t]s", str);
    write(fd, str, strlen(str) + 1);
    int fd2 = open(stats, O_RDONLY);
    close(fd);
    return 0;
}
