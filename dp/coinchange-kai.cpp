#include <stdio.h>

int N, M;
long long dp[50][251];
long long C[50];

int main() {

  scanf("%d %d", &N, &M);
  for (int i = 0; i < M; i++) scanf("%lld", &C[i]);
    
  for (int j = 1; j <= N; j++)
    if (j % C[0] == 0) dp[0][j] = 1;
    
  for (int i = 0; i < M; i++) dp[i][0] = 1;  
    
  for (int i = 1; i < M; i++) {
    for (int j = 1; j < C[i]; j++) dp[i][j] = dp[i-1][j];
    for (int j = C[i]; j <= N; j++)
      dp[i][j] = dp[i-1][j] + dp[i][j-C[i]];
  }
  
  printf("%lld\n", dp[M-1][N]);
  
  return 0;
}
