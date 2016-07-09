#include <vector>
#include <iostream>

using namespace std;

int main() {
  int T;
  cin >> T;
  vector<unsigned long long> N(T);
  for (int i=0;i<T;++i) cin >> N[i];
  for (int i=0;i<T;++i) {
    bool L = false;//if Louise can't play she loses
    unsigned long long n = N[i];
    while (n != 1ULL) {
      int k = 0;
      auto m = n;      
      while (m != 1) {m >>= 1ULL;k++;}
      if (n == (1ULL<<k)) n = (1ULL<<(k-1));
      else n -= (1ULL<<k);
      L = !L;
    }
    if (L) cout << "Louise";
    else cout << "Richard";
    cout << endl;
  }
}
