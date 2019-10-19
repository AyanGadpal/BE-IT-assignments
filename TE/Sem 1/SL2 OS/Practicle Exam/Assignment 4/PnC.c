/*
Name        : Process Synchronazation
Auther      : Ayan Naresh Gadpal
Copyright   : GNU public Library
Description : Producer Consumer
Date        : Fri Oct 19 2019 , 10:48 AM
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>

// Buffer Size
#define SIZE 5

// Producer and consumer thread
pthread_t producer,consumer;
int buffer[SIZE];

// Defining lock and semaphore
sem_t empty,full;
pthread_mutex_t lock;

int pid=0,cid=0;

// Print a Line For Output Formatting
void line()
{
    printf("\n================================================\n");
}

void *producing(void *p)
{
        int *is,i;
        is = (int *)p;
        int id = *is;
        printf("\nProducer %d\n",id);
        while(1)
        {
             int temp = rand() % 3;
             temp = temp == 0 ? 2 : temp;
             sleep(temp);
             
             sem_wait(&empty);
             
             pthread_mutex_lock(&lock);
             // CRITICAL SECTION
             line();
             printf("\n%d is producing \n",id);
             buffer[pid] = temp;
             printf("\nBUFFER : [ ");
             for (i = 0; i < SIZE; i++)
             {
                    printf("%d ", buffer[i]);
             }
             printf("]");
             
             
             pid = (pid + 1) % SIZE;   
             
             pthread_mutex_unlock(&lock);
             
             sem_post(&full);
        
        }        
        pthread_exit(NULL);        
}

void *consuming(void *p)
{
        int *is,i;
        is = (int *)p;
        int id = *is;
        printf("\nConsuming %d\n",id);
        while(1)
        {
             int temp = rand() % 3;
             temp = temp == 0 ? 2 : temp;
             sleep(temp);
             
             sem_wait(&full);
             
             pthread_mutex_lock(&lock);
             // CRITICAL SECTION
             line();
             printf("\n<<<<<<<<<<<<<<<<<<<<<<<%d is Consuming \n",id);
             buffer[cid] = 0;
              // Displaying the buffer
             printf("\nBUFFER : [ ");
             for (i = 0; i < SIZE; i++)
             {
                    printf("%d ", buffer[i]);
             }
             printf("]");
             
             cid=(cid + 1) % SIZE;   
             
             pthread_mutex_unlock(&lock);
             
             sem_post(&empty);
        
        }        
        pthread_exit(NULL);        
}

int main()
{
        int i,pcon,ccon;
    
        sem_init(&empty,0,SIZE);
        sem_init(&full,0,0);
        
        pthread_mutex_init(&lock,NULL);
        
        printf("\n Enter the number of Producers : ");
        scanf("%d",&pcon);
        printf("\n Enter the number of Consumer : ");    
        scanf("%d",&ccon);
        
        for(i=0;i<pcon;i++)
        {
                int *p;
                p = (int*)malloc(sizeof(int));
                *p = i+1;
                pthread_create(&producer,NULL,producing,(void *)p);
        }
        
         for(i=0;i<ccon;i++)
        {
                int *p;
                p = (int*)malloc(sizeof(int));
                *p = i+1;
                pthread_create(&consumer,NULL,consuming,(void *)p);
        }
        
        for(i=0;i<pcon;i++)
                pthread_join(producer,NULL);
        for(i=0;i<ccon;i++)
                pthread_join(consumer,NULL); 
        
        
        return 0;
}

