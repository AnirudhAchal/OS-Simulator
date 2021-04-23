//
//  main.cpp
//  sjf
//
//

#include<iostream>
#include<bits/stdc++.h>
using namespace std;
void calc_wt_tat_SJF(int p_id[],int at[],int bt[],int wt[],int tat[],int ft[],size_t size)
{
    int remaining_time[size]; //to store remaining burst time
    for(int i=0;i<size;i++)
    {
        remaining_time[i]=bt[i]; //initialization_SJF of remaining_time
    }
    int completed=0; //no of process completed
    int t,minm;
    t=0;minm=INT_MAX;
    int shortest,finish_time; /* t= keeps record of the time
                               minm= used to find minm burst time process
                               shortest=keeps the index of shortest process
                               check= flag variable*/
    shortest=0;
    bool check=false;
    
    while(completed!=size)
    {
        for(int j=0;j<size;j++)
        {
            if((at[j]<=t) and (remaining_time[j]< minm) and remaining_time[j]>0)
            {
                minm=remaining_time[j];
                shortest=j;  /*finding shortest process and storing its credential*/
                check=true;
            }
        }
        if(check == false)
        {
            t++; //no process is there so cpu is idle
            continue;
        }
        remaining_time[shortest]--; //decreasing remaining burst time
        minm=remaining_time[shortest]; //saving minm remaining burst time
        if(minm==0)
        {
            minm= INT_MAX;
        }
        if(remaining_time[shortest] == 0)
        {
            completed++; //process completed
            check=false; //set flag into false again
            finish_time=t+1; //save finishing time
            wt[shortest]=finish_time-bt[shortest]-at[shortest]; //saving waiting time
            if(wt[shortest]<0)
            {
                wt[shortest]=0; //if waitning time is in -ve set it to 0
            }
            tat[shortest]=bt[shortest]+wt[shortest]; //calculating total turn arround time of the finished process
            ft[shortest]=finish_time; //calculating finishing time of finished proces
        }
        t++; //increasing process time
    }
    return;
}
void avg_time_SJF(size_t t,int p_id[],int at[],int bt[])
{
    int wt[t],tat[t],finish_time[t]; /* wt= waiting time array
                                        tat=total turn arround time array
                                        finish_time= to store the finish time */
    int total_wt=0,total_tat=0; //total_wt=sum of total waiting time
                                //total_tat= sum of total turn arround time
    calc_wt_tat_SJF(p_id,at,bt,wt,tat,finish_time,t); //calling calc_wt_tat_SJF function
    //printing the output
    // cout<<"process ID\t"<<"Arrival time\t"<<"Burst Time\t"<<"Waiting Time\t"<<"Finishing Time\n";
    for(int i=0;i<t;i++)
    {
        total_wt+=wt[i]; //calculating total waiting time
        total_tat+=tat[i]; //calculating total turn arround time
        //cout<<"\t"<<p_id[i]<<"\t\t\t"<<at[i]<<"\t\t\t"<<bt[i]<<"\t\t\t"<<wt[i]<<"\t\t\t"<<finish_time[i]<<endl;
    }
    cout<<endl;
    cout << "\n\nFinal timing results: " << endl;
    cout << "--------------------- \n" << endl;

    cout << setw(13) << left << "Process No" << setw(10) << left << "AT" << setw(10) << left << "BT" << setw(10) << left << "CT" << setw(10) << left << "TAT" << setw(10) << left << "WT" << endl;
    cout << setw(13) << left << "----------" << setw(10) << left << "--" << setw(10) << left << "--" << setw(10) << left << "--" << setw(10) << left << "---" << setw(10) << left << "--" << endl;

    for(int i=0; i< t ; i++)
    {
        cout << setw(13) << left << p_id[i] << setw(10) << left << at[i] << setw(10) << left << bt[i] << setw(10) << left << finish_time[i] << setw(10) << left << tat[i] << setw(10) << left << wt[i] << endl;
    }
    
    cout<<"Average TurnArround time is :\t"<< (double)total_tat/t<<endl;
    cout<<"Average Waiting time is     :\t"<< (double)total_wt/t<<endl;

    return;
}
void initialization_SJF()
{
    size_t t; //number of processes
    cout<<"Enter the number of processes :\t";
    cin>>t;
    int bt[t],at[t]; /* bt=burst time array of size t
                      at= arrival time array of size t */
    int p_id[t];//used to store process id
    for(int i=0;i<t;i++)
    {
        p_id[i]=i+1; //process number starting from 1
        cout<<"\nEnter the arrival time and burst time of process "<<p_id[i]<< " : ";
        cin>>at[i]>>bt[i]; //taking input for arrival and burst time
    }
    avg_time_SJF(t,p_id,at,bt); //calling avg_time_SJF function for calculation
    return;
}
void sjf()
{
    cout << "\nRunning CPU Scheduling SJF\n\n";
    initialization_SJF();
}
