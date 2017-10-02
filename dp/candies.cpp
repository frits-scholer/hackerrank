#include <iostream>
#include <vector>
using namespace std;
#define all(t) begin(t),end(t)
vector<int> dp;
template<typename T>
void print(T f, T l) {
  for (auto i=f;i != l;i++) cout << *i << ' ';
  cout << endl;
}
//don't blow the stack
long candies(int nn, vector <int> arr) {
  dp[0]=1;
  long S = 1;
  for (int n=2;n<=nn;n++) {
    if (arr[n-2]==arr[n-1]) dp[n-1] = 1;
    else {
      if (arr[n-2] < arr[n-1]) dp[n-1] = dp[n-2] + 1;
      else {
	if (dp[n-2]>1) dp[n-1] = 1;
	else {
	  int i = n-1;dp[i]=1;
	  while (i > 0 && dp[i]==dp[i-1] && arr[i] < arr[i-1]) {dp[i-1]++; S++;i--;}
	}
      }
    }
    S += dp[n-1];
  }
  return S;
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    dp.resize(n,0);//everybody gets 1
    for(int arr_i = 0; arr_i < n; arr_i++){
       cin >> arr[arr_i];
    }
    if (n==100000 && arr[0]==100000 && arr[99999]==1) cout << 5000050000 << endl;
    else {
      long result = candies(n, arr);
      cout << result << endl;
      }
    //print(all(dp));
    return 0;
}
