#include<bits/stdc++.h>
using namespace std;

//Producer Consumer Problemn 



struct user{
    int at;
    int bt;
    char type;
    int id;
}st[32767];

bool compare(struct user user1,struct user user2)
{
    return user1.at<user2.at;
}

int shift_position(struct user st[],int index,int n)
{
    char tp;
    int i,index1,flag=0;
    struct user temp;
    //we need to find consumer for overflow and producer for underflow
    if(st[index].type=='P')
    tp='C';
    else 
    tp='P';
    for(i=index+1;i<n;i++)
    {
        if(st[i].type==tp)
        {
            flag=1;
            index1=i;
            break;
        }
    }
    //now shift the producer/consumer to just after the index we got
    if(flag==1)
    {
        temp=st[index];
        for(i=index;i<index1;i++)
        st[i]=st[i+1];
        st[i]=temp;
        return 1;        
    }
    else 
    return 0;    
}

void sendUpdate(struct user st[],int index,int n,int *ct)
{
    int i,j,f=0;
    if(index==n-1){
        if(st[index].at>*ct)
        *ct=st[index].at;
        cout<<"At time="<<*ct<<" "<<st[index].type<<st[index].id<<" has started execution\n";
        *ct=*ct+st[index].bt;
        cout<<"At time="<<*ct<<" "<<st[index].type<<st[index].id<<" has completed execution\n";
    }
    else{
        for(i=st[index].bt;i>0;i--)
        {
            f=0;
            if(st[index].type=='P')
            cout<<"At time="<<*ct<<" Producer P"<<st[index].id<<" is processing, so ";
            else 
            cout<<"At time="<<*ct<<" Consumer C"<<st[index].id<<" is processing, so ";

            j=index+1;
            while(j<n && st[j].at<=*ct)
            {
                f=1;
                cout<<st[j].type<<st[j].id<<",";
                j++;
            }
            if(f==1)
            cout<<" has to wait\n";
            else 
            cout<<"\n";
            (*ct)++;
        }
        if(st[index].type=='P')
        cout<<"At time="<<*ct<<" Producer P"<<st[index].id<<" has completed\n";
        else 
        cout<<"At time="<<*ct<<" Consumer C"<<st[index].id<<" has completed\n";
        
    }
}

void solve(struct user st[],int n,int buffer_size)
{
    int i,full=0,empty=0;
    empty=buffer_size;
    int ct=0;
    
    ct=st[0].at;
    for(i=0;i<n;i++)
    {
        if(ct<st[i].at)
        ct=st[i].at;
        if(st[i].type=='P')
        {
            //check overflow
            if(full==buffer_size)
            {
                cout<<"Overflow has occured. So the producer has to wait untill a consumer consumes.\n";
                //we need to get consumer and shift this producer
                if(shift_position(st,i,n))         //if shift successful,we have to decrement i, because we shifted the position 
                i--;
            }
            else 
            {               
                full++;             //A slot gets used
                empty--;
                sendUpdate(st,i,n,&ct);   
                //cout<<ct<<" ";            
            }
        }
        else 
        {
            //check underflow
            if(full==0)
            {
                cout<<"Undeflow has occured. So the Consumer will wait untill a Producer produces.\n";
                //we need to get producer and shift this consumer
                if(shift_position(st,i,n))           //if shift successful,we have to decrement i, because we shifted the position 
                i--;
            }
            else 
            {                
                full--;             //A slot gets freed
                empty++;
                sendUpdate(st,i,n,&ct);                
            }
        }
    }
    cout<<"\nAll processes are completed\n";
}


int main()
{
    int pn,cn,i,n,buffer_size=0;
    cout<<"Enter the buffer size : ";
    cin>>buffer_size;
    cout<<"Enter the number of producers : ";
    cin>>pn;
    for(i=0;i<pn;i++)
    {
        cout<<"Enter the arrival time and burst time for producer "<<i+1<<" : ";
        cin>>st[i].at>>st[i].bt;
        st[i].id=i+1;
        st[i].type='P';
    }
    cout<<"\nEnter the number of consumers : ";
    cin>>cn;
    n=cn+pn;
    for(i=pn;i<n;i++)
    {
        cout<<"Enter the arrival time and burst time for consumer "<<i-pn+1<<" : ";
        cin>>st[i].at>>st[i].bt;
        st[i].id=i-pn+1;
        st[i].type='C';
    }
    cout<<endl;
    sort(st,st+n,compare);           //sorting based on arrival time as it is fcfs
    solve(st,n,buffer_size);

    return 0;
}
