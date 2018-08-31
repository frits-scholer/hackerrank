#include <iostream>
#include <deque> 
#include <algorithm> 
using namespace std;

void printKMax(int arr[], int n, int k){
  /*
make a deque of size k
determine the max
pop front and  push on the back
*/
  deque<int> dq(arr, arr+k);
  int cur_max = *max_element(begin(dq), end(dq));
  cout << cur_max << ' ';
  for (int i=k;i<n;i++) {//skipped if k=n
    dq.push_back(arr[i]);
    if (arr[i] > cur_max) cur_max = arr[i];
    else if (dq.front() == cur_max) cur_max = *max_element(begin(dq)+1, end(dq));
    dq.pop_front();
    cout << cur_max << ' ';
  }
  cout << endl;
}

int main(){
  
	int t;
	cin >> t;
	while(t>0) {
		int n,k;
		cin >> n >> k;
		int i;
		int arr[n];
		for(i=0;i<n;i++)
		cin >> arr[i];
		printKMax(arr, n, k);
		t--;
  	}
  	return 0;
}
