#include <iostream>
#include <tuple>
using namespace std;

typedef tuple<int, int, int> subarray;

void print_subarray(subarray sa) {
  cout << "(" << get<0>(sa) << "," << get<1>(sa) << ")=>" << get<2>(sa) << endl;
}

int main() {
  int A[] {13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
  int acc[16];
  int low, high, sum;
  subarray maxSj = make_tuple(0,0,A[0]);
  print_subarray(maxSj);
  acc[0]=A[0];
  for (int j=1;j<16;j++) {
    acc[j]=acc[j-1]+A[j];
    tie(low, high, sum) = maxSj;
    if (A[j]>0) {
      if (high == j-1) high = j;
      else {
	if (acc[j-1]-acc[high+1] > 0) high = j;
	else if (A[j]>sum) {low=j;high=j;}
      }
    }
    sum = low>0?acc[high]-acc[low-1]:acc[high];
    maxSj = make_tuple(low, high, sum);
    print_subarray(maxSj);
  }
}
