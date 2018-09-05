#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define all(t) begin(t), end(t)
#define fore(i, l, r) for(int i = (l); i < (r); ++i)
#define forn(i, n) fore(i, 0, n)

long equalize( int indx, vector<int>& c) {
  long r = 0;
  while (c[indx - 1] <= c[indx] - 5) {
    forn(i, indx) c[i] += 5;
    r++;
  }
  while (c[indx - 1] <= c[indx] - 2) {
    forn(i, indx) c[i] += 2;
    r++;
  }
  if (c[indx - 1] < c[indx]) {
    forn(i, indx) c[i] ++;
    r++;
  }
  return r;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N;
    vector<int> c(N);
    forn(i, N) cin >> c[i];
    sort(all(c));
    long ops = 0;
    fore(i, 1, N) ops += equalize(i, c);
    cout << ops << endl;
  }
}
  
