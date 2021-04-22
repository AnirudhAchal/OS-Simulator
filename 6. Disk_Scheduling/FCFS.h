#include<bits/stdc++.h>

void fcfs()
{
    cout << "\nRunning Disk Scheduling FCFS\n\n";

 int n,head,i,j,k,seek=0,max1,diff;
 float avg;
 printf("-------------FCFS-------------------\n");
 printf("Enter the max range of disk please:\n");
 scanf("%d",&max1);

 printf("Enter the size of queue request:\n");
 scanf("%d",&n);

 int queue[n+1];

 printf("Enter the request sequence here:\n");
 for(i=1;i<=n;i++)
 {
    scanf("%d",&queue[i]);
 }

 printf("Enter the initial head position:\n");
 scanf("%d",&head);
 queue[0]=head;

 for(j=0;j<=n-1;j++)
 {
 diff=abs(queue[j+1]-queue[j]);
 seek+=diff;
 printf("Move is from %d to %d with seek %d\n",queue[j],queue[j+1],diff);
 printf("-------------------------------------\n");
 }

 printf("Total seek time is: %d\n",seek);
 avg=seek/(float)n;

 printf("Average seek time is: %f\n",avg);
printf("-------------Thank you----------------\n");
}
