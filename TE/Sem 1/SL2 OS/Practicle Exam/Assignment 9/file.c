/*============================================
Name        : FILE
Auther      : Ayan Naresh Gadpal
Copyright   : GNU public Library
Description : FILE
Date        : Fri Oct 19 2019 ,10:14 PM
==============================================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

typedef struct student 
{
        int roll;
        char name[20];
}Student;
char *filename = "Record.dat";

void line()
{
        printf("\n==================================n");
}
void createFile()
{
        int fd = open(filename,O_CREAT | O_RDONLY,0666);
        if(fd == -1)
                printf("\nERROR WHILE OPENING THE FILE\n");
        else
                printf("\nFILE OPENED SUCCEFULLY !");
        close(fd);
}

void insertData()
{
        Student S;
        printf("\nEnter The Name of Student : ");
        scanf("%s",S.name);
        printf("\nRoll No. : ");
        scanf("%d",&S.roll);
        int fd = open(filename,O_CREAT | O_WRONLY | O_APPEND,0777);
        if(fd == -1)
                printf("\nERROR WHILE OPENING THE FILE\n");
        
        write(fd,&S,sizeof(Student));  
        close(fd);
}

void display()
{
        int fd = open(filename,O_RDONLY);
        if(fd == -1)
                printf("\nERROR WHILE OPENING THE FILE\n");
        
        Student S;
        while(read(fd,&S,sizeof(S)))
        {
                printf("\n%s %d",S.name,S.roll);
        }
        close(fd);
}

void search()
{
        int fd = open(filename,O_RDONLY);
        if(fd == -1)
                printf("\nERROR WHILE OPENING THE FILE\n");
        
        Student S;
        int roll;
        printf("\nEnter the roll you want to search for : ");
        scanf("%d",&roll);
        while(read(fd,&S,sizeof(S)))
        {
               if(S.roll == roll)
               {
                        printf("\nFound ! \n Name : %s",S.name);
                        close(fd);
                        return;
               }
        }
        printf("\nNot Foound !");     
        
        close(fd);
}

void removeF()
{
        char *temp = "t.dat";
        int fd2 = open(temp,O_RDWR | O_CREAT | O_APPEND);
        int fd = open(filename,O_RDONLY);
        if(fd == -1)
                printf("\nERROR WHILE OPENING THE FILE\n");
        
        Student S;
        int roll;
        printf("\nEnter the roll you want to Remove for : ");
        scanf("%d",&roll);
        while(read(fd,&S,sizeof(S)))
        {
               if(S.roll == roll)
               {
                     continue;
               }
               else
               {
                    printf("\n1");
                    write(fd2,&S,sizeof(Student));
               }
        }
        close(fd);
        close(fd2);
    
        
        
        remove(filename);
        rename(temp,filename);
        
}

int main()
{
        int ch;
        while(1)
        {
                line();
                printf("\nPlease Select the Option");
                printf("\n1) Create / Open the File ");
                printf("\n2) Insert Data");
                printf("\n3) Display Data");
                printf("\n4) Remove Data");
                printf("\n5) Search Data");
                printf("\n6) Modify Data\n7) Exit\nYour Choice : ");
                scanf("%d",&ch);
                switch(ch)
                {
                       case 1:
                               createFile();
                       break;
                       case 2:
                               insertData();
                       break;       
                       case 3:
                               display();
                       break;       
                       case 4:
                               removeF();
                       break;       
                       case 5:
                                search();
                       break; 
                       case 7:
                                // Saying Farewell
                                printf("\nBye\n");
                                exit(0);
                       break;
                       case 6:
                                printf("7");
                       break;
               }
                
        }
        return 0;
}
