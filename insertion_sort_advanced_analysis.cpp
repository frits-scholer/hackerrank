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

long mrge(vector<long>& v, size_t l, size_t m, size_t r)
{
  size_t len=r-l+1;
  size_t count = 0;
  vector<long> c(len);
  size_t i=0;
  size_t j=l;
  size_t k=m;
  while(j<m && k<=r) {
    if(v[j]<=v[k]) {
      c[i++]=v[j++];
    }
    else {
      c[i++]=v[k++];
      count+=m-j;
    }
  }
 
  while(j<m) {
    c[i++]=v[j++];
  }
  while(k<=r) {
    c[i++]=v[k++];
  }
  i=0;
  while(l<=r) {
    v[l++]=c[i++];
  }
  return count;
}

long mergesort(vector<long>& v,size_t l,size_t r)
{
  long count=0;
  size_t m=(l+r)/2;
  if(l<r) {
      count+=mergesort(v,l,m);
      count+=mergesort(v,m+1,r);
      count+=mrge(v,l,m+1,r);
  }
  return count;
}

long nr_of_inversions(vector<long>& v, size_t n) {
  return mergesort(v,0,n);
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
    long S = nr_of_inversions(a, N-1);
    cout << S << endl;
  }
tm = clock()-tm;
cerr << (double) tm/CLOCKS_PER_SEC << " s" << endl;
}


