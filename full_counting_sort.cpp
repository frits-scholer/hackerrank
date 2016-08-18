#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> ar(n);
  //vector<int> counts(100,0);
  vector<string> strings(100);
  for (int i=0;i<n;i++) {
    string s;
    cin >> ar[i] >> s;
    strings[ar[i]]+= (i<n/2?"-":s) + " ";
  }
  for (int i=0;i<100;i++) {
    if (!strings[i].empty()) cout << strings[i];
  }
  cout << endl;
}
