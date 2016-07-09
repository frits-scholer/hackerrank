#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <utility>

using namespace std;


int main() {
  int T;
  cin >> T;
  vector<int> N(T);
  vector<int> M(T);
  vector<vector<vector<pair<int,int> > > > V(T);
  vector<int> S(T);
  //input all the data
  for (int i=0;i<T;i++) {
    cin >> N[i] >> M[i];
    //vector<int> VV(N[i]);
    V[i].resize(N[i]);
    for (int j=0;j<M[i];j++) {
      int x, y, r;
      cin >> x >> y >> r;
      V[i][x-1].push_back(make_pair(y-1,r));
      V[i][y-1].push_back(make_pair(x-1,r));
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
      for (size_t j=0;j<V[i][v].size();j++) {
	pair<int,int> p = V[i][v][j];
	if (dist[p.first] < 0 || dist[p.first] > dist[v]+p.second) {
	  dist[p.first]=dist[v]+p.second;
	  seen.push(p.first);
	}
      }
     }
    for (int j=0;j<N[i];j++) {
      if (j==S[i]-1) continue;
      cout << dist[j] << ' ';
    }
    cout << endl;
  }
}
