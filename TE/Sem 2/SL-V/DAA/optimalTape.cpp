//=================================================================================
// Name        : A3 SL-V DAA Optimal Storage
// Author      : Ayan Gadpal 33308
// Version     : 1.0
// Date        : 05 Feb 2020
// Description : Use Greedy Approach to optimal storage on tape
//=================================================================================
#include <iostream>
#include <bits/stdc++.h>

using namespace std;
struct Disk{
    int limit;
    int count;
    int *Tape;
    Disk(int limit)
    {
        this->limit = limit;
        Tape = new int[limit];

    }
    // <<<<<<<<<<<<<<<<<<<< CODIND HERE
};
class Storage{
    private:
        int n,m,tapes;
        int *jobList;
        int *Tape;
    public:
        Storage()
        {
            cout<<"\nEnter The number of jobs";
            cin>>n;
            cout<<"\nEnter The size of each job";
            jobList = new int[n];
            for(int i = 0;i<n;i++)
            {
                cout<<"\nSize of JOB NO."<<i+1<<" : ";
                cin>>jobList[i];
            }
            cout<<"\nEnter the number of Tape";
            cin>>tapes;
            cout<<"\nEnter the size of Tape";
            cin>>m;
            mergeSort(jobList,0,n-1);
        }
        void displayJobs()
        {
            for(int i=0;i<n;i++)
                cout<<"\n"<<i+1<<") "<<jobList[i];   
        }

        void merge(int arr[], int l, int m, int r)
        {
            // Length of both side
            int n1 = m - l + 1;
            int n2 = r - m;

            int L[n1], R[n2];

            int i, j, k;

            // Copy Left
            for (i = 0; i < n1; i++)
                L[i] = arr[l + i];

            // Copy Right
            for (j = 0; j < n2; j++)
                R[j] = arr[m + 1 + j];

            i = j = 0;
            k = l;

            // Copy Data from left and right in Ascending order in Original
            while (i < n1 && j < n2)
            {
                if (L[i] <= R[j])
                    arr[k] = L[i], i++;
                else
                    arr[k] = R[j], j++;

                k++;
            }

            // Copy Rest from Left
            while (i < n1)
                arr[k] = L[i], k++, i++;

            // Copy Rest from Right
            while (j < n2)
                arr[k] = R[j], k++, j++;
        }

        // Array ,left , right
        void mergeSort(int A[], int l, int r)
        {
            if (l < r)
            {
                int m = l + (r - l) / 2; // Middle

                // Left , Right
                mergeSort(A, l, m), mergeSort(A, m + 1, r);

                // Merging
                merge(A, l, m, r);
            }
        }

        void placeOnTape()
        {
            int limit1,limit2,limit3;
            limit1 = limit2 = limit3 = m;
            
            Tape1 = new int[m];
            Tape2 = new int[m];
            Tape3 = new int[m];
            
            for(int j=0,i = 0;i<n;i+=3,j++)
            {
                Tape1[j] = jobList[i];
                limit1 -= jobList[i];
                
                Tape2[j] = jobList[i+1];
                limit2 -= jobList[i+1];
                
                Tape3[j] = jobList[i+2];
                limit3 -= jobList[i+2];
            }

            if(limit1 < 0 || limit2 < 0 || limit3 < 0)
                cout<<"\n [ ERROR ] : OVERFLOWED";

            cout<<"\nTape 1 :";
            for(int j=0,i = 0;i<n;i+=3,j++)
                cout<<"  "<<Tape1[j];
            
            cout<<"\nTape 2 :";
            for(int j=0,i = 0;i<n;i+=3,j++)
                cout<<"  "<<Tape2[j];

            cout<<"\nTape 3 :";
            for(int j=0,i = 0;i<n;i+=3,j++)
                cout<<"  "<<Tape3[j];
            
            cout<<"\n";

        }

};

int main()
{
    Storage HDD;
    HDD.displayJobs();
    HDD.placeOnTape();
    return 0;
}
