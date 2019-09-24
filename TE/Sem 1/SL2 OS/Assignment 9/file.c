/*====================================================
Auther : Ayan N Gadpal K11 33308
Code : Databse using Low level file calls
Date : Sep 24 2019
Copyright : GNU public Library
=====================================================*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

struct student
{
  char rollNo[10], class[10];
  char name[20];
};

// OPEN THE FILE
void openFile(char *filename)
{
  int fd = open(filename, O_RDWR | O_CREAT, 0777);
  if (fd == -1)
    printf("\nERROR : UNABLE TO OPEN THE FILE\n");
  else
    printf("\nSYSTEM : FILE OPENED SUCCESSFULLY \n");
  close(fd);
}

// READ
void ReadFile(char *filename)
{
  int fd = open(filename, O_RDONLY, 0777);
  char str;
  int i = 0;
  while (read(fd, &str, 1) > 0)
  {
    printf("%c", str);
    i++;
  }
  printf("\nTOTAL READ : %d", i);
  close(fd);
}

// WRITE
void WriteFile(char *filename)
{
  int fd = open(filename, O_WRONLY | O_APPEND, 0777);
  struct student std;

  printf("\nEnter the Name of Student : ");
  scanf("%s", std.name);
  printf("\nEnter the Roll No ( Two Digit ) of Student : ");
  scanf("%s", std.rollNo);
  printf("\nEnter the Class of Student : ");
  scanf("%s", std.class);
  write(fd, std.rollNo, strlen(std.rollNo));
  write(fd, " ", 1);
  write(fd, std.name, strlen(std.name));
  write(fd, " ", 1);
  write(fd, std.class, strlen(std.class));
  write(fd, "\n", 1);
  close(fd);
}
void search(char *filename)
{
  int fd = open(filename, O_RDONLY, 0777);
  printf("\nEnter Roll No.\n");
  char *rollno,rollnoK[5], str;
  rollno = (char *)malloc(sizeof(char)*5);
  scanf("%s", rollnoK);
  rollno[0] = "\0";
  while (read(fd, &str, 1) > 0)
  {
    if (str != 0x20)
      rollno = strcat(rollno, &str);
    else
    {
        if(strcmp(rollno,rollnoK)==0)
        {
          printf("Found");
          return;
        }
        else
        {
          rollno = (char *)malloc(sizeof(char)*5);
          rollno[0] = "\0";
        } 
    }  
  }
   close(fd);
}

int main()
{
  char filein[30];
  int ch = 0;
  printf("\nEnter The Name of the file along with extension : \n");
  scanf("%s", filein);
  // char *c = (char *)calloc(100, sizeof(char));
  openFile(filein);

  while (1)
  {
    printf("\nEnter the Appropiate Choice\n");
    printf("\n1) Read All Records");
    printf("\n2) Write Record");
    printf("\n3) Search Record");
    printf("\n4) Modify Record");
    printf("\n5) Delete Record");
    printf("\n6) Exit\nYour Choice : ");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
      /* READ */
      ReadFile(filein);
      break;

    case 2:
      /* WRITE */
      printf("\nHow Many Records you want to add ?\n");
      scanf("%d", &ch);
      while (ch > 0)
      {
        ch--;
        WriteFile(filein);
      }

      break;

    case 3:
      /* SEARCH */

      break;

    case 4:
      /* MODIFY */

      break;

    case 5:
      /* DELETE */

      break;

    case 6:
      /* EXIT */
      return (EXIT_SUCCESS);
      break;

    default:

      break;
    }
  }
}
