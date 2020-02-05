//=================================================================================
// Name        : A3 SL-V DAA Optimal Storage
// Author      : Ayan Gadpal 33308
// Version     : 2.0
// Date        : 05 Feb 2020
// Description : Use Greedy Approach to optimal storage on tape
//=================================================================================
#include <iostream>
#include <bits/stdc++.h>
#define line() (cout<<"\n================================")
using namespace std;


struct Disk{
    int limit,load,top;
    int *Tape;

    Disk(){
        top = load = 0;
    }

    float display()
    {
        for(int i=0;i<top;i++)
            cout<<" "<<Tape[i];
        cout<<"  | Storage Used :  "<<load<<"  Retrival time : "<<(float)load/top;
        return (float)load/top;
    }

    void AssignMemory(int limit,int elementNumber)
    {
        this->limit = limit;
        Tape = new int[elementNumber];
    }
    bool push(int element)
    {
        // Check for Tape Overflow
        limit -= element;
        if(limit<0)
            return false;

        // Add Element on the tape
        Tape[top] = element;
        load+=element;
        top++;
        
        return true;
    }
};
class Storage{
    private:
        int n,m,tapes;
        int *jobList;
        struct Disk *T;
    public:
        Storage()
        {
            cout<<"\nEnter The number of jobs : ";
            cin>>n;
            line();

            cout<<"\nEnter The size of each job";
            jobList = new int[n];
            line();

            for(int i = 0;i<n;i++)
            {
                cout<<"\nSize of JOB NO."<<i+1<<" : ";
                cin>>jobList[i];
            }
            line();

            cout<<"\nEnter the number of Tape : ";
            cin>>tapes;
            line();

            cout<<"\nEnter the size of Tape : ";
            cin>>m;
            line();
            
            // Assigning Memory to the Tapes
            T = new Disk[tapes];
            for(int i=0;i<tapes;i++)
                T[i].AssignMemory(m,(n/tapes)+1);

            // Merge Sort
            mergeSort(jobList,0,n-1);
        }
        void displayJobs()
        {
            for(int i=0;i<n;i++)
                cout<<"\n"<<i+1<<") "<<jobList[i];   
        }

        void displayTapes()
        {
            float totalAvg = 0;
            for(int i=0;i<tapes;i++)
                line(),cout<<"\nTape "<<i+1<<endl,totalAvg += T[i].display();  

            cout<<"\nTotal Average is "<<totalAvg/tapes<<endl; 
            line();
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
            for(int i = 0;i<n;i++)
            {
                int index = i % tapes;
                if(!(T[index].push(jobList[i])))
                    cout<<"\nOverload ! Tape "<<index+1;     
            }

        }

};

int main()
{
    Storage HDD;
    HDD.placeOnTape();
    HDD.displayTapes();
    return 0;
}
