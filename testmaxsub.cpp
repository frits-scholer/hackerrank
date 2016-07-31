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
    long long Simaxj=A[1]%m;
    long long Smax = A[1]%m;
    long imax=1;
    acc[0]=A[0];
    acc[1]=A[1]%m;
    for (long j=2;j<=n;j++) {
      A[j] %= m;
      acc[j]=(acc[j-1]+A[j])%m;//beware of negatives
      //assume Simaxj is determined
      if (Simaxj + A[j] >= m) {//determine imax and Simaxj
	Simaxj = A[j];
	imax = j;
      }
      else {//nothing changes
	Simaxj += A[j];
	Simaxj %= m;
      }
      if (Simaxj > Smax) {
	maxSj = make_pair(imax,j);
	Smax = Simaxj;
	cout << imax << "," << j << " Smax: " << Smax << endl;
      }
    }
    cout << maxSj.first << ", " <<  maxSj.second << " => ";
    cout << S(maxSj.first, maxSj.second, acc) << " " << Smax << endl;
    /*
    for (long j= 1; j<=50; j++) 
      for (long i= j;i<=50; i++) 
	cout << j << "," << i << ":" << S(j,i,acc)%m << endl;
    */
  }
}
