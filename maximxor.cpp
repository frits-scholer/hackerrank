#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

int maxXor(int l, int r) {
  int max=0;
  for (int i=l;i<=r;++i)
    for (int j=i;j<=r;++j) {
      int k = i^j;
      if( k > max) max = k;
    }
  return max;
}

int main() {
    int res;
    int _l;
    cin >> _l;
    
    int _r;
    cin >> _r;
    
    res = maxXor(_l, _r);
    cout << res << endl;
    
    return 0;
}
