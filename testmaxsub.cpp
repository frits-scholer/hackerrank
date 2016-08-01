#include <iostream>
#include <utility>
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
    for (auto j=1;j<=n;j++) cin >> A[j];
    /*
maxSij = max ((acc[j]-acc[i-1]%m)
if acc[i-1] <= acc[j] maxSij = acc[j] (-min(acc[i-1]) which is 0)
if acc[i-1] > acc[j] maxSij = acc[j]+m-min(acc[i-1])
     */    
    long long acc[n+1];
    long long Smax = A[1]%m;
    acc[0]=0;
    acc[1]=A[1]%m;
    long long maxSij = acc[1];
    for (long j=2;j<=n;j++) {
      A[j] %= m;
      acc[j]=(acc[j-1]+A[j])%m;
      //find delta the m-min(acc[i-1]) such that acc[i-1] > acc[j] 1<=i<j
      long long delta = 0;
      maxSij = acc[j]+delta;
      if (maxSij>Smax) Smax = maxSij;
    }
    cout << Smax << endl;
  }
}
