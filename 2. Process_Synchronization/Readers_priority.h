//Process Synchronization : Readers_Writers problem with reader_reader's priority

#include<iostream>
#include<stdlib.h>
#include<iomanip>

using namespace std;

//Document_reader_reader class indicates information about reader_reader/writer_reader
class Document_reader_reader{
    public:
        int at_r;               // arrival time     
        int bt_r;               // burst time 
        int ct_r;               // complete time 
        int wt_r;               // waiting time  
        int start_t_r;          // start time 
        int index_r;            // index of reader_reader/writer_reader  
        int wr_r;               // if wr_r = 1  then writer_reader else reader_reader 
        int w_r;                // indicates if a reader_reader/writer_reader is wait_readering if w_r = 1    
        int s_r;                // indicates if a reader_reader/writer_reader completed the task     
        int print_r;            // to keep track of print statment for wait_readering 
        int q_r;                // only for readers: indicates if a reader is reading or not

        Document_reader_reader()
        {
            s_r = 0;
            w_r = 0;
            wt_r = 0;
            q_r = -1;
        }
};

//to store information about readers who are reading
struct queue_reader{
    int ct;
    int index;
    queue_reader *next;
};

//merge_reader two sorted arrays of readers and writer
void merge_reader(Document_reader_reader *p, Document_reader_reader *l, Document_reader_reader *r, int lc, int rc) 
{
    int i,j,k;
    i = j = k =0;
    while(j<lc&&k<rc)
    {
        if(r[k].at_r <= l[j].at_r)
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
        if(b[i].wr_r == 0)
        {
            cout << setw(13) << left << b[i].index_r+1 << setw(7) << left << b[i].at_r << setw(7) << left << b[i].bt_r << setw(7) << left << b[i].ct_r <<endl;
            j++;
        }
    }

    cout << "\n\n";

    cout << setw(13) << left <<"Writer No." << setw(7) << left << "AT" << setw(7) << left << "BT" <<setw(7) << left << "CT" << endl;
    cout << setw(13) << left <<"----------" << setw(7) << left << "----" << setw(7) << left << "----" <<setw(7) << left << "----" << endl;

    j = 0;
    for(int i=0; j<n ; i++)
    {
        if(b[i].wr_r == 1)
        {
            cout << setw(13) << left << b[i].index_r+1 << setw(7) << left << b[i].at_r << setw(7) << left << b[i].bt_r << setw(7) << left << b[i].ct_r <<endl;
            j++;
        }
    }
    return;
}


//to enqueue reader who starts reading
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

//to dequeue reader who completes reading
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
 

//writer_reader function to modify curr_time, R if writer is writing
int writer_reader(Document_reader_reader *b ,int x, int i, int curr_time)  
{
    cout<<"Writer "<<x+1<<" started writing at time "<< curr_time << ".\n" <<endl;
    b[i].start_t_r = curr_time;
    curr_time += b[i].bt_r;
    
    b[i].ct_r = curr_time;
    b[i].s_r = 1;
    b[i].w_r = -1;
    return curr_time;
}


//reader_reader function to modify curr_time, R if reader is reading
int reader_reader(int R, Document_reader_reader *b, int x, int i, int curr_time)  
{
    int t;

    if(R==1 && b[i].wt_r>0)       
    {
        if(b[i].wt_r + b[i].bt_r <= curr_time)
        {
            t = 0;
        }    
        else
        {
            t = b[i].wt_r + b[i].bt_r - curr_time;
        }
    }
    else if(R==1)            
    {
        if(b[i].at_r + b[i].bt_r > curr_time)
            t = b[i].at_r + b[i].bt_r - curr_time;
        else
            t = 0;
    }
    else
        t = b[i].bt_r;

    curr_time += t;

    if(b[i].wt_r == 0)
    {
        b[i].start_t_r = b[i].at_r;
        b[i].ct_r = b[i].at_r + b[i].bt_r;
    }
    else
    {
        b[i].start_t_r = b[i].wt_r;
        b[i].ct_r = b[i].wt_r + b[i].bt_r;
    }
        

    b[i].s_r = 1;
    b[i].w_r = -1;

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
    //R: indicates whether a reader is reading or reader is writing

    cout<<"Enter number of reader_readers: ";
    cin>>m;

    r = (Document_reader_reader*)malloc(m*sizeof(Document_reader_reader));
    if(m>0)
    {
        cout<<"\nEnter arrival time and burst time of reader_readers: "<<endl;
        for(i=0;i<m;i++)
        {
            cout << "\nReader " << i+1 <<" arrival time: ";
            cin >> r[i].at_r;
            cout << "Reader " << i+1 <<" burst time  : ";
            cin >> r[i].bt_r;

            r[i].wr_r = 0;
            r[i].index_r = i;

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
            cin >> w[i].at_r;
            cout << "Writer " << i+1 <<" burst time  : ";
            cin >> w[i].bt_r;

            w[i].wr_r = 1;
            w[i].index_r = i;

        }

    }
    
    b = (Document_reader_reader*)malloc((m+n)*sizeof(Document_reader_reader));

    sort_at_reader(w,n);
    sort_at_reader(r,m);
    merge_reader(b,w,r,n,m);

    // cout << "\n---" << endl;
    // for(int i=0; i<n+m ;i++)
    //     cout << b[i].wr <<" " << b[i].index <<endl;

    S = 1;   
    R = 0;   
    curr_time =0;

    cout << "\n\n--------------------------------------------------------" << endl;
    cout << "Order in which reader_readers and writer_readers access document:" << endl;
    cout << "--------------------------------------------------------\n" << endl;

    for(i=0 ; i<n+m;)
    {
        if(b[i].s_r == 1)
        {
            i++;
            continue;
        }    
        
        mark = i;
        
        if(b[i].wr_r==1)
        {
            for(j=i+1; b[j].w_r != 0 ;j++)
            {
                if(b[j].s_r == 1 )
                    continue;
                if(b[j].wr_r == 0)
                {
                    i = j;
                    R = 1;
                    wait_reader(S);
                    curr_time = reader_reader(R,b,b[i].index_r,i,curr_time);
                    signal_reader(S);
                    R = 1;
                    if(b[i].start_t_r == b[i].at_r)
                        cout<<"Reader "<< b[i].index_r+1 <<" arrived at time " << b[i].start_t_r << " and started reading.\n " <<endl;
                    else
                        cout<<"Reader "<< b[i].index_r+1 <<" started reading at time "<< b[i].start_t_r << ".\n" <<endl;
                    head = enqueue_reader_reader(b[i].ct_r, b[i].index_r, head);
                    b[i].q_r = 1;
                    break;
                }    
            }
            if(mark==i)
            {
                R = 0;
                wait_reader(S);
                curr_time = writer_reader(b,b[i].index_r,i, curr_time);
                signal_reader(S);
            }
        }   
        else
        {
            wait_reader(S);
            curr_time = reader_reader(R,b,b[i].index_r,i,curr_time);
            signal_reader(S);
            R = 1;
            if(b[i].start_t_r == b[i].at_r)
                cout<<"Reader "<< b[i].index_r+1 <<" arrived at time " << b[i].start_t_r << " and started reading.\n " <<endl;
            else
                cout<<"Reader "<< b[i].index_r+1 <<" started reading at time "<< b[i].start_t_r << ".\n" <<endl;
            head = enqueue_reader_reader(b[i].ct_r, b[i].index_r, head);
            b[i].q_r = 1;
        }

        t = 0;
        for(j=0; b[j].at_r <= curr_time && j<n+m;j++)
        {    
            if(b[j].s_r == 1)
                continue;
            if(b[j].wr_r == 0 && R==1)
            {
                wait_reader(S);
                curr_time = reader_reader(R,b,b[j].index_r,j,curr_time);
                signal_reader(S);

                while(head != NULL && head->ct <= b[j].start_t_r)
                    head = dequeue_reader_reader(head);
                if(b[j].start_t_r == b[j].at_r)
                    cout<<"Reader "<< b[j].index_r+1 <<" arrived at time " << b[j].start_t_r << " and started reading.\n " <<endl;
                else
                    cout<<"Reader "<< b[j].index_r+1 <<" started reading at time "<< b[j].start_t_r << ".\n" <<endl;
                R = 1;
                head = enqueue_reader_reader(b[j].ct_r, b[j].index_r, head);
                b[j].q_r = 1;
                continue;
            }
            else if(b[j].w_r == 1)
            {
                b[j].wt_r = curr_time;
                continue;
            }
            else if(b[j].wr_r == 1)
            {
                while(head != NULL && head->ct <= b[j].at_r)
                    head = dequeue_reader_reader(head);
                cout << "Writer "<< b[j].index_r + 1 << " arrived at time " << b[j].at_r << " and has to wait_reader.\n"<<endl;
                b[j].w_r = 1;
            }
            else if(b[j].wr_r==0 && b[j].at_r < curr_time)
            {
                cout << "Reader "<< b[j].index_r + 1 << " arrived at time " << b[j].at_r << " and has to wait_reader.\n"<<endl;
                b[j].w_r =1;
            }
            else if(b[j].wr_r==0)
            {
                b[j].w_r = 1;
            }

            b[j].wt_r = curr_time;  
        }

        if(b[i].wr_r == 1)
            cout<< "Writer "<< b[i].index_r +1 <<" finished writing at time "<<  b[i].ct_r << ".\n" << endl;
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

