 #include<bits/stdc++.h>
int present_or_not(int table_f[], int nframe, int page_is_here) //function to check if page is present or not
{
	for(int i=0; i<nframe; i++)
		if(page_is_here == table_f[i])
			return 1;
	return 0;
}

void printing(int table_f[], int nframe)  //printing the table at each step
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


int find_position_here(int table_f[], int nframe, int pages[], int curr, int np) //finds a suitable position
{
	for(int i=0; i<nframe; i++)
		if(table_f[i] == -1)
			return i;

	int position_noted[nframe] = {0};
	for(int i=0; i<nframe; i++)
	{
		position_noted[i] = -1;
		for(int j=curr-1; j>=0; j--)
			if(pages[j] == table_f[i])
			{
				position_noted[i] = j;
				break;
			}
	}

	int min_value = 1000, retu_Position_here = -1;
	for(int i=0; i<nframe; i++)
		if(min_value > position_noted[i])
		{
			min_value = position_noted[i];
			retu_Position_here = i;
		}

	return retu_Position_here;
}

int main()
{
    int n,nf,i,position_noted=0;
    float d;
    printf("******* 191CS102 ********:\n");
    printf("******* LRU  ********:\n");
    printf(" Please enter number of frames:\n");
    scanf("%d",&nf);
    int table_frame[nf];
    for(i=0;i<nf;i++)
    {
        table_frame[i]=-1;
    }

    printf("enter total number of page requests please:\n");
    scanf("%d",&n);
    int pages[n];
    printf("enter pages\n");
    for(i=0;i<n;i++)
    {
        scanf("%d",&pages[i]);
    }

    int count_tracker=0;
    printf("position of the frame table after each request is as follows:\n");
    for(i=0;i<n;i++)
    {
        printf("page table after request from %2d || ",pages[i]);
        if(!present_or_not(table_frame,nf,pages[i]))
        {
             int position_noted = find_position_here(table_frame,nf,pages,i,n);
             table_frame[position_noted]=pages[i];

             printing(table_frame,nf);
             printf("page fault!\n");
             count_tracker++; //increment the value if page fault found.
             continue;
        }
        printing(table_frame,nf);
		printf("\n");

    }
    d=count_tracker/(n*1.0); //page fault ratio.
    printf("\nNumber of page faults : %d\n\n", count_tracker);
   
    printf("The Page Fault ratio is: %f\n\n ",d);
    printf("THANK YOU...Exiting!\n");
printf("*****************\n");
}