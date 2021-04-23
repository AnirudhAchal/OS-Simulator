//
//  main.cpp
//  FCFS
//

#include <iostream>
#include<iomanip>
using namespace std;

class Process_fcfs
{
    private:
    int p_id;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnarround_time;
    int waiting_time;
    void scheduling(class Process_fcfs *p,int size);
public:
    void initialization();

};
void Process_fcfs :: scheduling(class Process_fcfs *p,int size)
{
    int i,j;
    int total_turn_arround_time,total_waiting_time;
    total_waiting_time=total_turn_arround_time=0;
    class Process_fcfs key; //creating key for swapping
    //sorting all processes according to their arrival time
    for(i=1;i<size;i++)
    {
        key=p[i];
        j=i-1;
        while(j>=0 and p[j].arrival_time>key.arrival_time)
        {
            p[j+1]=p[j];
            j--;
        }
        p[j+1]=key;
    }
    
    for(i=0;i<size;i++)
    {
        //running the selected process according to sorted array
        p[i].start_time = (i==0) ? p[i].arrival_time : ((p[i-1].completion_time>p[i].arrival_time) ? p[i-1].completion_time : p[i].arrival_time);
        p[i].completion_time=p[i].start_time+p[i].burst_time; //calculating completion time
        p[i].turnarround_time=p[i].completion_time-p[i].arrival_time; //calculating turnarround time
        p[i].waiting_time=p[i].turnarround_time-p[i].burst_time; //calculating waiting time
        total_turn_arround_time += p[i].turnarround_time; //calculating total turn arround time
        total_waiting_time += p[i].waiting_time; //calculating total waiting time
    }
    float avg_tat= float(float(total_turn_arround_time)/size); //calculation of average turn arround time
    float avg_wt= float(float(total_waiting_time)/size); //calculation of average waiting time
    cout << "\n\nFinal timing results: " << endl;
    cout << "--------------------- \n" << endl;

    cout << setw(13) << left << "Process No" << setw(10) << left << "AT" << setw(10) << left << "BT" << setw(10) << left << "CT" << setw(10) << left << "TAT" << setw(10) << left << "WT" << endl;
    cout << setw(13) << left << "----------" << setw(10) << left << "--" << setw(10) << left << "--" << setw(10) << left << "--" << setw(10) << left << "---" << setw(10) << left << "--" << endl;

    for(int i=0; i<size ; i++)
    {
        cout << setw(13) << left << p[i].p_id << setw(10) << left << p[i].arrival_time << setw(10) << left << p[i].burst_time << setw(10) << left << p[i].completion_time << setw(10) << left << p[i].turnarround_time << setw(10) << left << p[i].waiting_time << endl;
    }

    cout<<"\nAverage TurnArround Time : "<<avg_tat;
    cout<<"\nAverage Waiting Time     : "<<avg_wt << endl;
    return;
}
void Process_fcfs::initialization()
{
    int size; //taking input of number of processes
    cout<<"Enter the number of processes : ";
    cin>>size;
    class Process_fcfs p[size]; //creating a array of number of process size
    for(int i=0;i<size;i++)
    {
        //taking input of arrival time and burst time of processes
        p[i].p_id=i+1;
        cout<<"\nEnter the arrival time for process "<< p[i].p_id << " : ";
        cin>>p[i].arrival_time;
        cout<<"Enter the burst time for process "<< p[i].p_id << " : ";
        cin>>p[i].burst_time;
    }
    scheduling(p, size); //calling our schedulling function
    return;
}
void fcfs_cpu() {
    cout << "\nRunning CPU Scheduling FCFS\n\n";
    printf("******* FCFS ********\n\n");
    Process_fcfs p;
    p.initialization(); //calling initialization function
    printf("\n******* DONE ********\n");
}


