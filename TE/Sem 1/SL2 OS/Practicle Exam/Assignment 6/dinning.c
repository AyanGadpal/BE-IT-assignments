/*
Name        : Deadlock Handling
Auther      : Ayan Naresh Gadpal
Copyright   : GNU public Library
Description : Dinning Philosopher 
Date        : Fri Oct 19 2019 , 1:14 PM
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 5

enum {
        THINKING,
        HUNGRY,
        EATING
}STATE[N];    

void think(int);
void eat(int);
void takefork(int);
void putfork(int);

int eatCount[N] = {0};

// Mutexs and Semaphores
pthread_mutex_t lock;
sem_t chopsticks[N];

void *philoshper(void *p)
{
        int *id;
        id = (int *)p;
        int itn = *id;
        printf("Philosopher %d\n",itn);
        STATE[itn] = THINKING;
        while(1)
        {
              think(itn);
              eat(itn);              
        }
        
        pthread_exit(NULL);
}

void think(int i)
{
        if(STATE[i] == THINKING)
        {
                printf("%d : THINKING \n",i);               
                int temp = rand()%3;
                temp = temp==0?1:temp;
                sleep(temp);
                STATE[i] = HUNGRY;
                printf("%d : **********HUNGRY \n",i);
        }
}

void eat(int i)
{
        // MONITOR
        int j;
        if(STATE[(i+1)%N]!= EATING && STATE[(i+(N-1))%N] != EATING && STATE[i] == HUNGRY)
        {
                int temp = rand()%3;
                temp = temp==0?1:temp;
                
                takefork(i);
                
                sleep(temp);
                printf("%d : ........................EATING \n",i);
                eatCount[i]++;
                pthread_mutex_lock(&lock);
                printf("\n[");
                for(j=0;j<N;j++)
                        printf("%d ",eatCount[j]);
                printf("]\n");
                pthread_mutex_unlock(&lock);
                putfork(i);
                
                STATE[i] = THINKING;
        } 
}

void takefork(int i)
{
        sem_wait(&chopsticks[i]);
        sem_wait(&chopsticks[(i+1)%N]);
}

void putfork(int i)
{
        sem_post(&chopsticks[i]);
        sem_post(&chopsticks[(i+1)%N]);
}


int main(){
        pthread_t philoshoperThread;
        int i;
        
        for(i=0;i<N;i++)
                sem_init(&chopsticks[i],0,1);
        
        for(i=0;i<N;i++)
        {
                int *p;
                p = (int *)malloc(sizeof(int));
                *p = i; 
                pthread_create(&philoshoperThread,NULL,philoshper,(void *)p);
        }
        for(i=0;i<N;i++)
                pthread_join(philoshoperThread,NULL);
       
        return 0;
}
