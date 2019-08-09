/*====================================================
Auther : Ayan N Gadpal K11 33308
Code : Producer Consumer Problem
Date : AUG 09 2019
Copyright : GNU public Library
=====================================================*/

// NOTE : PLEASE RUN IT WITH '-lpthread'

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

// Buffer Size
#define BUF_SIZE 5

// Threads for producer and consumer
pthread_t producer, consumer;

// Mutex Lock
pthread_mutex_t lock;

// Semaphore to keep the status of Buffer data
sem_t full, empty;

// Defining the Buffer
int buffer[BUF_SIZE];

// Indices for producer and consumer
int pid, cid;

// Print a Line For Output Formatting
void line()
{
    printf("\n================================================\n");
}

// Producer Thread Function
void *producer_thread(void *agr)
{
    // Keep track of the ID of producer
    int *num = (int *)agr;
    while (1) // KEEP PRODUCING
    {
        // Take a random value (1 to 4)
        int temp = rand() % 5, i;

        // If 'temp' is zero ,then change it to a value
        temp = temp == 0 ? 2 : temp;

        // Give Random Sleep to emulate random behaviour
        sleep(temp);

        // Decrement the empty
        sem_wait(&empty);

        // Lock the Mutex
        pthread_mutex_lock(&lock);

        // ENTERING THE CRITICAL SECTION
        line();
        printf("Producer %d", *num);

        // Producing an item
        buffer[pid] = temp;

        // Displaying the buffer
        printf("\nBUFFER : [ ");
        for (i = 0; i < BUF_SIZE; i++)
        {
            printf("%d ", buffer[i]);
        }
        printf("]");

        // Updating the producer index
        pid = (pid + 1) % BUF_SIZE;

        // EXITTING CRITCAL SECTION BY UNLOCKING MUTEX
        pthread_mutex_unlock(&lock);

        // Increamenting the full status
        sem_post(&full);
    }
}

void *consumer_thread(void *agr)
{
    // Keep track of the number of consumer
    int *num = (int *)agr;
    while (1) // KEEP CONSUMING
    {
        // Take a random value (1 to 4)
        int temp = rand() % 5, i;

        // If 'temp' is zero ,then change it to a value
        temp = temp == 0 ? 2 : temp;

        // Give Random Sleep to emulate random behaviour
        sleep(temp);

        //  Decrementing the full status
        sem_wait(&full);

        // Lock the Mutex
        pthread_mutex_lock(&lock);

        // ENTERING THE CRITICAL SECTION

        // Consuming Item
        buffer[cid] = 0;

        // Updating the index for consumer
        cid = (cid + 1) % BUF_SIZE;
        line();
        printf("                       Consumer %d", *num);

        // Printing the BUFFER
        printf("\n                      BUFFER : [ ");
        for (i = 0; i < BUF_SIZE; i++)
        {
            printf("%d ", buffer[i]);
        }
        printf("]");

        // EXITTING CRITCAL SECTION BY UNLOCKING MUTEX
        pthread_mutex_unlock(&lock);

        // Increamenting the empty status
        sem_post(&empty);
    }
}

int main()
{
    // prcon : producer Count
    // cocon : consumer Count
    int i, prcon, cocon, result;

    printf("\nEnter the number of Producers : ");
    scanf("%d", &prcon);

    printf("\nEnter the number of Consumer : ");
    scanf("%d", &cocon);

    // Initializing the empty semaphore
    result = sem_init(&empty, 0, BUF_SIZE);
    if (result != 0)
    {
        printf("\nERROR : EMPTY INTIALIZTION");
    }

    // Initializing the full semaphore
    result = sem_init(&full, 0, 0);
    if (result != 0)
    {
        printf("\nERROR : FULL INTIALIZAION");
    }

    // Initializing the mutex lock
    result = pthread_mutex_init(&lock, NULL);
    if (result != 0)
    {
        printf("\nERROR : MUTEX INITALIAZATION");
    }

    // Initalizaing the Index for both producer and consumer
    pid = cid = 0;
    int *arg;
    for (i = 0; i < prcon; i++)
    {
        // Allocating a different memory for each thread id (as 'i' is their id)
        arg = (int *)malloc(sizeof(int));
        *arg = i;

        // Creating a producer thread
        result = pthread_create(&producer, NULL, producer_thread, (void *)(arg));
        if (result != 0)
        {
            printf("\nERROR : Producer Creation");
        }
    }
    for (i = 0; i < cocon; i++)
    {
        // Allocating a different memory for each thread id (as 'i' is their id)
        arg = (int *)malloc(sizeof(int));
        *arg = i;

        // Creating a consumer thread
        result = pthread_create(&consumer, NULL, consumer_thread, (void *)(arg));
        if (result != 0)
        {
            printf("\nERROR : Consumer Creation");
        }
    }

    // WAITING FOR THE THREADS
    result = pthread_join(producer, NULL);
    if (result != 0)
    {
        printf("\nERROR : PRODUCER JOIN ");
    }
    result = pthread_join(consumer, NULL);
    if (result != 0)
    {
        printf("\nERROR : Consumer JOIN");
    }
    return 0;
}
