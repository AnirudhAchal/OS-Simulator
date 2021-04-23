// CPU Scheduling : HRRN

#include<iostream>
#include<stdlib.h>
#include<iomanip>

using namespace std;

//stores information about eaxh process
struct Process{         
    int at;            //arrival time
    int bt;            //burst time
    int ct;            //completion time
    int tat;           //turn around time
    int wt;            //waiting time
    int no;            //process number
    int st;            //start time
    float rr;          //response ratio
};


void merge(struct Process *p,struct Process *l,struct Process *r,int lc,int rc) //merge two sorted arrays
{
    int i,j,k;
    i = j = k =0;
    while(j<lc&&k<rc)
    {
        if(l[j].at < r[k].at)
            p[i++] = l[j++];
        else
            p[i++] = r[k++];
    }
    while(j<lc)
        p[i++] = l[j++];
    while(k<rc)
        p[i++] = r[k++];
}

void sort_at(struct Process *p, int n)   //merge processes based on arrival time
{
    struct Process *l, *r;
    int i,j,mid;
    if(n<2)
        return;
    i = j = 0;
    mid = n/2;
    l = (struct Process*)malloc(mid*sizeof(struct Process));
    r = (struct Process*)malloc((n-mid)*sizeof(struct Process));  
    while(i<mid)
    {
        l[j++] = p[i++];
    }
    j = 0;
    while(i<n)
    {
        r[j++] = p[i++];
    }
    sort_at(l,mid);
    sort_at(r,n-mid);
    merge(p,l,r,mid,n-mid);
    free(l);
    free(r);
}

void print_output(Process *p, int n)        //prints Gantt chart
{
    cout << "\nGantt Chart: " << endl;
    cout << "-----------\n" << endl;
    cout << " |";
    for(int i=0; i < n ;i++)
    {
        if(i==0 && p[i].at > 0)
        {
            cout << setw(10) << left << " Idle CPU" << setw(4) << left << " " <<" | ";
            cout << setw(10) << left << "  Process" << setw(4) << left <<p[i].no << " | ";
        }
        else if( i>0 && p[i].st > p[i-1].ct)
        {
            cout << setw(10) << left << " Idle CPU" << setw(4) << left << " " <<" | ";
            cout << setw(10) << left << "  Process" << setw(4) << left <<p[i].no << " | ";
        }
        else
            cout << setw(10) << left << "  Process" << setw(4) << left <<p[i].no << " | ";
    }


    cout << endl;
    cout <<"0";
    for(int i=0; i < n ;i++)
    {
        if(i==0 && p[i].at > 0)
        {
            cout << setw(17) << right << p[i].st;
            cout << setw(17) << right << p[i].ct;
        }
        else if( i>0 && p[i].st > p[i-1].ct)
        {
            cout << setw(17) << right << p[i].st;
            cout << setw(17) << right << p[i].ct;
        }
        else
            cout << setw(17) << right << p[i].ct;
    }

    sort_at(p,n);

    cout << "\n\n";

    cout << "\nFinal timing results: " << endl;
    cout << "--------------------- \n" << endl;

    cout << setw(13) << left << "Process No" << setw(10) << left << "AT" << setw(10) << left << "BT" << setw(10) << left << "CT" << setw(10) << left << "TAT" << setw(10) << left << "WT" << endl;
    cout << setw(13) << left << "----------" << setw(10) << left << "--" << setw(10) << left << "--" << setw(10) << left << "--" << setw(10) << left << "---" << setw(10) << left << "--" << endl;

    for(int i=0; i<n ; i++)
    {
        cout << setw(13) << left << p[i].no << setw(10) << left << p[i].at << setw(10) << left << p[i].bt << setw(10) << left << p[i].ct << setw(10) << left << p[i].tat << setw(10) << left << p[i].wt << endl;
    }

    return;
}

void HRRN(Process *p, int n)
{
    int total_wt, total_tat, curr_time, mark;
    float hrrn;
    Process temp;

    //curr_time : time elapsed
    //total_tat : sum of all tat(s)
    //total_wt  : sum of all wt(s)
    //mark      : index of process with highest response ratio
    //hrrn      : stores the highest response ratio

    curr_time = p[0].ct  = p[0].bt + p[0].at;     //initialize required variables  
    total_wt = 0;
    p[0].tat = total_tat = p[0].ct - p[0].at;
    p[0].st = p[0].at;

    for(int i=1; i<n; i++)
    {
        mark = i;
        hrrn = -1;

        for(int j=i; p[j].at < curr_time && j<n ;j++)
        {
            p[j].wt = curr_time - p[j].at;                         //update waiting time
            p[j].rr = (float)(p[j].wt + p[j].bt) / p[j].bt;        //update response ratio

            if(hrrn < p[j].rr)
            {
                hrrn = p[j].rr;
                mark = j;
            }
            
        }

        if(curr_time < p[i].at)
            curr_time = p[i].at;
            
        p[mark].st = curr_time;
        curr_time += p[mark].bt;
        p[mark].ct = curr_time;
        p[mark].tat = p[mark].ct - p[mark].at;
        p[mark].wt = p[mark].tat - p[mark].bt;
    
        total_tat += p[mark].tat ;
        total_wt += p[mark].wt;

        if(mark != i)           
        {
            temp = p[i];
            p[i] = p[mark];
            p[mark] = temp;
        }

    }

    print_output(p,n);

    cout<<"\nAverage TurnArround Time : "<< (float)total_tat / n;
    cout<<"\nAverage Waiting Time     : "<< (float)total_wt / n;

    cout << endl;

    return;
}

void hrrn()
{
    cout << "\nRunning CPU Scheduling HRRN\n\n";
    int n, total_wt, total_tat, hrrn, curr_time, mark;
    struct Process *p;

    cout<<"Enter the number of processes: ";
    cin>>n;

    p = (struct Process*)malloc(n*sizeof(struct Process)); 

    cout<<"\nEnter the arrival time and burst time of processes: \n"<<endl;

    for(int i=0;i<n;i++)
    {
        cout << "Process "<< i <<" arrival time: " ;
        cin>>p[i].at;
        cout << "Process "<< i <<" burst time: " ;
        cin>>p[i].bt; 

        //initializing all 
        p[i].ct = -1; 
        p[i].wt = 0;    
        p[i].no = i; 
        p[i].rr = 1;
        p[i].st = -1;

        cout << endl;
    }

    sort_at(p,n);  //sorts the processes in increasing order of their arrival time

    HRRN(p,n);     //job scheduling

}
