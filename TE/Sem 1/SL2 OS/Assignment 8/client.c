/*====================================================
Auther : Ayan N Gadpal K11 33308
Code : Client Server Using Shared Memory
Date : Sep 10 2019
Copyright : GNU public Library
=====================================================*/

// CLIENT CODE

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE 10

struct keyServed
{
    int server_done;
    char key[SIZE];
};

int main()
{
    // To Store shared memory id
    int shmid;

    void *sharedMemory = (void *)0;
    struct keyServed *sharedStuff;

    shmid = shmget((key_t)1234, sizeof(struct keyServed), 0666 | IPC_CREAT);

    sharedMemory = (void *)shmat(shmid, NULL, 0);

    sharedStuff = (struct keyServed *)sharedMemory;
    printf("\n%d\n", (int )sharedMemory);
    while (1)
    {
        if (sharedStuff->server_done == 0)
        {
            printf("\nServer's Says:  %s \n", sharedStuff->key);
            sharedStuff->server_done = 1;
        }
    }
    return 0;
}
