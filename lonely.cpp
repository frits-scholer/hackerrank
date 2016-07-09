#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

int lonelyinteger(vector < int > a) {
  sort(a.begin(), a.end());
  auto it=a.begin();
  while(it < (a.end()-1) && ((*it) == *(it+1))) {it+=2;}
  return *it;
}

int main() {
    int res;
    int _a_size;
    cin >> _a_size;
    vector<int> _a;
    int _a_item;
    for(int _a_i=0; _a_i<_a_size; _a_i++) {
        cin >> _a_item;
        _a.push_back(_a_item);
    }
    res = lonelyinteger(_a);
    cout << res << endl;;
}
