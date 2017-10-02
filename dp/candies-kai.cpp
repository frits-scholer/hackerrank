#include <stdio.h>
#include <algorithm>

using namespace std;

int N;
int A[100000];
int D[100000];
int R[100000];

int main() {

  scanf("%d", &N);
  for (int i = 0; i < N; i++) scanf("%d", &A[i]);
 // for (int i = 0; i < N; i++) printf("%d ", A[i]); printf("\n");
  
  if (N == 1) {
    printf("%d\n", 1); return 0;
  }
  
  R[N-1] = 1;
  for (int i = N-2; i >= 0; i--) {
    if (A[i] > A[i+1])
      R[i] = R[i+1] + 1;
    else
      R[i] = 1;
  }
  //for (int i = 0; i < N; i++) printf("%d ", R[i]); printf("\n");
  
  
  D[0] = R[0];  
  
  for (int i = 1; i < N; i++) {
    if (A[i] <= A[i-1]) 
      D[i] = R[i];
    else
      D[i] = max(D[i-1] + 1, R[i]);
  }
//  for (int i = 0; i < N; i++) printf("%d ", D[i]); printf("\n");
  
  long long s = 0;
  for (int i = 0; i < N; i++) s = s + D[i];
  
  printf("%lld\n", s);
  
  return 0;
}
