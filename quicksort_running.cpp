#include <iostream>
#include <vector>
using namespace std;

typedef vector<int>::iterator vi;

long swaps = 0;

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
      swaps++;
      i++;
    }
  }
  swap(*i,*hi);
  swaps++;
  return i;
}

void quicksort( vector<int>& A, vi lo, vi hi) {
  if (lo < hi) {
    vi p = partition(lo, hi);
    //printA(A);
    quicksort(A, lo, p - 1);
    quicksort(A, p + 1, hi);
 }
}
long insertionSort_shifts(vector<int>& v) {
  if (v.size()==1) return 0;
  else {
    unsigned long shifts = 0;
    for (unsigned int i = 1;i < v.size();++i) {
      int e = v[i];
      unsigned int j = i+1;
      while (--j > 0 && v[j-1] > e) {
      v[j] = v[j-1];
      shifts++;
      }
      v[j] = e;
    }
    return shifts;
  }
}

int main(void) {
   vector <int> ar;
   int ar_size;
   cin >> ar_size;
   for (int i=0; i < ar_size; i++) {
     int tmp;
     cin >> tmp;
     ar.push_back(tmp); 
   }
   vector<int> arr(ar_size);
   copy(begin(ar), end(ar), begin(arr));
   quicksort(arr, begin(arr), --end(arr));
   cout << insertionSort_shifts(ar) - swaps << endl;
   return 0;
}
