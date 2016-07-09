#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;


int main() {
  int T;
  cin >> T;
  vector<int> N(T);
  vector<int> M(T);
  vector<vector<vector<int> > > V(T);
  vector<int> S(T);
  //input all the data
  for (int i=0;i<T;i++) {
    cin >> N[i] >> M[i];
    //vector<int> VV(N[i]);
    V[i].resize(N[i]);
    for (int j=0;j<M[i];j++) {
      int x, y;
      cin >> x >> y;
      V[i][x-1].push_back(y-1);
      V[i][y-1].push_back(x-1);
    }
    cin >> S[i];
  }
  for (int i=0;i<T;i++) {
    vector<int> dist(N[i], -1);
    dist[S[i]-1] = 0;
    stack<int> seen;
    seen.push(S[i]-1);
    while (!seen.empty()) {
      int v = seen.top();
      seen.pop();
      for (size_t j=0;j<V[i][v].size();j++)
	if (dist[V[i][v][j]] < 0 || dist[V[i][v][j]] > dist[v]+6) {
	    dist[V[i][v][j]]=dist[v]+6;
	    seen.push(V[i][v][j]);
		      }
     }
    for (int j=0;j<N[i];j++) {
      if (j==S[i]-1) continue;
      cout << dist[j] << ' ';
    }
    cout << endl;
  }
}
