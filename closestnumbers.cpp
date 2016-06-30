#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;
typedef pair<long,pair<long,long>> dif;
int main() {
  size_t N;
  cin >> N;
  long A[N];
  for (size_t i=0;i<N;i++) cin >> A[i];
  sort(A, A+N);
  //for (size_t i=0;i<N;i++) cout << A[i] << " ";
  //cout << endl;
  long D[N];
  adjacent_difference(A, A+N, D);
  dif Dplus[N-1];
  for (size_t i=1;i<N;i++) {
    Dplus[i-1]=make_pair(D[i],make_pair(A[i-1],A[i]));
  }
  sort(Dplus, Dplus+N-1);
  long min = Dplus[0].first;
  for (size_t i=0;Dplus[i].first==min;i++) {
    cout << Dplus[i].second.first << " " << Dplus[i].second.second << " ";
  }
  cout << endl;
}
  
