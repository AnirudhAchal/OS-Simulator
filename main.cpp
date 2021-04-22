// CPU Scheduling
#include "1. CPU_Scheduling/FCFS.h"
#include "1. CPU_Scheduling/SJF.h"
#include "1. CPU_Scheduling/LJF.h"
#include "1. CPU_Scheduling/SRTF.h"
#include "1. CPU_Scheduling/LRTF.h"
#include "1. CPU_Scheduling/round_robin.h"
#include "1. CPU_Scheduling/HRRN.h"
#include "1. CPU_Scheduling/nonpreemptive_priority.h"
#include "1. CPU_Scheduling/preemptive_priority.h"

// Process Synchronization
#include "2. Process_Synchronization/Producer_Consumer.h"
#include "2. Process_Synchronization/Readers_priority.h"
#include "2. Process_Synchronization/Writers_priority.h"


// Resource Allocation Deadlock
#include "3. Resource_Allocation_Deadlock/bankers.h"

// Memory Management
#include "4. Memory_Management/mft_best.h"
#include "4. Memory_Management/mft_first.h"
#include "4. Memory_Management/mft_worst.h"
#include "4. Memory_Management/mvt_best.h"
#include "4. Memory_Management/mvt_first.h"
#include "4. Memory_Management/mvt_worst.h"

// Page Replacement
#include "5. Page_Replacement/FIFO.h"
#include "5. Page_Replacement/LRU.h"
#include "5. Page_Replacement/MRU.h"

// Disk Scheduling
#include "6. Disk_Scheduling/FCFS.h"
#include "6. Disk_Scheduling/SCAN.h"
#include "6. Disk_Scheduling/CSCAN.h"
#include "6. Disk_Scheduling/LOOK.h"
#include "6. Disk_Scheduling/CLOOK.h"
#include "6. Disk_Scheduling/SSTF.h"

using namespace std;

void print_menu()
{
    cout << "\nMain Menu\n";
    cout << "1. CPU Scheduling\n";
    cout << "2. Process Synchronization\n";
    cout << "3. Resource Allocation Deadlock\n";
    cout << "4. Memory Management\n";
    cout << "5. Page Replacement\n";
    cout << "6. Disk Scheduling\n";
    cout << "Enter any other key to exit.\n\n";
}

void print_menu_CPU_scheduling()
{
    cout << "\nCPU Scheduling Main Menu\n";
    cout << "1. FCFS\n";
    cout << "2. SJF\n";
    cout << "3. LJF\n";
    cout << "4. SRTF\n";
    cout << "5. LRTF\n";
    cout << "6. Round Robin\n";
    cout << "7. HRRN\n";
    cout << "8. Non-preemptive Priority\n";
    cout << "9. Preemptive Priority\n";
    cout << "Enter any other key to return to main menu\n\n";
}

void print_menu_process_synchronization()
{
    cout << "\nProcess Synchronization Main Menu\n";
    cout << "1. Producer Consumer\n";
    cout << "2. Readers Priority\n";
    cout << "3. Writers Priority\n";
    cout << "Enter any other key to return to main menu\n\n";
}

void print_menu_bankers()
{
    cout << "\nResource Allocation Deadlock Main Menu\n";
    cout << "1. Bankers Algorithm\n";
    cout << "Enter any other key to return to main menu\n\n";
}

void print_menu_page_replacement()
{
    cout << "\nPage Replacement Main Menu\n";
    cout << "1. FIFO\n";
    cout << "2. LRU\n";
    cout << "3. MRU\n";
    cout << "Enter any other key to return to main menu\n\n";
}

void print_menu_disk_scheduling()
{
    cout << "\nDisk Scheduling Main Menu\n";
    cout << "1. FCFS\n";
    cout << "2. SCAN\n";
    cout << "3. CSCAN\n";
    cout << "4. LOOK\n";
    cout << "5. CLOOK\n";
    cout << "6. SSTF\n";
    cout << "Enter any other key to return to main menu\n\n";
}

void print_menu_memory_management()
{
    cout << "\nMemory Management Main Menu\n";
    cout << "1. MFT\n";
    cout << "2. MVT\n";
    cout << "Enter any other key to return to main menu\n\n";
}

void print_submenu_memory_management(string type)
{
    cout << "\n";
    cout << "1. " << type << " Best Fit\n";
    cout << "2. " << type << " First Fit\n";
    cout << "3. " << type << " Worst Fit\n";
    cout << "Enter any other key to return to main menu\n\n";
}

int main()
{
    while(true)
    {
        print_menu();

        cout << "Enter the algorithm category: ";
        int choice;
        cin >> choice;
        cout << "\n";

        if(choice == 1)
        {
            print_menu_CPU_scheduling();
            cout << "Enter choice: ";
            cin >> choice;

            if (choice == 1) fcfs_cpu();
            else if(choice == 2) sjf();
            else if (choice == 3) ljf();
            else if (choice == 4) srtf();
            else if (choice == 5) lrtf();
            else if (choice == 6) rr();
            else if (choice == 7) hrrn();
            else if (choice == 8) nonpreemptive_priority();
            else if (choice == 9) preemptive_priority();
            else continue;
        }
        else if(choice == 2)
        {
            print_menu_process_synchronization();
            cout << "Enter choice: ";
            cin >> choice;

            if(choice == 1) producer_consumer();
            else if (choice == 2) readers_priority();
            else if (choice == 3) writers_priority();
            else continue;
        }
        else if(choice == 3)
        {
            print_menu_bankers();
            cout << "Enter choice: ";
            cin >> choice;

            if(choice == 1) bankers();
            else continue;
        }
        else if(choice == 4)
        {
            print_menu_memory_management();
            cout << "Enter choice: ";
            cin >> choice;

            if(choice == 1)
            {
                print_submenu_memory_management("MFT");
                cout << "Enter choice: ";
                cin >> choice;

                if(choice == 1) mft_best();
                else if(choice == 2) mft_first();
                else if(choice == 3) mft_worst();
                else continue;
            }
            else if(choice == 2)
            {
                print_submenu_memory_management("MVT");
                cout << "Enter choice: ";
                cin >> choice;

                if(choice == 1) mvt_best();
                else if(choice == 2) mvt_first();
                else if(choice == 3) mvt_worst();
                else continue;
            }
            else {
                continue;
            }
        }
        else if(choice == 5)
        {
            print_menu_page_replacement();
            cout << "Enter choice: ";
            cin >> choice;

            if(choice == 1) fifo();
            else if (choice == 2) lru();
            else if (choice == 3) mru();
            else continue;
        }
        else if(choice == 6)
        {
            print_menu_disk_scheduling();
            cout << "Enter choice: ";
            cin >> choice;

            if(choice == 1) fcfs();
            else if(choice == 2) scan();
            else if(choice == 3) cscan();
            else if(choice == 4) look();
            else if(choice == 5) clook();
            else if(choice == 6) sstf();
            else continue;
        }
        else {
            cout << "\nSimulation Complete.\n\n\n";
            break;
        }
    }

    return 0;
}
