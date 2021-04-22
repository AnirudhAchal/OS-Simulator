#include<bits/stdc++.h>
using namespace std;

class Process{
public:
  int id;
  float at, bt;
  int flag = 0;
} *p;

int main(){
  int n, process_completed = 0;
  cout << "Number of philosophers : ";
  cin >> n;
  p = new Process[n];
  cout << "Enter at and bt of each philosopher: " << endl;
  for(int i = 0; i < n; i++){
    p[i].id = i+1;
    cout << i+1 << enld;
    cout << "at: ";
    cin >> p[i].at;
    cout << "bt: ";
    cin >> p[i].bt;
  }
  sort(p, p+n, [](const Processr& lhs, const Process&rhs){
    return lhs.at < rhs.at;
  });
  int forks[n];
  for(int i = 0; i < n; i++) forks[i] = 0;
  while(process_completed < n){
    cout << "At t = " << total_time << endl;
    for(int i = 0; i < n; i++){
      if(p[i].flag == 1){
        if(p[i].bt > 0){
          cout << "Person " << p[i].id << "is consuming";
        }
        else{
          p[i].flag = 2;
          if(p[i].id == 1){
            forks[p[i].id-1] = 0;
            forks[n-1] = 0;
          }
          else{
            forks[p[i].id-1] = 0;
            forks[p[i].id-2] = 0;
          }
          cout << "Persons " << p[i].id << "finished consuming " << endl;
          process_completed++;
        }
        p[i].bt--;
      }
    }
    for(int i=0;i<n;i++)   {
        if(p[i].flag==0) {
            if(p[i].AT<=tot_time) {
                if(p[i].id==1) {
                    if(forks[0]==0&&forks[n-1]==0) {
                        cout<<"Person "<<p[i].id<<" has started consuming "<<endl;
                        p[i].flag=1;
                        forks[0]=1;
                        forks[n-1]=1;

                        if(p[i].BT==0)
                        {
                            p[i].flag=2;
                            forks[0]=0;
                            forks[n-1]=0;
                            cout<<"Person "<<p[i].id<<" has finished consuming "<<endl;
                            process_complete++;

                        }
                        p[i].BT--;
                    }
                    else
                    {
                        cout<<"Person "<<p[i].id<<" is waiting"<<endl;
                    }

                }
                else
                {
                    if(forks[p[i].id-1]==0&&forks[p[i].id-2]==0)
                    {
                        cout<<"Person "<<p[i].id<<" has started consuming "<<endl;
                        p[i].flag=1;
                        forks[p[i].id-1]=1;
                        forks[p[i].id-2]=1;

                        if(p[i].BT==0)
                        {
                            p[i].flag=2;
                            forks[p[i].id-1]=0;
                            forks[p[i].id-2]=0;
                            process_complete++;
                        }
                        p[i].BT--;
                    }
                    else
                    {
                        cout<<"Person "<<p[i].id<<" is waiting"<<endl;
                    }
                }
            }
        }
      }
  }
}
