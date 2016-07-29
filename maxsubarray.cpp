#include <iostream>
#include <utility>
using namespace std;

typedef pair<long, long> subarray;
#define S(i,j,B,mod) (B[j]-B[i-1]+mod)%mod

int main() {
  long q;
  cin >> q;
  for (long i=0;i<q;i++) {
    long n;//2<=n<=10^5
    long long m;//1<=m<=10^14
    cin >> n >> m;
    long long A[n+1];
    A[0]=0;
    for (auto j=1;j<=n;j++) cin >> A[j];
    long long acc[n+1];
    subarray maxSj = make_pair(1LL,1LL);
    long long Simaxj=A[1]%m;
    long imax=1;
    acc[0]=A[0];
    acc[1]=A[1]%m;
    for (long j=2;j<=n;j++) {
      acc[j]=(acc[j-1]+A[j])%m;//beware of negatives
      long long sum = S(maxSj.first, maxSj.second, acc, m);
      if ((Simaxj + A[j])%m < A[j]%m) {
	Simaxj = 0;
	imax = j;
      }
      if ((A[j] + Simaxj)%m > sum) maxSj = make_pair(imax, j);
      Simaxj = (Simaxj + A[j])%m;
    }
    cout << S(maxSj.first, maxSj.second, acc, m) << endl;
  }
}
