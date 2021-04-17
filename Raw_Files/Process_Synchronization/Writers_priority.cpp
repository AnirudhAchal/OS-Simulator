//Process Synchronization : Readers_Writers problem with writers priority
//Akanksha : 191CS106

#include<iostream>
#include<stdlib.h>
#include<iomanip>

using namespace std;

//Document class indicates information about reader/writer
class Document{
    public:
        int at;               // arrival time     
        int bt;               // burst time 
        int ct;               // complete time 
        int wt;               // waiting time  
        int start_t;          // start time 
        int index;            // index of reader/writer  
        int wr;               // if wr = 1  then writer else reader 
        int w;                // indicates if a reader/writer is waiting if w = 1    
        int s;                // indicates if a reader/writer completed the task     
        int print;            // to keep track of print statment for waiting 
        int q;                // only for readers: indicates if a reader is reading or not
};

//to store information about readers who are reading
struct queue{
    int ct;
    int index;
    queue *next;
};

//merge two sorted arrays of readers and writers
void merge(Document *p, Document *l, Document *r, int lc, int rc) 
{
    int i,j,k;
    i = j = k =0;
    while(j<lc&&k<rc)
    {
        if(l[j].at <= r[k].at)
            p[i++] = l[j++];
        else
            p[i++] = r[k++];
    }
    while(j<lc)
        p[i++] = l[j++];
    while(k<rc)
        p[i++] = r[k++];
}

//merge sort algorithm
void sort_at(Document *p, int size)   
{
    Document *l, *r;
    int i,j,mid;

    if(size<2)
        return;

    i = j = 0;
    mid = size/2;

    l = (Document*)malloc(mid*sizeof(Document));
    r = (Document*)malloc((size-mid)*sizeof(Document));  

    while(i<mid)
    {
        l[j++] = p[i++];
    }

    j = 0;
    while(i<size)
    {
        r[j++] = p[i++];
    }

    sort_at(l,mid);
    sort_at(r,size-mid);
    merge(p,l,r,mid,size-mid);
    free(l);
    free(r);
}


void print_table(Document *b,int n, int m)  
{
    int i, j;

    cout << "----------------------------" << endl;
    cout << "Resulting completion times:   " << endl;
    cout << "----------------------------\n\n" << endl;

    cout << setw(13) << left <<"Reader No." << setw(7) << left << "AT" << setw(7) << left << "BT" <<setw(7) << left << "CT" << endl;
    cout << setw(13) << left <<"----------" << setw(7) << left << "----" << setw(7) << left << "----" <<setw(7) << left << "----" << endl;
    if(m==0)
        cout << "**No readers accessed the document**" << endl;
    j = 0;
    for(int i=0; j<m ; i++)
    {
        if(b[i].wr == 0)
        {
            cout << setw(13) << left << b[i].index+1 << setw(7) << left << b[i].at << setw(7) << left << b[i].bt << setw(7) << left << b[i].ct <<endl;
            j++;
        }
    }


    cout << "\n\n";

    cout << setw(13) << left <<"Writer No." << setw(7) << left << "AT" << setw(7) << left << "BT" <<setw(7) << left << "CT" << endl;
    cout << setw(13) << left <<"----------" << setw(7) << left << "----" << setw(7) << left << "----" <<setw(7) << left << "----" << endl;
    if(n==0)
        cout << "**No writers accessed the document**" << endl;
    j = 0;
    for(int i=0; j<n ; i++)
    {
        if(b[i].wr == 1)
        {
            cout << setw(13) << left << b[i].index+1 << setw(7) << left << b[i].at << setw(7) << left << b[i].bt << setw(7) << left << b[i].ct <<endl;
            j++;
        }
    }
    return;
}


//to enqueue reader who starts reading
queue* enqueue(int ct, int index, queue *head)
{
    queue *temp, *temp1;
    temp = (queue*)malloc(sizeof(queue));
    temp->ct = ct;
    temp->index = index;
    if(head == NULL)
    {
        temp->next = NULL;
        head = temp;
        return head;
    }
    temp1 = head;
    while(temp1->next != NULL && temp1->next->ct <= temp->ct)
    {
        temp1 = temp1->next;
    }
    if(temp1 == head)
    {
        if(temp1->ct > temp->ct)
        {
            temp->next = temp1;
            head = temp;
        }
        else
        {
            temp1->next = temp;
            temp->next = NULL;
        }
    }
    else
    {
        temp->next = temp1->next;
        temp1->next = temp;
    }

    return head;
}

//to dequeue reader who completes reading
queue* dequeue(queue *head)
{
    queue *temp;
    temp = head;
    
    if(head == NULL)
        return head;

    cout << "Reader " << head->index + 1 <<" finished reading at time "<< head->ct << ".\n" <<endl;

    head = head->next;

    return head;
    
}


//wait function to ensure that no other process in interrupted
void wait(int S)  
{
    while(S<=0);
    S = S-1;
}

//signal function to to show that current process is completed
void signal(int S) 
{
    S = S+1;
}
 

//writer function to modify curr_time, R if writer is writing
int writer(Document *b ,int x, int i, int curr_time)  
{
    cout<<"Writer "<<x+1<<" started writing at time "<< curr_time << ".\n" <<endl;
    b[i].start_t = curr_time;
    curr_time += b[i].bt;
    
    b[i].ct = curr_time;
    b[i].s = 1;
    b[i].w = -1;
    return curr_time;
}


//reader function to modify curr_time, R if reader is reading
int reader(int R, Document *b, int x, int i, int curr_time)  
{
    int t;

    if(R==1 && b[i].wt>0)       
    {
        if(b[i].wt + b[i].bt <= curr_time)
        {
            t = 0;
        }    
        else
        {
            t = b[i].wt + b[i].bt - curr_time;
        }
    }
    else if(R==1)            
    {
        if(b[i].at + b[i].bt > curr_time)
            t = b[i].at + b[i].bt - curr_time;
        else
            t = 0;
    }
    else
        t = b[i].bt;

    curr_time += t;

    if(b[i].wt == 0)
    {
        b[i].start_t = b[i].at;
        b[i].ct = b[i].at + b[i].bt;
    }
    else
    {
        b[i].start_t = b[i].wt;
        b[i].ct = b[i].wt + b[i].bt;
    }
        

    b[i].s = 1;
    b[i].w = -1;

    return curr_time;
}


//main function
int main(void)
{
    int n, m, i, j, mark, curr_time, t;
    int S=0, R; 
    queue* head = NULL;
    Document *b, *r, *w;

    //S: semaphore variable
    //curr_time: current time
    //R: indicates whether a reader is reading or writer is writing

    cout<<"Enter number of readers: ";
    cin>>m;

    r = (Document*)malloc(m*sizeof(Document));
    if(m>0)
    {
        cout<<"\nEnter arrival time and burst time of readers: "<<endl;
        for(i=0;i<m;i++)
        {
            cout << "\nReader " << i <<" arrival time: ";
            cin >> r[i].at;
            cout << "Reader " << i <<" burst time  : ";
            cin >> r[i].bt;

            r[i].wr = 0;
            r[i].s = r[i].w = 0;
            r[i].index = i;
            r[i].wt = 0;
            r[i].q = -1;

        }

    }
    
    cout<<"\nEnter number of writers: ";
    cin>>n;

    w = (Document*)malloc(n*sizeof(Document));
    if(n>0)
    {
        cout<<"\nEnter arrival time and burst time of writers: "<<endl;
        for(i=0;i<n;i++)
        {
            cout << "\nWriter " << i+1 <<" arrival time: ";
            cin >> w[i].at;
            cout << "Writer " << i+1 <<" burst time  : ";
            cin >> w[i].bt;

            w[i].wr = 1;
            w[i].s = w[i].w = 0;
            w[i].index = i;
            w[i].wt = 0;
            w[i].q = -1;

        }

    }
    
    b = (Document*)malloc((m+n)*sizeof(Document));

    sort_at(w,n);
    sort_at(r,m);
    merge(b,w,r,n,m);

    S = 1;   
    R = 0;   
    curr_time =0;

    cout << "\n\n--------------------------------------------------------" << endl;
    cout << "Order in which readers and writers access document:" << endl;
    cout << "--------------------------------------------------------\n" << endl;

    for(i=0 ; i<n+m;)
    {
        if(b[i].s == 1)
        {
            i++;
            continue;
        }    
        
        mark = i;
        
        if(b[i].wr==1)
        {
            R = 0;
            wait(S);
            curr_time = writer(b,b[i].index,i, curr_time);
            signal(S);
        }   
        else
        {
            for(j=0; b[j].w != 0 || b[j].at <= curr_time ;j++)
            {
                if(b[j].s == 1 || j==i)
                    continue;
                if(b[j].wr == 1)
                {
                    i = j;
                    R = 0;
                    wait(S);
                    curr_time = writer(b,b[i].index,i,curr_time);
                    signal(S);
                    break;
                }    
            }
            if(mark == i)
            {
                wait(S);
                curr_time = reader(R,b,b[i].index,i,curr_time);
                signal(S);
                R = 1;
                if(b[i].start_t == b[i].at)
                    cout<<"Reader "<< b[i].index+1 <<" arrived at time " << b[i].start_t << " and started reading.\n " <<endl;
                else
                    cout<<"Reader "<< b[i].index+1 <<" started reading at time "<< b[i].start_t << ".\n" <<endl;
                head = enqueue(b[i].ct, b[i].index, head);
                b[i].q = 1;
            }
            
        }


        t = 0;
        for(j=0; b[j].at<curr_time && j<n+m;j++)
        {    
            if(b[j].s == 1)
                continue;
            if(b[j].wr == 0 && R==1)
            {
                wait(S);
                curr_time = reader(R,b,b[j].index,j,curr_time);
                signal(S);

                while(head != NULL && head->ct <= b[j].start_t)
                    head = dequeue(head);
                if(b[j].start_t == b[j].at)
                    cout<<"Reader "<< b[j].index+1 <<" arrived at time " << b[j].start_t << " and started reading.\n " <<endl;
                else
                    cout<<"Reader "<< b[j].index+1 <<" started reading at time "<< b[j].start_t << ".\n" <<endl;
                R = 1;
                head = enqueue(b[j].ct, b[j].index, head);
                b[j].q = 1;
                continue;
            }
            else if(b[j].w == 1)
            {
                b[j].wt = curr_time;
                continue;
            }
            else if(b[j].wr == 1)
            {
                while(head != NULL && head->ct <= b[j].at)
                    head = dequeue(head);
                cout << "Writer "<< b[j].index + 1 << " arrived at time " << b[j].at << " and has to wait.\n"<<endl;
                b[j].w = 1;
            }
            else
            {
                while(head != NULL && head->ct <= b[j].at)
                    head = dequeue(head);
                cout << "Reader "<< b[j].index + 1 << " arrived at time " << b[j].at << " and has to wait.\n"<<endl;
                b[j].w = 1;
            }

            b[j].wt = curr_time;  
        }

        if(b[i].wr == 1)
            cout<< "Writer "<< b[i].index +1 <<" finished writing at time "<<  b[i].ct << ".\n" << endl;
        else
        {
            while (head!= NULL)
            {
                head = dequeue(head);
            }
        }
        
        if(mark != i)
            i = mark;
        else
            i++;
        R = 0;

    }

    cout << endl;

    print_table(b,n,m);

    cout << endl;

    
    return 0;
}

