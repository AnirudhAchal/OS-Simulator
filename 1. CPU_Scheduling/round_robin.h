//
//  main.cpp
//  round  robin
//
//  Created by Apurba Ranjan Mohapatra on 18/04/21.
//
//round robin scheduling algorithm in C++
#include <bits/stdc++.h>
using namespace std;
class process_rr
{
private:
    int pid;
    int arrival_time;
    int burst_time;
    int temp;
    void scheduling(int n,class process_rr *p,int pro,int qt);
public:
    void initialization();
};
void process_rr::scheduling(int n,class process_rr *p,int pro,int qt)
{
        //sorting the array according to arrival time
        int i,j,k,count,sum,wt,tat;
        count=0;wt=tat=0;
        struct process_rr key;
        for(j = 1; j < n; j++) {        //Sorting the structure
            key = p[j];
            k = j - 1;
            while (k >= 0 && p[k].arrival_time > key.arrival_time) {
                p[k + 1] = p[k];
                k = k - 1;
            }
            p[k + 1]= key;
        }
    cout<<"\nProcessID\tArrivalTime\tBurstTime\tTurnAroundTime\t\tWaitingTime\n";
    for(sum=p[0].arrival_time, i = 0; pro!=0;)
        {
            if(p[i].temp <= qt && p[i].temp > 0) //comparing burst time with time quantum
            {
                sum = sum + p[i].temp;
                p[i].temp = 0;
                count=1;
            }
            else if(p[i].temp > 0)
            {
                p[i].temp = p[i].temp - qt;
                sum = sum + qt;
            }
            if(p[i].temp==0 && count==1)
            {
                pro--; //decreasing the process_rr
                int wt_ans=sum-p[i].arrival_time-p[i].burst_time;
                cout<<"\t"<< p[i].pid<<"\t\t"<<p[i].arrival_time<<"\t\t"<<p[i].burst_time<<"\t\t"<<sum-p[i].arrival_time<<"\t\t"<<wt_ans<<endl; //printing the output
                wt = wt+sum-p[i].arrival_time-p[i].burst_time; //calculating total wt
                tat = tat+sum-p[i].arrival_time; //calculating total turn arround time
                count =0;
            }
            if(i==n-1)
            {
                i=0;  //checking one full loop condition and setting pointer to 0
            }
            else if(p[i+1].arrival_time<=sum)
            {
                i++;
            }
            else
            {
                i=0;
            }
        }
    // finding the average waiting time and Turn Around time
    float avg_wt = (float) wt/n;
    float avg_tat = (float) tat/n;
    cout<<"\nAverage Turn Around Time: \t"<< avg_tat;
    cout<<"\nAverage Waiting Time: \t"<<avg_wt<<endl;
    return;
}
void process_rr::initialization()
{
    //taking input of number of process_rres
    int i,n,pro,qt;
    cout<<"Enter the number of process_rres for roundrobin scheduling : ";
    cin>>n;
    struct process_rr p[n];
    pro=n;
    for(i=0; i<n; i++)   //taking input of arrival and burst time
    {
        cout<<"Enter arrival time And burst time of process_rr "<< i+1<<" : ";
        cin>>p[i].arrival_time>>p[i].burst_time;
        p[i].temp = p[i].burst_time;
        p[i].pid = i+1;
    }
    cout<<endl;
    cout<<"Enter the Time Quantum for the process_rr : ";          //input of time quantum
    cin>>qt;
    scheduling(n,p,pro,qt); //calling our scheduling function
    return;
}
void rr()
{

    cout << "\nRunning CPU Scheduling Round Robin\n\n";
    process_rr P;
    P.initialization(); //calling our initialization function
}
