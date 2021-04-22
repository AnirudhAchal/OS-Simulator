#include<bits/stdc++.h>

int preset_or_not_fifo(int table_f[], int nframe, int page_is_here) //to check if page is present or not
{
	for(int i=0; i<nframe; i++)
		if(page_is_here == table_f[i])
			return 1;
	return 0;
}

void printing_fifo(int table_f[], int nframe) //to print status of table at each stage
{
	for(int i=0; i<nframe; i++)
	{
		if(table_f[i] == -1)
			printf("-- ");
		else
			printf("%2d ", table_f[i]);
	}
	printf("||");
} 

void fifo()
{
    printf("\nRunning Page Replacement FIFO\n\n");

    int n,nf,i,position_noted=0;
    float d;
    printf("******* FIFO ********\n");
    printf("Please enter number of frames:\n");
    scanf("%d",&nf);
    int table_frame[nf];
    for(i=0;i<nf;i++)
    {
        table_frame[i]=-1;
    }

    printf("\nEnter total number of page requests please:\n");
    scanf("%d",&n);
    int pages[n];
    printf("\nPlease enter pages here:\n\n");
    for(i=0;i<n;i++)
    {
        printf("Enter page request : ");
        scanf("%d",&pages[i]);
    }

    int count_tracker=0;
    printf("\nPosition of the frame table after each request is as follows:\n");
    for(i=0;i<n;i++)
    {
        printf("\nCurrent status of frames after page request from %2d || ",pages[i]);
        if(!preset_or_not_fifo(table_frame,nf,pages[i]))
        {
             
             table_frame[position_noted]=pages[i];
               position_noted = (position_noted+1)%nf ;//considering it as a queue here
             printing_fifo(table_frame,nf);
             printf(" page fault!\n");
             count_tracker++; //incrementing the value if page fault found
             continue;
        }
        printing_fifo(table_frame,nf);
		printf("\n");

    }
    d=count_tracker/(n*1.0);
    printf("\nNumber of page faults : %d\n\n", count_tracker);
   
    printf("The Page Fault ratio is: %f\n\n ",d);
    printf("THANK YOU...Exiting!\n");
    printf("**************************\n");
}
