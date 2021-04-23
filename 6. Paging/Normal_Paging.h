//Paging : Normal Paging
//Akanksha : 191CS106

#include<iostream>
#include<stdlib.h>
#include<iomanip>

using namespace std;

//store frames
struct Phyical_M{
    int page_no;
    int t;
    long long int word_offset;
};

//store mapping between pages no and frames
struct PageTable{
    int frame_no;
};

void print_page_table(PageTable *pt, int n_p)
{
    cout << "\n---------------------" << endl;
    cout << "Final Page Table : " << endl;
    cout << "---------------------\n" << endl;

    cout << setw(10) << left << "Page No." << setw(10) << left << "Frame No." << endl;
    cout << setw(10) << left << "--------" << setw(10) << left << "---------" << endl;

    for(int i=0 ;i< n_p ; i++)
    {
        cout << setw(10) << left << i << setw(10) << left << pt[i].frame_no << endl;
    }

    cout << endl;
    return;
}

void print_frames(Phyical_M *f, int n_f)
{
    cout << "\n----------------------------------" << endl;
    cout << "Final Physical Memory Layout : " << endl;
    cout << "----------------------------------\n" << endl;

    cout << setw(10) << left << "Frame No." << setw(10) << left << "Page No." << setw(20) << left << "Word offset(Bytes)" << endl;
    cout << setw(10) << left << "---------" << setw(10) << left << "--------" << setw(12) << left << "-----------" <<endl;
    for(int i=0 ;i< n_f ; i++)
    {
        if(f[i].page_no == -1)
            cout << setw(10) << left << i << setw(10) << left << "-" << setw(12) << left << "-" << endl;
        else
            cout << setw(10) << left << i << setw(10) << left << f[i].page_no << setw(12) << left << f[i].word_offset << endl;
    }

    cout << endl;
    return;
}

int normal_paging(void)
{
    cout << "\nRunning Normal Paging\n";
    int n_p, n_f, x, page_number, t, small, page_fault, rate;
    long int page_size, word_offset, VM_size, PM_size;
    Phyical_M *f;
    PageTable *pt;

    cout << "\nEnter size of virtual memory in KB : ";
    cin >> VM_size;

    cout << "\nEnter size of physical memory in KB : ";
    cin >> PM_size;

    cout << "\nEnter page_size in KB : ";
    cin >> page_size;

    n_p = VM_size / page_size;      //calculate number of pages
    n_f = PM_size /page_size;       //calculate number of frames

    f = (Phyical_M*)malloc(n_f*sizeof(Phyical_M));
    pt = (PageTable*)malloc(n_p*sizeof(PageTable));

    cout << "\nNumber of pages in virtual memory : " << n_p << endl;
    cout << "Number of frames in physical memory : " << n_f << endl;
    cout << endl;

    page_size = page_size * 1024;      //calculate page size in bytes

    //initialiaze page table
    for(int i = 0; i<n_p; i++)
        pt[i].frame_no = -1;
    
    //initialize frames
    for(int i = 0; i<n_f; i++)
        f[i].page_no = -1;

    t = 0;      //count of inputs

    page_fault = 0; 

    while(1)
    {
        cout << "\nMenu : " << endl;
        cout << "1 : Enter Virtual Address      2 : Stop\n" << endl;
        cout << "Enter your choice : ";
        cin >> x;
        
        if(x==2)
            break;

        if(x != 1)
        {
            cout << "\n**Please enter a valid choice**" << endl;
            continue;
        }

        t++;

        cout << "Please enter VA : ";
        cin >> page_number >> word_offset;

        if(page_number >= n_p || page_number < 0)
        {
            cout << "\n**Please enter a valid page no.**" << endl;
            continue;
        }
        

        if(word_offset > page_size)         //word offset dould be less than the page size
        {
            cout << "\n**Word offset greater than page size**" << endl;
            if(pt[page_number].frame_no != -1)       //page number already in physical memory
            {
                cout << "Page no. " << page_number << " already present in frame no. " << pt[page_number].frame_no << endl;
                cout << "Physical address : " << pt[page_number].frame_no << " " << word_offset << endl;
            }
            cout << endl;
            continue;
        }
        else if(word_offset < 0)
        {
            cout << "\n**Please enter a valid word offset**" << endl;
            continue;
        }

        if(pt[page_number].frame_no != -1)       //page number already in physical memory
        {
            cout << "Page no. " << page_number << " already present in frame no. " << pt[page_number].frame_no << endl;
            cout << "Physical address : " << pt[page_number].frame_no << " " << word_offset << endl;
            f[pt[page_number].frame_no].word_offset = word_offset;
        }
        else
        {
            cout << "Page no. " << page_number << " is not present in physical memory" << endl;
            small = 0;
            for(int i=0; i<n_f ; i++)
            {
                if(f[i].page_no == -1)          //empty frame present
                {
                    small = i;
                    break;
                }
                if(f[i].t < f[small].t)       //finding page which was accomodated earliest to remove
                    small = i;
            }

            if(f[small].page_no == -1)
                cout << "Page no. " << page_number << " is accommodated in frame no " << small << endl;
            else
            {
                cout << "Page no. " << page_number << " is accommodated in frame no. " << small << " after removal of page no. " 
                                                            << f[small].page_no << " according to FIFO" << endl;
                pt[f[small].page_no].frame_no = -1;
            }   

            pt[page_number].frame_no = small;
            f[small].page_no = page_number;
            f[small].t = t;
            f[small].word_offset = word_offset;

            page_fault++ ;
        
        }

        cout << endl;
        
    }

    cout << "---Stopped---" << endl;

    cout << "\nNumber of page faults : " << page_fault << endl;
    cout << "\nPage fault rate : " << (float)page_fault / (float)t << endl;

    cout << endl;

    print_page_table(pt,n_p);

    print_frames(f,n_f);

    return 0;
}
