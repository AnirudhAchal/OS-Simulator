// Mft memory management simulation Best Fit 

#include<iostream>
#include<cassert>
#include<vector>

using namespace std;

void print_menu_mft_best()
{
    cout << "\nMain Menu:\t1. Insert\t2. Delete\t3. Stop\n\n";
}

void print_partitions_mft_best(vector<int> assigned_process, vector<int> partitions_size_alloc, vector<int> partitions, int memory_block_count)
{
    cout << "\n\nPartition number\tAssigned Process\tPartition Used Mem\t Partition Total Mem\n";
    for(int i = 0; i < memory_block_count; i++)
    {
        cout << "\t" << i << "\t\t\t" << assigned_process[i] << "\t\t\t" << partitions_size_alloc[i] << "\t\t\t" << partitions[i] << "\n";
    }
    cout << "\n\n";
}

void mft_best()
{
    cout << "\nRunning MFT Best Fit\n\n";

    int total_memory;
    cout << "Enter size of total memory: ";
    cin >> total_memory;

    int partition_count;
    cout << "\nEnter the number of partitions: ";
    cin >> partition_count;

    vector<int> partitions(partition_count); // Stores the memory allocated for each partition
    vector<int> partitions_size_alloc(partition_count); // Stores the memory used in each partition
    vector<bool> partition_used(partition_count); // Stores True is partition is being used
    vector<int> assigned_process(partition_count, -1); // Stores the assigned process for a particular partition

    int used_memory = 0;
    int memory_block_count = 0;
    int max_block_size = 0;

    for(int i = 0; i < partition_count; i++)
    {
        cout << "Enter the size of partition " << i << " : ";
        cin >> partitions[i];
        
        if(used_memory + partitions[i] > total_memory) // Not enough memory
        {
            partitions[i] = 0; // Cannot allocate
            cout << "Partition " << i << " cannot be allocated memory since only " << total_memory - used_memory << " memory is remaining\n";
        }
        else {
            cout << "Partition allocated\n";
            used_memory += partitions[i];
            memory_block_count++;
        }

        max_block_size = max(max_block_size, partitions[i]);
    }

    total_memory = used_memory; 
    used_memory = 0;

    while(true)
    {
        print_menu_mft_best();
        cout << "Enter Choice: ";
        int choice;
        cin >> choice;

        cout << "\n";

        if(choice == 1)
        {
            int process;
            cout << "Enter process number: ";
            cin >> process;

            int process_size;
            cout << "Enter process size: ";
            cin >> process_size;

            bool process_allocated = false;

            for(int i = 0; i < partition_count; i++)
            {
                if(assigned_process[i] == process)
                {
                    cout << "\nProcess " << process << " already in partition " << i << "\n";
                    process_allocated = true; 
                    break;
                }
            }

            // Process already allocated
            if(process_allocated)
            {
                cout << "Process " << process << " already allocated.\n"; 
                print_partitions_mft_best(assigned_process, partitions_size_alloc, partitions, memory_block_count);
                continue;
            }

            // Process > max partition size
            if(process_size > max_block_size)
            {
                cout << "\nProcess size is greater than " << max_block_size << " (maximum partition size).\n";
                cout << "Cannot allocate any partition.\n";
                print_partitions_mft_best(assigned_process, partitions_size_alloc, partitions, memory_block_count);
                continue;
            }

            // Process > remaining_time
            int remaining_memory = total_memory - used_memory;
            if(process_size > remaining_memory)
            {
                cout << "\nProcess size is greater than " << remaining_memory << " (remaining memory).\n";
                cout << "Cannot allocate, not enough memory.\n";
                print_partitions_mft_best(assigned_process, partitions_size_alloc, partitions, memory_block_count);
                continue;
            }

            bool internal_frag = false;

            // Find the smallest partition that can fit the ith process
            int min_partition = -1;
            for(int i = 0; i < partition_count; i++)
            {
                if(partition_used[i])
                {
                    if(partitions[i] - partitions_size_alloc[i] >= process_size)
                    {
                        internal_frag = true;
                    }
                    continue;
                }

                if(partitions[i] >= process_size && (min_partition == -1 || partitions[i] < partitions[min_partition]))
                {
                    min_partition = i;
                }
            }


            if(min_partition != -1)
            {
                cout << "\nProcess " << process << " is at partition " << min_partition + 1 << "\n";
                partition_used[min_partition] = true;
                partitions_size_alloc[min_partition] = process_size;
                assigned_process[min_partition] = process;
                used_memory += partitions_size_alloc[min_partition];
                print_partitions_mft_best(assigned_process, partitions_size_alloc, partitions, memory_block_count);
                continue;
            }

            if(min_partition == -1) // There was no valid partition
            {
                cout << "\nNo valid partition found for process " << process << " ";

                if(internal_frag)
                {
                    cout << "due to internal fragmentation\n";
                }
                else {
                    cout << "due to external fragmentation\n";
                }
            }
        }
        else if(choice == 2)
        {
            int process;
            cout << "Enter process: ";
            cin >> process;

            int partition = -1;
            for(int i = 0; i < partition_count; i++)
            {
                if(assigned_process[i] == process)
                {
                    partition = i;
                    break;
                }
            }

            if(partition == -1)
            {
                cout << "Enter valid process\n";
                print_partitions_mft_best(assigned_process, partitions_size_alloc, partitions, memory_block_count);
                continue;
            }

            if(partition >= partition_count)
            {
                cout << "Please enter valid partition (0 - " << partition - 1 << ").\n";
                continue;
            }

            used_memory -= partitions_size_alloc[partition];
            partition_used[partition] = false;
            partitions_size_alloc[partition] = 0;
            assigned_process[partition] = -1;
        }
        else if(choice == 3)
        {
            break;
        }
        else {
            cout << "Enter valid choice\n";
            continue;
        }

        print_partitions_mft_best(assigned_process, partitions_size_alloc, partitions, memory_block_count);
    }
}

