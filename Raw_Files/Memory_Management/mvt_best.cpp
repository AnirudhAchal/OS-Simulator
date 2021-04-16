// Q. Mvt memory management simulation best fit

#include<iostream>
#include<cassert>
#include<vector>

using namespace std;

struct partition {
    int start;
    int end;
    int process_id;
};

void print_menu()
{
    cout << "\nMain Menu:\t1. Insert Process\t2. Delete Process\t3. Quit\n\n";
}

void print_table(vector<partition> partitions, int total_memory)
{
    cout << "\nMemory Table\n";

    int partition_count = 1;
    for(int i = 0; i < partitions.size(); i++)
    {
        if(i == 0)
        {
            if(partitions[i].start != 0)
            {
                int partition_size = partitions[i].start;
                cout << "Partition " << partition_count << " is empty with size " << partition_size << "\n";
                partition_count++;
            }

            int partition_size = partitions[i].end - partitions[i].start;
            cout << "Partition " << partition_count << " has process " << partitions[i].process_id << " with size " << partition_size << "\n";
            partition_count++;
        }
        else {
            if(partitions[i].start != partitions[i - 1].end)
            {
                int partition_size = partitions[i].start - partitions[i - 1].end;
                cout << "Partition " << partition_count << " is empty with size " << partition_size << "\n";
                partition_count++;
            }

            int partition_size = partitions[i].end - partitions[i].start;
            cout << "Partition " << partition_count << " has process " << partitions[i].process_id << " with size " << partition_size << "\n";
            partition_count++;
        }

        if(i == partitions.size() - 1)
        {
            if(partitions[i].end != total_memory)
            {
                int partition_size = total_memory - partitions[i].end;
                cout << "Partition " << partition_count << " is empty with size " << partition_size << "\n";
                partition_count++;
            }
        }
    }

    if(partitions.size() == 0)
    {
        int partition_size = total_memory;
        cout << "Partition " << partition_count << " is empty with size " << partition_size << "\n";
        partition_count++;
    }
}

int main()
{
    int total_memory;
    cout << "Enter size of total memory: ";
    cin >> total_memory;

    vector<partition> partitions;

    int used_memory = 0;
    int process_allocated_count = 0;
    int process_count = 1;

    while(true)
    {
        print_menu();
        cout << "Choice : ";
        int choice;
        cin >> choice;
        cout << "\n";

        if(choice == 1)
        {
            cout << "Process ID : ";

            int process_id;
            cin >> process_id;

            cout << "Size of process " << process_id << " : ";

            int process;
            cin >> process;

            bool is_valid = true;

            for(int i = 0; i < partitions.size(); i++)
            {
                if(partitions[i].process_id == process_id)
                {
                    is_valid = false;
                    cout << "\nProcess " << process_id << " has already been allocated\n";
                    break;
                }
            }

            if(!is_valid)
            {
                continue;
            }
            
            partition new_partition;
            new_partition.process_id = process_id;

            int position = -1;
            int start;
            int end;

            int current_fit_size = total_memory;

            for(int i = 0; i < partitions.size(); i++)
            {
                if(i == 0)
                {
                    start = 0;
                    end = partitions[i].start;

                }
                else {
                    start = partitions[i - 1].end;
                    end = partitions[i].start;
                }

                if(end - start >= process)
                {
                    if(end - start < current_fit_size)
                    {
                        position = i;
                        new_partition.start = start;
                        new_partition.end = new_partition.start + process;
                        current_fit_size = end - start;
                    }
                }

                if(i == partitions.size() - 1)
                {
                    start = partitions[partitions.size() - 1].end;
                    end = total_memory;

                    if(end - start >= process)
                    {
                        if(end - start < current_fit_size)
                        {
                            position = i + 1;
                            new_partition.start = start;
                            new_partition.end = new_partition.start + process;
                            current_fit_size = end - start;
                        }
                    }
                }
            }

            if(partitions.size() == 0)
            {
                start = 0;
                end = total_memory;

                if(end - start >= process)
                {
                    position = partitions.size();
                    new_partition.start = start;
                    new_partition.end = new_partition.start + process;
                    current_fit_size = end - start;
                }
            }

            if(position == -1)
            {
                if(total_memory - used_memory < process)
                {
                    cout << "Memory not allocated for process " << process_id << " as only " << total_memory - used_memory << " memory are remaining\n";
                }
                else {
                    cout << "Memory not allocated for process " << process_id << " due to external fragmentation\n";
                }
            }
            else {
                cout << "Memory allocated for process " << process_id << "\n";
                partitions.insert(partitions.begin() + position, new_partition);
                used_memory += process;
                process_allocated_count++;
            }

            process_count++;
        }
        else if(choice == 2)
        {
            cout << "Process ID : ";
            int process_id;
            cin >> process_id;
            bool is_deleted = false;

            for(int i = 0; i < partitions.size(); i++)
            {
                if(partitions[i].process_id == process_id)
                {
                    used_memory -= partitions[i].end - partitions[i].start;
                    partitions.erase(partitions.begin() + i);
                    process_allocated_count--;
                    is_deleted = true;  
                    break;
                }
            }

            if(is_deleted)
            {
                cout << "Process " << process_id << " deleted\n";
                process_count--;
            }
            else {
                cout << "Process " << process_id << " does not exist\n";
            }
        }
        else if(choice == 3)
        {
            break;
        }
        else {
            cout << "Enter valid choice\n";
            continue;
        }

        print_table(partitions, total_memory);
    }
    
    print_table(partitions, total_memory);
        
    return 0;
}

