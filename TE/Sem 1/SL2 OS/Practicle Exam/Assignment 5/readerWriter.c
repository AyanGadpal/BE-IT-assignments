/*
Name        : Process Synchronazation
Auther      : Ayan Naresh Gadpal
Copyright   : GNU public Library
Description : Reader Writer 
Date        : Fri Oct 19 2019 , 11:36 AM
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>

pthread_mutex_t lock,rwlock;

int readcount=0;
int data =0;

// Print a Line For Output Formatting
void line()
{
    printf("\n================================================\n");
}

void *reading(void *p)
{
        int *id;
        id = (int*)p;
        printf("READER %d\n",*id);
        while(1){
                int temp = rand() % 3;
                temp = temp == 0 ? 2 : temp;
                sleep(temp);
                
                pthread_mutex_lock(&lock);
                        readcount++;
                        if(readcount == 1) // FIRST READER LOCKS
                        {
                                 printf("%d LOCKED RWLOCK<<<<<<<<<<<<<\n",*id);                            
                                pthread_mutex_lock(&rwlock);
                        }
                pthread_mutex_unlock(&lock);
                
                // READING START
                sleep(temp);
                line();
                temp = data;
                printf("%d) READ %d\n",*id,temp);
                // READING END
                
                pthread_mutex_lock(&lock);
                        readcount--;
                        if(readcount == 0) // LAST READER UNLOCKS
                        {
                                printf("%d>>>>>>>>>>>>>>UNLOCKED RWLOCK\n",*id);  
                                pthread_mutex_unlock(&rwlock);
                        }
                pthread_mutex_unlock(&lock);              
        }
        
        pthread_exit(NULL);
}


void *writing(void *p)
{
        int *id;
        id = (int*)p;
        printf("WRITER %d\n",*id);
        while(1)
        {
                int temp = rand() % 3;
                temp = temp == 0 ? 2 : temp;
                sleep(temp);
                pthread_mutex_lock(&rwlock);
                        // WRITING DATA
                        sleep(temp);
                        line();
                        data = temp;
                        printf("<<<<<<<<<<<<<<<%d ) WRITING %d\n",*id,data);
                
                pthread_mutex_unlock(&rwlock);
                
        }
        pthread_exit(NULL);
}

int main()
{
        int i,readers,writers;
        pthread_t reader,writer;
        
        pthread_mutex_init(&lock,NULL);
        pthread_mutex_init(&rwlock,NULL);
        
        printf("\nEnter the number of Readers : ");
        scanf("%d",&readers);
        printf("\nEnter the number of Writers : ");
        scanf("%d",&writers);
        
        for(i=0;i<readers;i++)
        {
                int *p;
                p = (int*)malloc(sizeof(int));
                *p = i+1;
                pthread_create(&reader,NULL,reading,(void *)p);       
        }
        
        for(i=0;i<writers;i++)
        {
                int *p;
                p = (int*)malloc(sizeof(int));
                *p = i+1;
                pthread_create(&writer,NULL,writing,(void *)p);       
        }
        
        for(i=0;i<readers;i++)
                pthread_join(reader,NULL);
        for(i=0;i<writers;i++)
                pthread_join(writer,NULL);
        
        return 0;
}
