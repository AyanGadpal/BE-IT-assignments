/*====================================================
Auther : Ayan N Gadpal K11 33308
Code : Classical Problem of Dinning philosopher     
Date : AUG 27 2019
Copyright : GNU public Library
=====================================================*/

// NOTE : PLEASE RUN IT WITH '-lpthread'

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

// Philosopher
#define N 5

// States for all Pholosoper
enum
{
    THINKING,
    EATING,
    HUNGRY
} state[N];

// Mutexs and Semaphores
pthread_mutex_t lock;
sem_t chopsticks[N];

// Thread function for philosopher
void *philosopher(void *no);

// Other functions
void takeChopstick(int i);
void putChopstick(int i);
void think(int i);
void eat(int i);

int eatCount[N]={0};
void main()
{
    int *arg, i;

    pthread_mutex_init(&lock, NULL);

    pthread_t philosopherThread;

    for (i = 0; i < N; i++)
        sem_init(&chopsticks[i], 0, 1);

    for (i = 0; i < N; i++)
    {
        arg = (int *)malloc(sizeof(int));
        *arg = i;
        pthread_create(&philosopherThread, NULL, philosopher, (void *)arg);
    }

    for (i = 0; i < N; i++)
        pthread_join(philosopherThread, NULL);
}

void *philosopher(void *arg)
{
    int i;
    i = *(int *)arg;
    printf("Philosoper %d Entered\n", i);
    while (1)
    {
        think(i);
        eat(i);
    }
}

void think(int i)
{
    if (state[i] == THINKING)
    {
        int temp = rand() % 5;
        temp = (temp == 0 ? 2 : temp);
        printf("\nPhilosopsher %d : THINKING \n", i);
        sleep(temp);
        state[i] = HUNGRY;
    }
}
void takeChopstick(int i)
{
    sem_wait(&chopsticks[i]);
    sem_wait(&chopsticks[(i+1)%N]);
}
void putChopstick(int i)
{
    sem_post(&chopsticks[i]);
    sem_post(&chopsticks[(i+1)%N]);
}
void eat(int i)
{
    int temp = rand() % 3;
    temp = temp == 0 ? 1 : temp;
    int j;
    if (state[(i + 1) % N] != EATING && state[(i + (N - 1)) % N] != EATING && state[i] == HUNGRY)
    {
        state[i] = EATING;
        printf("\n\tPhilosopsher %d is EATING", i);
        takeChopstick(i);
        sleep(temp);
        eatCount[i]++;

        printf("\n\t\tPhilosopsher %d HAS DONE EATING", i);
        putChopstick(i);
        state[i] = THINKING;

        pthread_mutex_lock(&lock);
        printf("\n========================================");
        printf("\n\nEatCount : [");
        for(j=0;j<N;j++)
        {
            printf(" %d",eatCount[j]);
        }
        printf("]");
        printf("\n========================================\n");
        pthread_mutex_unlock(&lock);
    }
}
