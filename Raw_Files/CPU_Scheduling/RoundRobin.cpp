#include<bits/stdc++.h>
using namespace std;

struct RR{
    int at;
    int bt;
    int rem_bt;
    int ct;
    int id;
    int inq;
};

bool compare(struct RR time1, struct RR time2)
{
    return time1.at < time2.at;
}

void solve(struct RR st[],int n,int time_slice)
{
        cout<<"Gantt Chart : ";
        sort(st,st+n,compare);
        int i,j,t=0,sum1=0,sum2=0;
        float tat,wt;
        queue<struct RR *> q;
        struct RR *x;
        i=0;
        j=0;
        q.push(&st[0]);
        t=st[0].at;
        if(t>0)
        cout<<"0 idle "<<t<<" ";
        else
        cout<<"0 ";
here:   while(!q.empty())
        {
            x=q.front();
            q.pop();
            x->inq=0;
            cout<<"P"<<x->id<<" ";
            if(x->rem_bt>=time_slice)
            {
                t=t+time_slice;
                x->rem_bt=x->rem_bt-time_slice;
            }
            else 
            {
                t=t+x->rem_bt;
                x->rem_bt=0;
            }
            for(i=0;i<n;i++)
            {
                if(x!=&st[i] && st[i].ct==-1)
                {
                    if(st[i].at<=t && st[i].inq==0)
                    {
                        st[i].inq=1;
                        q.push(&st[i]);
                    }
                }
            }
            cout<<t<<" ";
            if(x->rem_bt>0)
            {
                x->inq=1;
                q.push(x);
            }
            else {
                x->ct=t;
            }
        }
        for (i=0;i<n;i++)
        {
            if (st[i].ct==-1)
            {
                t=st[i].at;
                cout<<"idle "<<t<<" ";
                st[i].inq=1;
                q.push(&st[i]);
                goto here;
            }
        }
        cout<<endl;
        cout << "Pid Arriving Burst Completing TAT Waiting\n";
        for (i = 0; i < n; i++)
        {
            cout <<"P"<< st[i].id<<"     " << st[i].at << " \t " << st[i].bt << "\t " << st[i].ct << "\t  " << st[i].ct - st[i].at << "\t" << st[i].ct - st[i].at - st[i].bt << endl;
            sum1 += st[i].ct - st[i].at;
            sum2 += st[i].ct - st[i].at - st[i].bt;
        }
        tat = (float)sum1 / n;
        wt = (float)sum2 / n;
        cout << "Average turn around time:" << tat << endl;
        cout << "Average waiting time:" << wt << endl;
}

int main()
{
    int n,i,j,time_slice=0;
    struct RR st[10000];
    cout<<"Enter the number of processes : ";
    cin>>n;
    for(i=0;i<n;i++)
    {
        cout<<"Enter the arrival time and burst time of Process P"<<i<<" : ";
        cin>>st[i].at>>st[i].bt;
        st[i].rem_bt=st[i].bt;       
        st[i].ct=-1; 
        st[i].inq=0;
        st[i].id=i;
    }
    cout<<"Enter the time quantum : ";
    cin>>time_slice;
    solve(st,n,time_slice);
    return 0;
}
