// CPU Scheduling : SJF

#include<iostream>
#include<iomanip>

using namespace std;
void sjf()
{
    cout << "\nRunning CPU Scheduling SJF\n\n";
    printf("******* SJF ********\n\n");

      int n,temp,tt=0,min,d,i,j;
      float atat=0,awt=0,stat=0,swt=0;

      cout<<"Enter no of process : ";
      cin>>n;
      int a[n],b[n],e[n],tat[n],wt[n];
  
      for(i=0;i<n;i++)
      {
            cout<<"Enter arival time : ";       //input
            cin>>a[i];
      }
      for(i=0;i<n;i++)
      {
            cout<<"Enter brust time : ";      //input
            cin>>b[i];
      }
      for(i=0;i<n;i++)
      {
         for(j=i+1;j<n;j++)
          {
                if(b[i]>b[j])
                {
                      temp=a[i];
                      a[i]=a[j];
                      a[j]=temp;

                      temp=b[i];
                      b[i]=b[j];
                      b[j]=temp;
                }
          }
      }
      min=a[0];
      for(i=0;i<n;i++)
      {
            if(min>a[i])
            {
                  min=a[i];
                  d=i;
            }
      }
      tt=min;
      e[d]=tt+b[d];
      tt=e[d];

      for(i=0;i<n;i++)
      {
            if(a[i]!=min)
            {
                  e[i]=b[i]+tt;
                  tt=e[i];
            }
      }
      for(i=0;i<n;i++)
      {

            tat[i]=e[i]-a[i];
            stat=stat+tat[i];
            wt[i]=tat[i]-b[i];
            swt=swt+wt[i];
      }
      atat=stat/n;
      awt=swt/n;
//       cout<<"Process  Arrival-time(s)  Burst-time(s)  Waiting-time(s)  Turnaround-time(s)\n";

//     for(i=0;i<n;i++)
//     {
//     cout<<"P"<<i+1<<"              "<<a[i]<<"                "<<b[i]<<"                  "<<wt[i]<<"               "<<tat[i]<<endl;
//     }

//     cout<<"awt="<<awt<<" atat="<<atat;  //average waiting time and turn around time
  
      cout << "\nFinal timing results: " << endl;
      cout << "--------------------- \n" << endl;
      cout << setw(13) << left << "Process No" << setw(10) << left << "AT" << setw(10) << left << "BT" << setw(10) << left << "CT" << setw(10) << left << "TAT" << setw(10) << left << "WT" << endl;
      cout << setw(13) << left << "----------" << setw(10) << left << "--" << setw(10) << left << "--" << setw(10) << left << "--" << setw(10) << left << "---" << setw(10) << left << "--" << endl;
      for(int i=0; i<n ; i++)
      {
        cout << setw(13) << left << i+1 << setw(10) << left << a[i] << setw(10) << left << b[i] << setw(10) << left << tat[i]+a[i] << setw(10) << left << tat[i] << setw(10) << left << wt[i] << endl;
      }
      cout<<"\nAverage TurnAround Time : "<<atat<<endl;
      cout<<"Average Waiting Time      : "<<awt<<endl;
    printf("\n******* DONE ********\n");
}
