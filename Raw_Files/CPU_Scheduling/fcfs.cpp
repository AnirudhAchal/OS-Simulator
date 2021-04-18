//
//  main.cpp
//  FCFS
//
//Apurba Ranjan Mohapatra
//Roll No 191CS109

//Aaidan Ram
//Roll No :191CS101

#include <iostream>
using namespace std;

class Process
{
    private:
    int p_id;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnarround_time;
    int waiting_time;
    void scheduling(class Process *p,int size);
public:
    void initialization();

};
void Process :: scheduling(class Process *p,int size)
{
    int i,j;
    int total_turn_arround_time,total_waiting_time;
    total_waiting_time=total_turn_arround_time=0;
    class Process key; //creating key for swapping
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
    cout<<"\nProcess_ID\tArrival Time\tBurst Time\tTurn Arround Time\tWaiting Time\n";
    for(i=0;i<size;i++)
    {
        //printing the outputs
        cout<<"\t"<<p[i].p_id<<"\t\t\t"<<p[i].arrival_time<<"\t\t\t\t"<<p[i].burst_time<<"\t\t\t"<<p[i].turnarround_time<<"\t\t\t\t"<<p[i].waiting_time<<endl;
    }
    cout<<"Average Waiting Time :\t"<<avg_wt;
    cout<<"\nAverage TurnArround Time :\t"<<avg_tat<<endl;
    return;
}
void Process::initialization()
{
    int size; //taking input of number of processes
    cout<<"enter the number of cpu process : \t";
    cin>>size;
    class Process p[size]; //creating a array of number of process size
    for(int i=0;i<size;i++)
    {
        //taking input of arrival time and burst time of processes
        p[i].p_id=i+1;
        cout<<"enter the arrival time and burst time for process :\t"<<p[i].p_id<<endl;
        cin>>p[i].arrival_time>>p[i].burst_time;
    }
    scheduling(p, size); //calling our schedulling function
    return;
}
int main(int argc, const char * argv[]) {
    Process p;
    p.initialization(); //calling initialization function
    return 0;
}


