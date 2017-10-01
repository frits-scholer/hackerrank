#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define all(t) begin(t), end(t)
#define fore(i, l, r) for(int i = (l); i < (r); ++i)
#define forn(i, n) fore(i, 0, n)

int main()
{
  int T;
  cin >> T;
  while(T--) {
    int N;
    cin >> N;
    vector<int> c(N);
    int ops1(0), ops2(0), ops3(0);
    int minimum(10000);
    int rest;
    forn(i, N) {
      cin >> c[i];
      if(minimum > c[i]) minimum = c[i];
    }
    forn(i, N) {
      rest = c[i] - minimum;
      ops1 += rest / 5;
      rest %= 5;
      ops1 += rest / 2;
      rest %= 2;
      ops1 += rest;

      rest = c[i] - (minimum - 1);
      ops2 += rest / 5;
      rest %= 5;
      ops2 += rest / 2;
      rest %= 2;
      ops2 += rest;

      rest = c[i] - (minimum - 2);
      ops3 += rest / 5;
      rest %= 5;
      ops3 += rest / 2;
      rest %= 2;
      ops3 += rest;
    }
    cout << min(min(ops1, ops2), ops3) << endl;
  }
}


  
