#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
typedef vector<int>::iterator vi;

void printA(vector<int>& A) {
  for (auto a: A) cout << a << " ";
  cout << endl;
}

vi partition(vi lo, vi hi){
  vi pivot = hi;
  vi i = lo;        // place for swapping
  for (vi j = lo; j < hi; j++) {
    if (*j <=  *pivot) {
      swap(*i,*j);
      i++;
    }
  }
  swap(*i,*hi);
  return i;
}

void quicksort( vector<int>& A, vi lo, vi hi) {
  if (lo < hi) {
    vi p = partition(lo, hi);
    printA(A);
    quicksort(A, lo, p - 1);
    quicksort(A, p + 1, hi);
 }
}

int main()
{
    int n;
    cin >> n;

    vector <int> arr(n);
    for(int i = 0; i < (int)n; ++i) {
        cin >> arr[i];
    }

    quicksort(arr, begin(arr), --end(arr));

    return 0;
}
