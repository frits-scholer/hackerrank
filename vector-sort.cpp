#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
  int N;
  cin >> N;
  vector<int> v(N);
  for (int i=0;i<N;i++) cin >> v[i];
  sort(begin(v), end(v));
  for (int i=0;i<N;i++) cout << v[i] << ' ';
  cout << endl;
}
