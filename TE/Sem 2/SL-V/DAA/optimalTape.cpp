//=================================================================================
// Name        : A3 SL-V DAA Optimal Storage
// Author      : Ayan Gadpal 33308
// Version     : 3.0
// Date        : 06 Feb 2020
// Description : Use Greedy Approach to optimal storage on tape
//=================================================================================
#include <iostream>
#include <bits/stdc++.h>

// Macro To Print a line
#define line() (cout<<"\n================================")
using namespace std;

// Disk which contain a single Tape and keep Track of it
struct Disk{
    
    // "Limit" : is the total Storage of tape
    // "Load" : Total storage used
    // "top" : Keep track of topmost empty elements
    int limit,load,top;
    
    // Tape : Storage Tape 
    int *Tape;

    // Intialize the top and load to 0
    Disk(){
        top = load = 0;
    }

    // Display the contain on the tape along with its Total Storage used and return its Avg Retrieval time
    float display()
    {
        for(int i=0;i<top;i++)
            cout<<" "<<Tape[i];
        cout<<"  | Storage Used :  "<<load<<"  Retrival time : "<<(float)load/top;
        return (float)load/top;
    }

    // Assign Total Elemets to the Tape
    // In Greedy Approach if we will need to store max of (TotalJobs/TotalTape + 1) in a Tape
    void AssignMemory(int limit,int elementNumber)
    {
        this->limit = limit;
        Tape = new int[elementNumber];
    }

    // Push the element on list
    // if tape is not overloaded then return true
    // else return flase
    bool push(int element)
    {
        // Check for Tape Overflow
        limit -= element;
        if(limit<0)
            return false;

        // Add Element on the tape
        Tape[top] = element;

        // Increase the load
        load+=element;
        
        // Point to next empty slot
        top++;
        
        return true;
    }
};


// Used For Storing the Jobs on Multiple Tapes 
 class Storage{
    private:
        // 'n' : Number of Jobs
        // 'm' : Size of Each Tape ( Cosidered to be same of all tape )
        // 'tapes' : Total number of Tapes
        int n,m,tapes;

        // JOB LIST store the jobs with their weight
        int *jobList;

        // Array of Object "Disk", Each Disk will keep track of 1 Tape
        struct Disk *T;
    public:

        // Intialize the Storage 
        Storage()
        {
            // Accept the Total Number of Jobs
            cout<<"\nEnter The number of jobs : ";
            cin>>n;
            line();

            // Accept the Size for Each job, Individually
            cout<<"\nEnter The size of each job";
            jobList = new int[n];
            line();
            for(int i = 0;i<n;i++)
            {
                cout<<"\nSize of JOB NO."<<i+1<<" : ";
                cin>>jobList[i];
            }
            line();

            // Accept the Total Number of tapes
            cout<<"\nEnter the number of Tape : ";
            cin>>tapes;
            line();

            // Accept the Size of tape
            cout<<"\nEnter the size of Tape : ";
            cin>>m;
            line();
            
            // Assigning Memory to the Tapes
            T = new Disk[tapes];
            for(int i=0;i<tapes;i++)
                T[i].AssignMemory(m,(n/tapes)+1);

            // Merge Sort the Joblist in Ascending order
            mergeSort(jobList,0,n-1);
        }

        // Display the JobList
        void displayJobs()
        {
            for(int i=0;i<n;i++)
                cout<<"\n"<<i+1<<") "<<jobList[i];   
        }

        // Display the Contain of all tapes along with total Average Retrival time
        void displayTapes()
        {
            float totalAvg = 0;
            
            // Contain of all Tapes
            for(int i=0;i<tapes;i++)
                line(),cout<<"\nTape "<<i+1<<endl,totalAvg += T[i].display();  

            // Total Avg Time
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

// Driver Code
int main()
{
    // Create an Storage Intance, 
    Storage HDD;

    // Call the Sub modules
    HDD.placeOnTape();
    HDD.displayTapes();
    return 0;
}

