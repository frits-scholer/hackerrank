#include <iostream>
#include <utility>
using namespace std;

typedef pair<long, long> subarray;
#define S(i,j,B) ((B[j]-B[i-1]+m)%m)

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
    subarray maxSj = make_pair(1L,1L);
    long long Smax = A[1]%m;
    acc[0]=A[0];
    acc[1]=A[1]%m;
    for (long j=2;j<=n;j++) {
      A[j] %= m;
      acc[j]=(acc[j-1]+A[j])%m;//beware of negatives
      for (long k=1;k<=j;k++) {
	if (S(k,j,acc)>Smax) {
	  maxSj=make_pair(k,j);
	  Smax = S(k,j,acc);
	}
      }
    }
    cout << maxSj.first << ", " <<  maxSj.second << " => ";
    cout << Smax << endl;
  }
}
