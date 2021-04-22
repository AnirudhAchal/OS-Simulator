//Process Synchronization : Readers_Writers problem with reader_reader's priority

#include<iostream>
#include<stdlib.h>
#include<iomanip>

using namespace std;

//Document_reader_reader class indicates information about reader_reader/writer_reader
class Document_reader_reader{
    public:
        int at;               // arrival time     
        int bt;               // burst time 
        int ct;               // complete time 
        int wt;               // wait_readering time  
        int start_t;          // start time 
        int index;            // index of reader_reader/writer_reader  
        int wr;               // if wr = 1  then writer_reader else reader_reader 
        int w;                // indicates if a reader_reader/writer_reader is wait_readering if w = 1    
        int s;                // indicates if a reader_reader/writer_reader completed the task     
        int print;            // to keep track of print statment for wait_readering 
        int q;                // only for reader_readers: indicates if a reader_reader is reading or not

        Document_reader_reader()
        {
            s = 0;
            w = 0;
            wt = 0;
            q = -1;
        }
};

//to store information about reader_readers who are reading
struct queue_reader{
    int ct;
    int index;
    queue_reader *next;
};

//merge_reader two sorted arrays of reader_readers and writer_readers
void merge_reader(Document_reader_reader *p, Document_reader_reader *l, Document_reader_reader *r, int lc, int rc) 
{
    int i,j,k;
    i = j = k =0;
    while(j<lc&&k<rc)
    {
        if(r[k].at <= l[j].at)
            p[i++] = r[k++];
        else
            p[i++] = l[j++];
    }
    while(j<lc)
        p[i++] = l[j++];
    while(k<rc)
        p[i++] = r[k++];
}

//merge_reader sort algorithm
void sort_at_reader(Document_reader_reader *p, int size)   
{
    Document_reader_reader *l, *r;
    int i,j,mid;

    if(size<2)
        return;

    i = j = 0;
    mid = size/2;

    l = (Document_reader_reader*)malloc(mid*sizeof(Document_reader_reader));
    r = (Document_reader_reader*)malloc((size-mid)*sizeof(Document_reader_reader));  

    while(i<mid)
    {
        l[j++] = p[i++];
    }

    j = 0;
    while(i<size)
    {
        r[j++] = p[i++];
    }

    sort_at_reader(l,mid);
    sort_at_reader(r,size-mid);
    merge_reader(p,l,r,mid,size-mid);
    free(l);
    free(r);
}


void print_table_reader(Document_reader_reader *b,int n, int m)  
{
    int i, j;

    cout << "----------------------------" << endl;
    cout << "Resulting completion times:   " << endl;
    cout << "----------------------------\n\n" << endl;

    cout << setw(13) << left <<"Reader No." << setw(7) << left << "AT" << setw(7) << left << "BT" <<setw(7) << left << "CT" << endl;
    cout << setw(13) << left <<"----------" << setw(7) << left << "----" << setw(7) << left << "----" <<setw(7) << left << "----" << endl;

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


//to enqueue_reader_reader reader_reader who starts reading
queue_reader* enqueue_reader_reader(int ct, int index, queue_reader *head)
{
    queue_reader *temp, *temp1;
    temp = (queue_reader*)malloc(sizeof(queue_reader));
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

//to dequeue_reader_reader reader_reader who completes reading
queue_reader* dequeue_reader_reader(queue_reader *head)
{
    queue_reader *temp;
    temp = head;
    
    if(head == NULL)
        return head;

    cout << "Reader " << head->index + 1 <<" finished reading at time "<< head->ct << ".\n" <<endl;

    head = head->next;

    return head;
    
}


//wait_reader function to ensure that no other process in interrupted
void wait_reader(int S)  
{
    while(S<=0);
    S = S-1;
}

//signal_reader function to to show that current process is completed
void signal_reader(int S) 
{
    S = S+1;
}
 

//writer_reader function to modify curr_time, R if writer_reader is writing
int writer_reader(Document_reader_reader *b ,int x, int i, int curr_time)  
{
    cout<<"Writer "<<x+1<<" started writing at time "<< curr_time << ".\n" <<endl;
    b[i].start_t = curr_time;
    curr_time += b[i].bt;
    
    b[i].ct = curr_time;
    b[i].s = 1;
    b[i].w = -1;
    return curr_time;
}


//reader_reader function to modify curr_time, R if reader_reader is reading
int reader_reader(int R, Document_reader_reader *b, int x, int i, int curr_time)  
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
int readers_priority(void)
{
    cout << "\nRunning Process Synchronization Readers Priority\n\n";
    int n, m, i, j, mark, curr_time, t;
    int S=0, R; 
    queue_reader* head = NULL;
    Document_reader_reader *b, *r, *w;

    //S: semaphore variable
    //curr_time: current time
    //R: indicates whether a reader_reader is reading or writer_reader is writing

    cout<<"Enter number of reader_readers: ";
    cin>>m;

    r = (Document_reader_reader*)malloc(m*sizeof(Document_reader_reader));
    if(m>0)
    {
        cout<<"\nEnter arrival time and burst time of reader_readers: "<<endl;
        for(i=0;i<m;i++)
        {
            cout << "\nReader " << i <<" arrival time: ";
            cin >> r[i].at;
            cout << "Reader " << i <<" burst time  : ";
            cin >> r[i].bt;

            r[i].wr = 0;
            r[i].index = i;

        }

    }
    
    cout<<"\nEnter number of writer_readers: ";
    cin>>n;

    w = (Document_reader_reader*)malloc(n*sizeof(Document_reader_reader));
    if(n>0)
    {
        cout<<"\nEnter arrival time and burst time of writer_readers: "<<endl;
        for(i=0;i<n;i++)
        {
            cout << "\nWriter " << i+1 <<" arrival time: ";
            cin >> w[i].at;
            cout << "Writer " << i+1 <<" burst time  : ";
            cin >> w[i].bt;

            w[i].wr = 1;
            w[i].index = i;

        }

    }
    
    b = (Document_reader_reader*)malloc((m+n)*sizeof(Document_reader_reader));

    sort_at_reader(w,n);
    sort_at_reader(r,m);
    merge_reader(b,w,r,n,m);

    cout << "\n---" << endl;
    for(int i=0; i<n+m ;i++)
        cout << b[i].wr <<" " << b[i].index <<endl;

    S = 1;   
    R = 0;   
    curr_time =0;

    cout << "\n\n--------------------------------------------------------" << endl;
    cout << "Order in which reader_readers and writer_readers access document:" << endl;
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
            for(j=i+1; b[j].w != 0 ;j++)
            {
                if(b[j].s == 1 )
                    continue;
                if(b[j].wr == 0)
                {
                    i = j;
                    R = 1;
                    wait_reader(S);
                    curr_time = reader_reader(R,b,b[i].index,i,curr_time);
                    signal_reader(S);
                    R = 1;
                    if(b[i].start_t == b[i].at)
                        cout<<"Reader "<< b[i].index+1 <<" arrived at time " << b[i].start_t << " and started reading.\n " <<endl;
                    else
                        cout<<"Reader "<< b[i].index+1 <<" started reading at time "<< b[i].start_t << ".\n" <<endl;
                    head = enqueue_reader_reader(b[i].ct, b[i].index, head);
                    b[i].q = 1;
                    break;
                }    
            }
            if(mark==i)
            {
                R = 0;
                wait_reader(S);
                curr_time = writer_reader(b,b[i].index,i, curr_time);
                signal_reader(S);
            }
        }   
        else
        {
            wait_reader(S);
            curr_time = reader_reader(R,b,b[i].index,i,curr_time);
            signal_reader(S);
            R = 1;
            if(b[i].start_t == b[i].at)
                cout<<"Reader "<< b[i].index+1 <<" arrived at time " << b[i].start_t << " and started reading.\n " <<endl;
            else
                cout<<"Reader "<< b[i].index+1 <<" started reading at time "<< b[i].start_t << ".\n" <<endl;
            head = enqueue_reader_reader(b[i].ct, b[i].index, head);
            b[i].q = 1;
        }

        t = 0;
        for(j=0; b[j].at <= curr_time && j<n+m;j++)
        {    
            if(b[j].s == 1)
                continue;
            if(b[j].wr == 0 && R==1)
            {
                wait_reader(S);
                curr_time = reader_reader(R,b,b[j].index,j,curr_time);
                signal_reader(S);

                while(head != NULL && head->ct <= b[j].start_t)
                    head = dequeue_reader_reader(head);
                if(b[j].start_t == b[j].at)
                    cout<<"Reader "<< b[j].index+1 <<" arrived at time " << b[j].start_t << " and started reading.\n " <<endl;
                else
                    cout<<"Reader "<< b[j].index+1 <<" started reading at time "<< b[j].start_t << ".\n" <<endl;
                R = 1;
                head = enqueue_reader_reader(b[j].ct, b[j].index, head);
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
                    head = dequeue_reader_reader(head);
                cout << "Writer "<< b[j].index + 1 << " arrived at time " << b[j].at << " and has to wait_reader.\n"<<endl;
                b[j].w = 1;
            }
            else if(b[j].wr==0 && b[j].at < curr_time)
            {
                cout << "Reader "<< b[j].index + 1 << " arrived at time " << b[j].at << " and has to wait_reader.\n"<<endl;
                b[j].w =1;
            }
            else if(b[j].wr==0)
            {
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
                head = dequeue_reader_reader(head);
            }
        }
        
        if(mark != i)
            i = mark;
        else
            i++;
        R = 0;

    }

    cout << endl;

    print_table_reader(b,n,m);

    cout << endl;

    
    return 0;
}

