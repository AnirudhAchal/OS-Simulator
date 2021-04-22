//Disk Scheduling : SSTF
//Akanksha : 191CS106
#include<iostream>
#include<stdlib.h>

using namespace std;

//SSTF function
void SSTF(int *track, int n, int start)
{
    int small, seek, w_r_head, temp, direction, l_small, r_small;

    w_r_head = start;      //initial position of read-write head
    seek = 0;              //total seek time

    for(int i=0; i<n ;i++)
    {
        l_small = -1;           // initializing the index for finding smallest seek time on left hand side of read-write head
        r_small = -1;           // initializing the index for finding smallest seek time on right hand side of read-write head

        for(int j=i; j < n ; j++)
        {
            
            if(w_r_head < track[j]) 
            {
                if(r_small == -1)       // first smallest seek request on right hand side of read-write head   
                    r_small = j;
                else if(track[j]-w_r_head < track[r_small] - w_r_head)
                {
                    r_small = j;
                } 
            }
            else
            {
                if(l_small == -1)      // first smallest seek request on left hand side of read-write head  
                    l_small = j;
                else if(w_r_head-track[j] < w_r_head -track[l_small])
                {
                    l_small = j;
                }
            }
        }

        //next track request to be assisted
        if(l_small == -1 || ( r_small >-1 && track[r_small] - w_r_head < w_r_head -track[l_small]))
        {
            small = r_small;
            seek += (track[small] - w_r_head);
        }
        else if(r_small == -1 || (track[r_small] - w_r_head > w_r_head -track[l_small]))
        {
            small = l_small;
            seek += (w_r_head-track[small]);
        }
        else
        {
            if(direction == 1)
                small = r_small;
            else
                small = l_small;
        }

        // to check the direction of read-write head
        if(w_r_head > track[small])
            direction = -1;
        else if(w_r_head < track[small])
            direction = 1;

        w_r_head = track[small];

        //to segragate pending traxk requests from the handled once into right sub array
        if(small != i)
        {
            temp = track[small];
            track[small] = track[i];
            track[i] = temp;
        }

    }

    cout << "\nTotal seek time : " << seek << endl;
    
    cout << "\nOrder of track requests : " << endl;
    cout << "Head(" << start << ")"; 
    for(int i=0; i<n ;i++)
    {
        cout << " ==> " << track[i];
    }

    cout << "\n\n";

    return;
}


void sstf(void)
{
    cout << "\nRunning Disk Scheduling SSTF\n\n"; 

    int *track_req, n, n_tracks, start;

    cout << "Enter total number of tracks: " ;
    cin >> n_tracks;

    cout << "\nEnter total number of track requests: ";
    cin >> n;
    track_req = (int*)malloc(n*sizeof(int));

    cout << "\nEnter position of read-write head: ";
    cin >> start;

    cout << "\nEnter the track requests: \n" << endl;
    for(int i=0; i<n ;)
    {
        cout << "Enter track request " << i+1 << " : ";
        cin >> track_req[i];

        if(track_req[i] > n_tracks)
        {
            cout << "Invalid track request" << endl;
            continue;
        }

        i++;

    }

    SSTF(track_req,n,start);

}
