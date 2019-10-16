

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
    int charCount = 0;
    int lineCount = 0;
    int wordCount = 0;
    int i = 0;
    
    char *filename = "/tmp/contain.txt";
    char *stats = "/tmp/contain2.txt";
    mkfifo(filename, 0666);
    mkfifo(stats, 0666);
    fd = open(filename, O_RDONLY);
    read(fd, str, MAX);
    int fd2 = open(stats, O_WRONLY);
    // TODO :
    // Convert stats to string and write it to the stats.txt
    charCount = count_chars(str);
    wordCount = count_words(str);
    lineCount = count_lines(str);

    FILE *file = fopen("/home/oslab-14/33308/Assignment 7/B/stats.txt", "w");
    fprintf(file, "Character Count: %d\nWord Count: %d\nLine Count: %d\n", charCount, wordCount, lineCount);
    fclose(file);
    write(fd2, str, strlen(str) + 1);
    // write contain of filename
    close(fd2);
    close(fd);
    return 0;
}
