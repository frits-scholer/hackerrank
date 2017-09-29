#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;

#define all(t) begin(t), end(t)
#define sp << " " <<
#define X first
#define Y second
#define fore(i, l, r) for(int i = (l); i < (r); ++i)
#define forn(i, n) fore(i, 0, n)
#define fori(i, l, r) fore(i, l, (r) + 1)

typedef pair<int,int> pt;
const int mod = 1000000007;

int modpow(int a, int b){
    int ans = 1 % mod;
    while(b){
        if(b & 1)
            ans = (ans * 1LL * a) % mod;
        a = (a * 1LL * a) % mod;
        b >>= 1;
    }
    return ans;
}

int main() {
  int n;
  cin >> n;
  vector<pt> roads(n-1);
  vector<int> deg(n+1,0);
  forn(i, n-1) {
    cin >> roads[i].X >> roads[i].Y;
    deg[roads[i].X]++;
    deg[roads[i].Y]++;
  }
  //  fori(i, 1, n) cout << i sp deg[i] << endl;
  long x = 0;
  for (auto e:roads) if (deg[e.X]>1 && deg[e.Y]>1) x++;
  cout << modpow(2, x+1) << endl;  
}
