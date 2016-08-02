#include <iostream>
#include <utility>
#include <algorithm>
#include <set>
using namespace std;

int main() {
  long q;
  cin >> q;
  for (long iq=0;iq<q;iq++) {
    long n;//2<=n<=10^5
    long long m;//1<=m<=10^14
    cin >> n >> m;
    long long A[n+1];
    A[0]=0;
    set<long long> accs;
    for (auto j=1;j<=n;j++) cin >> A[j];
    long long acc[n+1];
    A[1] %= m;
    long long Smax = A[1];
    acc[0]=0;
    acc[1]=A[1];
    long long maxSij;
    accs.insert(m-acc[1]);
    for (long j=2;j<=n;j++) {
      A[j] %= m;
      acc[j]=(acc[j-1]+A[j])%m;
      //find delta the m-min(acc[i-1]) such that acc[i-1] > acc[j] 1<=i<j
      long long delta = 0;
      auto it = accs.lower_bound(m-acc[j]);
      if (it != accs.begin()) delta = *--it;
      maxSij = max((acc[j]+delta)%m, acc[j]);
      accs.insert(m-acc[j]);
      if (maxSij>Smax) Smax = maxSij;
    }
    cout << Smax << endl;
  }
}
