#include <iostream>
#include <map>
#include <string>
using namespace std;
int main() {
  map<string, int> m;
  int Q;
  cin >> Q;
  while (Q--) {
    int t, y;
    cin >> t;
    string x;
    switch (t) {
    case 1:
      cin >> x >> y;
      m[x] += y;
      //m.insert(pair<string,int>(x,y));
      break;
    case 2:
      cin >> x;
      m.erase(x);	  
      break;
    case 3:
      cin >> x;
      auto it = m.find(x);
      if (it == m.end()) cout << 0 << endl;
      else cout << m[x] << endl;
      break;
    }
  }
}
