/*

Preemptive Priority CPU Scheduling
*/
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string.h>
#include <vector>
using namespace std;

class priority_preemp{
   //structure for process
    struct process {
    int pid;     //process id
    int AT;      //arrival time of process
    int BT;      //burst time of process
    int priority;//priority of process (high number ==> high priority)
    int ST;      //starting time of process
    int CT;      //completion time of process
    int TT;      //turnaround time of process
    int WT;      //waiting time of process
};
    public:
         void solve();
};

//function to facilitate non-preemptive scheduling algorithm
void priority_preemp:: solve()
{
    int n;
    struct process p[100];           //maximum number of process is 100
    float avg_TT;                    //average turnaround time for each process
    float avg_WT;                    //average waiting time time for each process

    int total_TT = 0;
    int total_WT = 0;

    int burst_remaining[100];        //remaining burst time of processes
    int is_completed[100];           //array to check if the process is completed(==1) or not(==0)
    memset(is_completed,0,sizeof(is_completed));

    cout << setprecision(2) << fixed;
    //taking input for number of processes
    cout<<"Enter the number of processes: ";
    cin>>n;
    cout<<"\n";
    //taking input for number of processes
    //taking input for each process about arrival time,burst time and priority
    for(int i = 0; i < n; i++) {
        cout<<"Enter arrival time of process "<<i+1<<" : ";
        cin>>p[i].AT;
        cout<<"Enter burst time of process "<<i+1<<" : ";
        cin>>p[i].BT;
        cout<<"Enter priority of the process "<<i+1<<" : ";
        cin>>p[i].priority;
        p[i].pid = i+1;
        burst_remaining[i] = p[i].BT;
        cout<<endl;
    }

    int current_time = 0;
    int completed = 0;       //to count the total number of processes

    vector<int> order;
    //calculating the next process which should be executed according to priority
    while(completed != n) {

        int index = -1;
        int max = -1;
        for(int i = 0; i < n; i++) {
            if(p[i].AT <= current_time && is_completed[i] == 0) {
                if(p[i].priority > max) {
                    max = p[i].priority;
                    index = i;
                }
                //if priority is same then process is chosen according to arrival time
                if(p[i].priority == max) {
                    if(p[i].AT < p[index].AT) {
                        max = p[i].priority;
                        index = i;
                    }
                }
            }
        }

        //if a process is found for execution
        if(index != -1) {
            order.push_back(index);
            if(burst_remaining[index] == p[index].BT) {
                p[index].ST = current_time;
            }
            burst_remaining[index] -= 1; //decrementing burst time of current process
            current_time++; //moving forward 1 unit at a time

            if(burst_remaining[index] == 0) {
                p[index].CT = current_time;                   // completion time = current time
                p[index].TT = p[index].CT - p[index].AT;       // turnaround time = completion time - arrival time
                p[index].WT = p[index].TT - p[index].BT;      // waiting time = turnaround time - burst time

            total_TT += p[index].TT;
            total_WT += p[index].WT;

                is_completed[index] = 1;                //marking the process as complete
                completed++;                           //increasing the completed count
            }
        }
        //if no process is available for execution
        else {
             order.push_back(-1);
             current_time++;
        }
    }

//Printing Gantt Chart
    cout << "\nGantt Chart: " << endl;
    cout << "-----------\n" << endl;
    cout<<"|";
    int i=0;
    if(order[i]!=-1) cout<<"\tProcess "<<order[i]<<"\t|";
    else cout<<"\tCPU IDLE\t|";
    i++;
    while(i<order.size())
    {
      if(order[i]!=order[i-1])
      {
        if(order[i]!=-1)
        cout<<"\tProcess "<<order[i]+1<<"\t|";
        else cout<<"\tCPU IDLE\t|";
      }
      i++;
    }
    cout<<"\n";
    i=0;
    cout<<"0\t\t\t";
    i++;
    while(i<order.size())
    {
      if(order[i]!=order[i-1])cout<<i<<"\t\t\t";
      i++;
    }
    cout<<i;


    //calculating final results
    avg_TT = (float) total_TT / n;
    avg_WT = (float) total_WT / n;

    cout<<endl<<endl;

    //printing the final result
    // cout << "\nFinal timing results: " << endl;
    // cout << "--------------------- \n" << endl;
    // cout<<"#P\t"<<"AT\t"<<"BT\t"<<"PRI\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"\n"<<endl;

    // for(int i = 0; i < n; i++) {
    //     cout<<p[i].pid<<"\t"<<p[i].AT<<"\t"<<p[i].BT<<"\t"<<p[i].priority<<"\t"<<p[i].ST<<"\t"<<p[i].CT<<"\t"<<p[i].TT<<"\t"<<p[i].WT<<"\t"<<"\n"<<endl;
    // }
    // cout<<"\nAverage Turnaround Time = "<<avg_TT<<endl;
    // cout<<"Average Waiting Time = "<<avg_WT<<endl;

    cout << "\nFinal timing results: " << endl;
    cout << "--------------------- \n" << endl;
    cout << setw(13) << left << "Process No" << setw(10) << left << "AT" << setw(10) << left << "BT" << setw(10) << left << "CT" << setw(10) << left << "TAT" << setw(10) << left << "WT" << endl;
    cout << setw(13) << left << "----------" << setw(10) << left << "--" << setw(10) << left << "--" << setw(10) << left << "--" << setw(10) << left << "---" << setw(10) << left << "--" << endl;
    for(int i=0; i<n ; i++)
    {
      cout << setw(13) << left << p[i].pid << setw(10) << left << p[i].AT << setw(10) << left << p[i].BT << setw(10) << left << p[i].CT << setw(10) << left << p[i].TT << setw(10) << left << p[i].WT << endl;
    }
    cout<<"\nAverage TurnAround Time : "<<avg_TT<<endl;
    cout<<"Average Waiting Time      : "<<avg_WT<<endl;
}
void preemptive_priority() {
    cout << "\nRunning CPU Scheduling Preemptive Priority\n\n"; 
    printf("******* Non-Preemptive Priority ********\n\n");
    priority_preemp p;
    p.solve();
    printf("\n******* DONE ********\n");
}

