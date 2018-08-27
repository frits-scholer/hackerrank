#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
  int N;
  cin >> N;
  vector<int> v(N);
  for (int i=0;i<N;i++) cin >> v[i];
  int x;
  cin >> x;
  int a, b;
  cin >> a >> b;
  v.erase(begin(v)+x-1);
  v.erase(begin(v)+a-1, begin(v)+b-1);
  cout << v.size() << endl;
  for (auto vv : v) cout << vv << ' ';
  cout << endl;
}
