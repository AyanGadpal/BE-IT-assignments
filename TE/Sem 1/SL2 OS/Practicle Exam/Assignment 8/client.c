/*
Name        : IPC
Auther      : Ayan Naresh Gadpal
Copyright   : GNU public Library
Description : Reader Writer 
Date        : Fri Oct 19 2019 ,10:14 PM
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE 10

struct keyServed
{
        char key[SIZE];
        int status;
};


int main()
{
        int id;
        struct keyServed *shared;
        
        id = shmget((key_t)1234,sizeof(struct keyServed),0666 | IPC_CREAT);
        shared=(struct keyStruct *)shmat(id,NULL,0);
        
        while (1)
        {
                if(shared->status == 0)
                {
                        printf("\nServer says : %s",shared->key);
                
                        shared->status = 1;
                }
        }
        return 0;
}


