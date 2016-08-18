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
  for (int i=0;i<100;i++) while (counts[i]>0) {cout << i << ' ';counts[i]--;}
  cout << endl;
}
