#include <iostream>
#include <utility>
using namespace std;

typedef pair<int, int> subarray;
#define S(i,j,A) A[j]-A[i-1]

void print_subarray(subarray sa, int *acc) {
  cout << "(" << sa.first << "," << sa.second << ")=>" << S(sa.first, sa.second, acc) << endl;
}

int main() {
  int A[] {0,13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
  int acc[17];
  subarray maxSj = make_pair(1,1);
  int sum = A[1];
  int Simaxj=A[1];
  int imax=1;
  acc[0]=A[0];
  acc[1]=A[1];
  for (int j=2;j<16;j++) {
    acc[j]=acc[j-1]+A[j];
    if (A[j]>0) {
      if (Simaxj < 0) {
	Simaxj = 0;
	imax = j;
      }
      if (A[j]> sum - Simaxj) {
	maxSj = make_pair(imax, j);
	sum = S(maxSj.first, maxSj.second,acc);
      }
    }
    Simaxj += A[j];
  }
  print_subarray(maxSj,acc);
}
