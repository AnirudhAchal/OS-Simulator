//Program to implement Bankers Algorithm
#include<iostream>
#include<stdio.h>

using namespace std;

void bankers()
{
  cout << "\nRunning Bankers Algorithm\n";
  int p_no,r_no;
  cout<<"\nEnter the number of processes: ";
  cin>>p_no;
  cout<<"\nEnter number of resources: ";
  cin>>r_no;
  cout<<"\nEnter number of each resource available :";
  int avail[r_no];
  for(int i=0;i<r_no;i++)
  {
    cout<<"\nR"<<i+1<<": ";
    cin>>avail[i];
  }
  int allocTotal[r_no];
  for(int i=0;i<r_no;i++)
  {
     allocTotal[i]=0;
  }
  int alloc[p_no][r_no],max[p_no][r_no],need[p_no][r_no];
  //taking inputs for allocated rsources and max requirement of resources and
  //and calculating need matrix respectively
  for(int i=0;i<p_no;i++)
  {
    for(int j=0;j<r_no;j++)
    {
      cout<<"\nProcess "<<i+1<<" resource "<<j+1<<" : \n";
      cout<<"\nEnter allocation: ";
      cin>>alloc[i][j];
      allocTotal[j]+=alloc[i][j];
      cout<<"\nEnter max requirement: ";
      cin>>max[i][j];
      need[i][j]=max[i][j]-alloc[i][j];
    }
  }

  int UpdAvail[r_no]; //Available resources after allocation
  for(int i=0;i<r_no;i++)
  {
    UpdAvail[i]=avail[i]-allocTotal[i];
  }

  int flag,count=0,fl[p_no];
  for(int i=0;i<p_no;i++)
  {
    fl[i]=0;  // flag per process is set to 0 to check if that proecss has
              // finished or not
  }

  cout<<"\nAllocated resources are: \n";
  cout<<"\t";
  for(int i=0;i<r_no;i++)
  {
    cout<<"R"<<i+1<<"\t";
  }
  cout<<"\n";
  for(int i=0;i<p_no;i++)
  {
    cout<<"P"<<i+1<<"\t";
    for(int j=0;j<r_no;j++)
    {
      cout<<alloc[i][j]<<"\t";
    }
    cout<<"\n";
  }

  cout<<"\nNeeded resources are: \n";
  cout<<"\t";
  for(int i=0;i<r_no;i++)
  {
    cout<<"R"<<i+1<<"\t";
  }
  cout<<"\n";
  for(int i=0;i<p_no;i++)
  {
    cout<<"P"<<i+1<<"\t";
    for(int j=0;j<r_no;j++)
    {
      cout<<max[i][j]<<"\t";
    }
    cout<<"\n";
  }
  cout<<"The safe order to execute the processes to avoid deadlock is: ";
  while(count<p_no)   // Repeatedly check all process till all have been
  {                    //executed
    for(int i=0;i<p_no;i++)
    {
      if(fl[i]==1)
      {
        continue;
      }
      else if(fl[i]==0)
      {flag=0;
        for(int j=0;j<r_no;j++)
        {
          if(need[i][j]>UpdAvail[j]) //If resource can't be allocatd move to next process.
          {
            flag=1;
            break;
          }
        }

      }
      if(flag==0)
      {
        for(int j=0;j<r_no;j++)
        {
          UpdAvail[j]+=alloc[i][j]; //If resource can be allocated, finish
                                   //process and update available resources.
        }
        fl[i]=1; // Finished process flag set to 1 to not call it again
        count++; // Finished process count is incremented.
        cout<<" P"<<i+1;
      }
    }
  }
  cout<<"\n";

}
