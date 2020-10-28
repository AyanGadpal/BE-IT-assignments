/*====================================================
Auther : Ayan N Gadpal P11 43308
Code : RSA Algorithm using client server, this is server code
Date : Aug 20 2020
=====================================================*/

// SERVER CODE
#include <iostream>
#include <string.h>
#include <math.h>

// MUST BE INCLUDED IN SAME SEQUENCE
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE 20 // Size of message  string

using namespace std;

struct keyServed
{
    int server_done;
    double c1;
    double d,n;
    keyServed(){server_done=1;}
};
int gcd(int a, int b)
{
    while (b)
    {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

double getE(double phi)
{
    int flag =0;
    double e;
    for(e = 2;e<phi;e++)
    {
        flag = gcd(e,phi);
        if(flag==1)
            break;
    }

    return e;
}

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

    sharedStuff->server_done = 1;

    // Pooling
    while (1)
    {
        if (sharedStuff->server_done == 1)
        {
            double message;
            cout<<"\n Enter the Message : ";
            cin>>message;
            double p = 11;
            double q = 17;    
            sharedStuff->n = p*q;
            double phi = (p-1)*(q-1); // Total number of co prime of 'n'
            double e = getE(phi);
            sharedStuff->d=fmod((1/e),phi); // Decryption key, satisfies d*e = 1 mod phi
            sharedStuff->c1 = pow(message,e);

            cout<<"\n Encrypted : "<<sharedStuff->c1;
            sharedStuff->server_done = 0;
        }
    }
    return 0;
}
