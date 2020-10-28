/*====================================================
Auther : Ayan N Gadpal P11 43308
Code : RSA Algorithm using client server, this is client code
Date : Aug 20 2020
=====================================================*/

// CLIENT CODE
#include <iostream>
#include <string.h>
#include <math.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE 20
using namespace std;

struct keyServed
{
    int server_done;
    double c1;
    double d,n;
    keyServed(){server_done=1;}
};

int main()
{
     // To Store shared memory id
    int shmid;

    void *sharedMemory = (void *)0;// NULL
    
    struct keyServed *sharedStuff;

    
    // Create Memory
    shmid = shmget((key_t)2324, sizeof(struct keyServed), 0666 | IPC_CREAT);

    // Get the Base Address of SM
    sharedMemory = (void *)shmat(shmid, NULL, 0);

    // Attach
    sharedStuff = (struct keyServed *)sharedMemory;


    // Pooling
    while (1)
    {
        if (sharedStuff->server_done == 0)
        {
            double m = pow(sharedStuff->c1,sharedStuff->d); 
            m=fmod(m,sharedStuff->n);
            cout<<"\nServer's Cipher: " <<sharedStuff->c1;
            cout<<"\nServer's Says: " <<m<<"\n";
            sharedStuff->server_done = 1;
        }
    }
    return 0;
}
