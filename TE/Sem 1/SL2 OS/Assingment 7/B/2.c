/*====================================================
Auther : Ayan N Gadpal K11 33308
Code : Matrix Multiplication using multithreading
Date : Sep 6 2019
Copyright : GNU public Library
=====================================================*/

// NOTE : THIS IS THE SECOND PROCESS

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX 1000

int count_chars(char *str)
{

    int count = 0;
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] != '\n' && str[i] != ' ')
            count++;
        i++;
    }
    count++;
    return count;
}

int count_lines(char *str)
{

    int count = 0;
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\n')
            count++;
        i++;
    }
    count++;

    return count;
}

int count_words(char *str)
{
    int count = 0;
    int i = 0;

    while (str[i] != '\0')
    {
        if (str[i] == ' ' || str[i] == '\n')
            count++;
        i++;
    }
    count++;

    return count;
}

int main()
{
    char str[MAX];
    int fd;
    int count = 0;
    int i = 0;
    char *filename = "/tmp/contain.txt";
    char *stats = "/tmp/stats.txt";
    mkfifo(filename, 0666);
    mkfifo(stats, 0666);
    fd = open(filename, O_RDONLY);
    read(fd, str, MAX);
    int fd2 = open(stats, O_WRONLY);  
    // TODO :
    // Convert stats to string and write it to the stats.txt
    // write contain of filename

    close(fd);
    return 0;
}
