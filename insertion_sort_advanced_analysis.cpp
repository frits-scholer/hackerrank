/*
insertion sort analysis
ki is the number of elements over which ith element of array has to shift
find sum of ki
1<=T<=15
1<=N<=100000
1<=a[i]<=10000000
count the number of inversions
 */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long nr_of_inversions(const vector<long>& v) {
  long S=0;
  for (size_t i=1;i<v.size();i++) {
    for (size_t j=0;j<i;j++) {
      if (v[i]<v[j]) S++;
    }
  }
  return S;
}

int main() {
clock_t tm=clock();
  //input
  int T;
  cin >> T;
  for (int i=0;i<T;i++) {
    size_t N;
    cin >> N;
    vector<long> a(N);
    for (size_t j=0;j<N;j++) cin >> a[j];
    long S = nr_of_inversions(a);
    cout << S << endl;
  }
tm = clock()-tm;
cerr << (double) tm/CLOCKS_PER_SEC << " s" << endl;
}


