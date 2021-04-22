//Longest Job First Scheduling
#include<iostream>
#include<stdio.h>

using namespace std;


void ljf()
{
    cout << "\nRunning CPU Scheduling LJF\n";
    struct proc{
      int id,at,bt,ct,wt,tat,completed;
    };
  struct proc p[100];
  int n;
  int curr_time=0;
  int avg_tat=0,avg_wt=0,comp=0;
  cout<<"\nEnter the number of process: ";
  cin>>n;


  for(int i=0;i<n;i++)
  {
    cout<<"\nEnter arrival time of P"<<i+1<<": ";
      p[i].id=i+1;
    cin>>p[i].at;
    cout<<"\nEnter burst time of P"<<i+1<<": ";
    cin>>p[i].bt;
    p[i].completed=0;
  }

    //Sorting according to arrival times
    int i, j, min;
    struct proc temp;
    for (i=0; i<n; i++){
        min = i;
        for(j=i+1; j<n ;j++){
            if(p[min].at>p[j].at)
                min = j;
        }
        temp = p[i];
        p[i] = p[min];
        p[min] = temp;
    }
    
    //scheduling part
    
    int t,max_bt=-1,idx,c_count=0;
    t=p[0].at;
    while(c_count<n)
    {
        max_bt=-1;
        i=0;
        while(p[i].at<=t && i<n)        //check if process has arrived
        {
            if(p[i].completed!=1 && p[i].bt>max_bt)
            {
                idx=i;
            }
            i++;
        }
        p[idx].ct=t+p[idx].bt;      //completiton time of the process
        p[idx].tat= p[idx].ct-p[idx].at; //TAT
        avg_tat+=p[idx].tat;
        p[idx].wt=  p[idx].tat - p[idx].bt;     //Waiting time
        avg_wt+=p[idx].wt;
        t=t+p[idx].bt;               //time is updated
        p[idx].completed=1;
        c_count++;              //completed process count
        cout<<"\nTime here is: "<<t<<"\n";
    }
   

  cout<<"P_id\t"<<"AT\t"<<"BT\t"<<"CT\t"<<"WT\t"<<"TAT\t"<<"\n";
  for(int i=0;i<n;i++)
  {
    cout<<p[i].id<<"\t"<<p[i].at<<"\t"<<p[i].bt<<"\t"<<p[i].ct<<"\t"<<p[i].wt<<"\t"<<p[i].tat<<"\t"<<"\n";
  }

  cout<<"\nAverage waiting time is: "<<(float)avg_wt/n;
    cout<<"\nAverage turn around time is: "<<(float)avg_tat/n<<"\n";



}
