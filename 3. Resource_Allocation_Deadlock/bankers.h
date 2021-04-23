// Q. Simulation of Producer Consumer Problem

#include<iostream>
#include<cassert>
#include<vector>

using namespace std;

bool is_all_processes_completed(vector<bool> is_process_complete)
{
    int process_count = is_process_complete.size();

    for(int i = 0; i < process_count; i++)
    {
        if(!is_process_complete[i])
        {
            return false;
        }
    }

    return true;
}

int bankers()
{
    cout << "Enter details of resources: \n";

    cout << "Enter the number of resources: ";
    int resource_count; 
    cin >> resource_count;

    vector<int> resource_max(resource_count);

    for(int i = 0; i < resource_count; i++)
    {
        cout << "Enter the maximum available instances of Resource " << i + 1 << ": ";
        cin >> resource_max[i];
    }

    int process_count;
    cout << "\nEnter the number of processes: ";
    cin >> process_count; 
    cout << "\n";

    vector<vector<int>> processes_allotment(process_count, vector<int>(resource_count));
    vector<vector<int>> processes_maxreq(process_count, vector<int>(resource_count));

    for(int i = 0; i < process_count; i++)
    {
        cout << "Enter details for process " << i + 1 << "\n";

        for(int j = 0; j < resource_count; j++)
        {
            cout << "Enter max need for resource " << j + 1 << ": ";
            cin >> processes_maxreq[i][j];
        }

        for(int j = 0; j < resource_count; j++)
        {
            cout << "Enter current allotment for resource " << j + 1 << ": ";
            cin >> processes_allotment[i][j];
        }

        cout << "\n";
    }

    vector<vector<int>> processes_remaining_need(process_count, vector<int>(resource_count));

    for(int i = 0; i < process_count; i++)
    {
        for(int j = 0; j < resource_count; j++)
        {
            processes_remaining_need[i][j] = processes_maxreq[i][j] - processes_allotment[i][j];
        }
    }

    vector<int> resource_availability(resource_count);

    // Initializing
    for(int i = 0; i < resource_count; i++)
    {
        resource_availability[i] = resource_max[i];
    }

    for(int i = 0; i < process_count; i++)
    {
        for(int j = 0; j < resource_count; j++)
        {
            resource_availability[j] -= processes_allotment[i][j];
        }
    }

    cout << "Checking user input ...\n";
    for(int i = 0; i < resource_count; i++)
    {
        if(resource_availability[i] < 0)
        {
            cout << "Entries are not valid.\n";
            return 0;
        }
    }

    bool is_valid = false;

    for(int i = 0; i < process_count; i++)
    {
        bool is_valid_temp = true;
        for(int j = 0; j < resource_count; j++)
        {
            if(resource_availability[j] < processes_remaining_need[i][j])
            {
                is_valid_temp = false;
                break;
            }
        }

        if(is_valid_temp)
        {
            is_valid = true;  
            break;
        }
    }

    if(!is_valid)
    {
        cout << "This is not a safe configuration.\n";
        return 0;
    }
    else {
        cout << "This is a safe configuration.\n";
    }

    vector<bool> is_process_complete(process_count);
    int remaining_processes_count = process_count;
    int process_pos = 0;

    vector<int> process_order;

    while(remaining_processes_count > 0)
    {
        if(is_process_complete[process_pos])
        {
            process_pos = (process_pos + 1) % process_count;
            continue;
        }

        is_valid = true;
        for(int i = 0; i < resource_count; i++)
        {
            if(resource_availability[i] < processes_remaining_need[process_pos][i])
            {
                is_valid = false;
                break;
            }
        }

        if(is_valid)
        {
            remaining_processes_count--;
            is_process_complete[process_pos] = true;
            for(int i = 0; i < resource_count; i++)
            {
                resource_availability[i] += processes_allotment[process_pos][i];
            }
            process_order.push_back(process_pos + 1);
        }

        process_pos = (process_pos + 1) % process_count;
    }

    cout << "The order of run: ";
    for(int i = 0; i < process_count; i++)
    {
        cout << process_order[i];

        if(i != process_count - 1)
        {
            cout << " => ";
        }
        else {
            cout << "\n";
        }
    }

    return 0;
}

