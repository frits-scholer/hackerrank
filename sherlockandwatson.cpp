/*
input:
N-size of array, k nr of right rotations, q nr of queries
n space separated integers
q lines with index m
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
void rotate_right(vector<long>& v, long k) {
  rotate(v.rbegin(), v.rbegin() + k%v.size(), v.rend());
}

int main(){
  //input
  long N, k;
  int q;
  cin >> N >> k >> q;
  vector<long> A(N);
  for (auto& i : A) cin >> i;
  vector<long> m(q);
  for (auto& i : m) cin >> i;
  for (auto i : m) cout << A[i] << endl;//debug
  cout << endl;//debug
  rotate_right(A, k);
  for (auto i : m) cout << A[i] << endl;
}
