/*
Name        : Process control System calls
Auther      : Ayan Naresh Gadpal
Copyright   : GNU public Library
Description : Employing dynamic multithreading approach for matrix multiplication
Date        : Fri Oct 19 2019 , 12:48 AM
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// ReQ
#include <sys/types.h>
#include <pthread.h>

// compile it with  gcc multithreading.c -lpthread

// GLOBAL MATRIX AND THEIR ROWS AND COL
int *m1,*m2,*m3;
int r1,c1,r2,c2;

// To pass to thread function 
struct param
{
        int i,j;
};


// Simple Matrix Input
int* input(int *row,int *col)
{
        int *matrix,i,j;
        printf("\nEnter the row and column for Matrix\nRow : ");
        scanf("%d",row);
        printf("\ncol :");
        scanf("%d",col);
        
        matrix = malloc(sizeof(int)*(*row)*(*col));
        
        for(i=0;i<*row;i++)
                for(j=0;j<*col;j++)
                       scanf("%d",(matrix+(i*(*col))+j));
        
        return matrix;
}

// Simple Matrix Output
void display(int *matrix,int row,int col)
{
        int i,j;
        for(i=0;i<row;i++)
        {
                for(j=0;j<col;j++)
                {
                        printf("%d ",*(matrix+(i*col)+j));
                }
           printf("\n");
        }  

}

// THREAD FUNCTION 
void *multi(void *v)
{
        // PARAM will tell the thread the position of the matrix it need to calculate
        struct param *p;
        p = (struct param *) v;
        
        // 'p->i' is row position and 'p->j' is col position
        printf("\ni=%d j=%d\n",p->i,p->j); 
        int k;
        
        // Store the result of multiplication
        int result = 0;
        
        for (k=0;k<c1;k++)
                result += *(m1+p->i*c1+k) * *(m2+k*c2+p->j); // FORMULA : PositionValue += M1[p->i][k] x M2[k][p->j] 
      
        // Send the result back;
        pthread_exit((void *)result);        
}

int main()
{
        int i,j;
       
        pthread_t *thread_id;
        
        // Take input for 1st matrix
        m1 = input(&r1,&c1);
        
        // Take input for 2nd matrix
        m2 = input(&r2,&c2);
        
        // Validation    
        if(c1 != r2)
        {
                printf("[ ERROR ] : Row Column Unmached ! Operation Aborted...\n");
                return (0);
        }
        
        // Dyanamic thread id creation
        thread_id = (pthread_t *) malloc(r1*c2*sizeof(pthread_t));
        
        // Resultant Matrix Memory Allocation
        m3 = (int *)malloc(sizeof(int)*(r1)*(c2));
      
        for (i=0;i<r1;i++) // ROW 1
                for (j=0;j<c2;j++) // COL 2
                     {
                              // INTIALIZE NEW MEMORY to param FOR EACH THREAD
                              struct param *p;
                              p = (struct param *) malloc(sizeof(struct param)); 
                              
                              // ASSIGN POSITION
                              p->i = i; 
                              p->j = j;
     
                              // CREATE THREAD 
                              pthread_create(thread_id+(i*c2)+j, NULL, multi, (void *)p);    
                    }
       // TO ACCEPT ANSWER
       void *t = NULL;
       
       for (i=0;i<r1;i++)
                for (j=0;j<c2;j++)
                {          
                      // WAIT FOR THREAD TO COMPLETE THERE TASK AND ACCEPT ANSWER
                      pthread_join(*(thread_id+(i*c2)+j),&t);
                      *(m3+(i*c2)+j) = (int)t;
                }
                
       // DISPLAY RESULT
       display(m3,r1,c2);
       
       
        return (0);
}
