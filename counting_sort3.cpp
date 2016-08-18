#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
  size_t n;
  cin >> n;
  vector<int> ar(n);
  vector<int> counts(100,0);
  for (auto& a: ar) {
    string s;
    cin >> a >> s;
    counts[a]++;
  }
  size_t S=0;
  for (int i=0;i<100;i++) {
    while (counts[i]>0) {S++;counts[i]--;}
    cout << S << ' ';
  }
  cout << endl;
}
