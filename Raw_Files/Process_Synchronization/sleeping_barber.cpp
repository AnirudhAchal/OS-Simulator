#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

class Customer{
public:
  int id;
  float at, bt, ct;
  int flag;
}*c;

int total_time = 0;
sem_t mutex;


int i = -1, n, chairs_wait;

void* thread1(void *arg){
  i++;
  sem_wait(&mutex);

  // cs
  cout << "At t = " << total_time << " , barber has started cutting hair of customer " << i<< endl;

  while(c[i].bt != 0){
    while(c[i].flag == 3) i++;
    c[i].flag = 2;
    total_time++;
    c[i].bt--;
    for(int x = 0; x < n; x++){
      if(c[x].flag == 0){
        if(total_time == c[x].at){
          if(chairs_wait > 0){
            chairs_wait--;
            c[x].flag = 1;
            cout << "At t = " << total_time << " ,customer " << x << " took a waiting seat" << endl;
          }
          else{
            c[x].flag = 3;
            cout << "At t = " << total_time << " ,customer " << x << " left shaking his head " << endl;
          }
        }
      }
    }
  }
  cout << "At t = " << total_time << ", barber was finished with customer " << i << endl;
  for(int j = 0; j < n; j++){
    if(c[j].flag == 1){
      chairs_wait++;
      break;
    }
  }
  // End of CS
  sem_post(&mutex);
}

int main(){
  sem_init(&mutex, 0, 1);
  cout << "Number of customer waiting: ";
  cin >> n;
  cout << "Number of waiting chairs: ";
  cin >> chairs_wait;
  c = new Customer[n];
  cout << "Enter customer id, at and bt: " << endl;
  for(int i = 0; i < n; i++){
    cout << "Customer id: ";
    cin >> c[i].id;
    cout << "AT: ";
    cin >> c[i].at;
    cout << "BT: ";
    cin >> c[i].bt;
    c[i].flag = 0;
  }
  sort(c, c+n, [](const Customer& lhs, const Customer&rhs){
    return lhs.at < rhs.at;
  }); // sort customers based on at
  pthread_t t_c[n];
  c[0].flag = 1;
  int flag1 = 0;
  total_time = c[0].at;
  for(int x = 0; x < n; x++){
    if(c[x].flag == 1){
      flag1 = 1;
      pthread_create(&t_c[x], NULL, thread1, NULL);
      pthread_join(t_c[x], NULL);
    }
    if(flag1 == 0){
      for(int y = 0; y < n; y++){
        if(c[y].flag == 0){
          total_time = c[y].at;
          i = y;
          pthread_create(&t_c[x], NULL, thread1, NULL);
          pthread_join(t_c[x], NULL);
          break;
        }
      }
    }
  }
  return 0;
}
