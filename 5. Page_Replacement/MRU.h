 #include<bits/stdc++.h>
int preset_or_not_mru(int table_f[], int nframe, int page_is_here) //function to check if page is present or not
{
	for(int i=0; i<nframe; i++)
		if(page_is_here == table_f[i])
			return 1;
	return 0;
}

void printing_mru(int table_f[], int nframe)  //printing_mru the table at each step
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


int find_position_here_mru(int table_f[], int nframe, int pages[], int curr, int np) //finds a suitable position
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

	int max_value = -1, retu_Position_here = -1;
	for(int i=0; i<nframe; i++)
		if(max_value < position_noted[i])
		{
			max_value = position_noted[i];
			retu_Position_here = i;
		}

	return retu_Position_here;
}

void mru()
{
    printf("\nRunning Page Replacement MRU\n\n");

    int n,nf,i,position_noted=0;
    float d;
    printf("******* MRU  ********:\n");
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
    printf("Enter pages\n\n");
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
        if(!preset_or_not_mru(table_frame,nf,pages[i]))
        {
             int position_noted = find_position_here_mru(table_frame,nf,pages,i,n);
             table_frame[position_noted]=pages[i];
             printing_mru(table_frame,nf);
             printf(" page fault!\n");
             count_tracker++; //increment the value if page fault found.
             continue;
        }
        printing_mru(table_frame,nf);
		printf("\n");

    }
    d=count_tracker/(n*1.0); //page fault ratio.
    printf("\nNumber of page faults : %d\n\n", count_tracker);
   
    printf("The Page Fault ratio is: %f\n\n ",d);
    printf("THANK YOU...Exiting!\n");
printf("*****************\n");
}
