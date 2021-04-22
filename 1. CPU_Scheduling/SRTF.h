//Shortest Remaining time first Job scheduling
#include<iostream>
#include<stdio.h>

using namespace std;

void srtf()
{
    cout << "\nRunning CPU Scheduling SRTF\n\n";
    
    struct proc{
      int id,at,bt,bt_r,ct,wt,tat,completed;
    };
  struct proc p[100];
  int n;
  int curr_time=0;
  int avg_tat=0,avg_wt=0,comp=0;
  cout<<"Enter the number of process: ";
  cin>>n;


  for(int i=0;i<n;i++)
  {
      cout<<"\nEnter process ID: ";
      cin>>p[i].id;
      cout<<"\nEnter arrival time of P"<<p[i].id<<": ";
    cin>>p[i].at;
      cout<<"\nEnter burst time of P"<<p[i].id<<": ";
    cin>>p[i].bt;
    p[i].bt_r=p[i].bt;
    p[i].completed=0;
  }

  while(comp != n)
  {
    int min_bt=10000,id=-1;
    for(int i=0;i<n;i++)
    {
      if(p[i].at <= curr_time && p[i].completed==0)
      {
        if(p[i].bt_r < min_bt)
        {
          min_bt=p[i].bt_r;
          id=i;
        }
        if(p[i].bt_r==min_bt && p[i].at<p[id].at)
        {
          min_bt=p[i].bt_r;
          id=i;
        }
      }
    }

    if(id!=-1)
    {
    p[id].bt_r=p[id].bt_r-1;
    curr_time++;


    if(p[id].bt_r == 0)
    {
      p[id].completed=1;
      p[id].ct=curr_time;
      p[id].tat=p[id].ct-p[id].at;
      p[id].wt=p[id].tat-p[id].bt;
      comp++;
      avg_tat+=p[id].tat;
      avg_wt+=p[id].wt;
    }
    
  }
    else{
        curr_time++;
    }


  }

  cout<<"P_id\t"<<"AT\t"<<"BT\t"<<"CT\t"<<"WT\t"<<"TAT\t"<<"\n";
  for(int i=0;i<n;i++)
  {
    cout<<p[i].id<<"\t"<<p[i].at<<"\t"<<p[i].bt<<"\t"<<p[i].ct<<"\t"<<p[i].wt<<"\t"<<p[i].tat<<"\t"<<"\n";
  }

  cout<<"\nAverage waiting time is: "<<(float)avg_wt/n;
  cout<<"\nAverage turn around time is: "<<(float)avg_tat/n;



}
