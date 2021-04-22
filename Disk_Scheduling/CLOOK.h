#include <bits/stdc++.h>
using namespace std;

void solve(int n, int track[], int nt, int p, int dir)
{
    int seek_time = 0;
    int i, j, index = 0, n2 = 0;
    int sequence[n];
    sort(track, track + n);
    if (dir == 1)
    {
        index = n;
        for (i = 0; i < n; i++)
        {
            if (p < track[i])
            {
                index = i;
                break;
            }
        }
        for (i = index - 1; i >= 0; i--)
        {
            sequence[n2++] = track[i];
            seek_time += abs(track[i] - p);
            p = track[i];
        }
        for (i = n - 1; i >= index; i--)
        {
            sequence[n2++] = track[i];
            seek_time += abs(track[i] - p);
            p = track[i];
        }
    }
    else
    {
        for (i = 0; i < n; i++)
        {
            if (p <= track[i])
            {
                index = i;
                break;
            }
        }
        for (i = index; i < n; i++)
        {
            sequence[n2++] = track[i];
            seek_time += abs(track[i] - p);
            p = track[i];
        }
        for (i = 0; i < index; i++)
        {
            sequence[n2++] = track[i];
            seek_time += abs(track[i] - p);
            p = track[i];
        }
    }
    cout << "Seek sequence : ";
    for (i = 0; i < n2; i++)
        cout << sequence[i] << " ";
    cout << "\nTotal seek time : " << seek_time << endl;
}

void clook()
{
    cout << "\nRunning Disk Scheduling CLOOK\n\n";

    int n, nt, i, p, dir, x;
    cout << "Enter the number of pages : ";
    cin >> n;
    int track[n];
    cout << "Enter the total number of tracks in secondary memory : ";
    cin >> nt;
    for (i = 0; i < n; i++)
    {
    here:
        cout << "Enter the track location of Page " << i << " : ";
        cin >> x;
        if (x >= nt || x < 0)
        {
            cout << "Invalid track location.\n";
            goto here;
        }
        track[i] = x;
    }
again:
    cout << "Enter the initial location of head : ";
    cin >> p;
    if (p >= nt || p < 0)
    {
        cout << "Invalid track location.\n";
        goto here;
    }
    cout << "Direction towards \n1.LEFT\n2.RIGHT\nEnter choice : ";
    cin >> dir;
    solve(n, track, nt, p, dir);
}
