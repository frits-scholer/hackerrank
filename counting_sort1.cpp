#include <iostream>
#include <vector>
using namespace std;

int main() {
  size_t n;
  cin >> n;
  vector<int> ar(n);
  vector<int> counts(100,0);
  for (auto& a: ar) {
    cin >> a;
    counts[a]++;
  }
  for (auto c: counts) cout << c << ' ';
  cout << endl;
}
