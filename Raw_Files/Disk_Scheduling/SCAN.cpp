/*
Abhishek Singh (191CS103)

SCAN Disk Scheduling algorithm
*/
#include <bits/stdc++.h>
using namespace std;


class scanalgo{
private:
    void SCAN(int n,int arr[],int head,string direction,int disk_size);

public:
    void solve();
};

//function to facilitate SCAN algorithm
void scanalgo::SCAN(int n,int arr[], int head, string direction,int disk_size)
{
	int total_count = 0;        //to count number of seek operations
	int distance, current;
	vector<int> left, right;   //to hold the tracks left and right to the initial R/W head position
	vector<int> sequence; //Sequence in which requests are executed
    sequence.push_back(head);
	//pushing the end values of disk
	if (direction == "left") left.push_back(0);
	else if (direction == "right") right.push_back(disk_size - 1);

	for (int i = 0; i < n; i++) {
		if (arr[i] < head) //if the value of current request is less than R/W head position
			left.push_back(arr[i]);
		if (arr[i] > head) //if the value of current request is less than R/W head position
			right.push_back(arr[i]);
	}

	//sorting the requests according to distance from current R/W head position
	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());

	//Run loop 2 times, one for left and other for right or vice-versa
	int times = 2;
	while (times--) {
            //if current direction of movement is left
		if (direction == "left") {
                //consume requests sequentially according to left vector
			for (int i = left.size() - 1; i >= 0; i--) {
				current = left[i];

				sequence.push_back(current);
				distance = abs(current - head);
				total_count += distance;

				head = current;
			}
			direction = "right";
		}
		//if current direction of movement is right
		else if (direction == "right") {
                 //consume requests sequentially according to right vector
			for (int i = 0; i < right.size(); i++) {
				current = right[i];

				sequence.push_back(current); //pushing the current request
				distance = abs(current - head);   //calculating absolute difference between current request and previous R/W head position
				total_count += distance;             //adding distance to total seek count

				head = current;                   //pointing head to current track
			}
			direction = "left";
		}
	}

	//printing the final result

	cout << "\nThe sequence of seek operations is: \n" << endl;
    int i;
	for (i = 0; i < sequence.size()-1; i++) {
		cout << sequence[i] <<" ==> ";
	}
    cout << sequence[i];
	cout << "\n\nTotal number of seek operations = "<< total_count << endl;

}


//Driver Code
void scanalgo::solve()
{
    int n,head,choice,disk_size;
	cout<<"Enter the number of requests: ";
	cin>>n;
	int arr[n];

    cout<<"\nEnter the size of the disk: ";
    cin>>disk_size;
    cout<<"\n";
	for(int i=0;i<n;i++)
    {
        cout<<"Enter the position of Request "<<i+1<<": ";
        cin>>arr[i];
    }
    cout<<"\nEnter the initial position of Read/Write Head: ";
	cin>> head;
    cout<<"\nSelect the initial direction of Read/Write Head: 1) Left 2) Right: ";
	cin>>choice;
	string direction="right";
    if(choice==1) direction="left";
	SCAN(n,arr, head, direction,disk_size);
}
int main()
{
    scanalgo s;
    s.solve();
}
