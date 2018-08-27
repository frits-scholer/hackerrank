#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
  int N;
  cin >> N;
  vector<int> v(N);
  for (int i=0;i<N;i++) cin >> v[i];
  int Q;
  cin >> Q;
  while (Q--) {
    int x;
    cin >> x;
    auto it = lower_bound(begin(v), end(v), x);
    if (*it == x) cout << "Yes ";
    else cout << "No ";
    cout << distance(v.begin(), it)+1 << endl;
  }
  cout << endl;
}
