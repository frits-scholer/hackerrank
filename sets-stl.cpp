#include <iostream>
#include <set>
#include <algorithm>
using namespace std;
int main() {
  set<int> s;
  int Q;
  cin >> Q;
  while (Q--) {
    int x, y;
    cin >> y >> x;
    switch (y) {
    case 1:
      s.insert(x);
      break;
    case 2:
      s.erase(x);
      break;
    case 3:
      auto it = s.find(x);
      if (it == s.end()) cout << "No" << endl;
      else cout << "Yes" << endl;
      break;
    }
  }
}
