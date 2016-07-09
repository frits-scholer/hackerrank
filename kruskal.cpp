#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
 
struct Edge {
  unsigned long wt;
  size_t from;
  size_t to;
  Edge(size_t f, size_t t, long w): wt(w), from(f), to(t) {} 
};

struct Node {
  size_t nr;
  size_t comp;
  size_t clink;
  size_t csize;
  Node(size_t n): nr(n), comp(n), clink(n), csize(1) {}
};

inline bool operator<( const Edge &a, const Edge &b ) {
  return (a.wt < b.wt || (a.wt == b.wt && a.from+a.to+a.wt < b.from+b.to+b.wt)) ;
}

int main() {
  //input N, M
  size_t N, M;
  cin >> N >> M;
  vector<Edge> Edges;
  vector<Node> Vert;
  for (size_t i=0;i<N;++i) Vert.push_back(Node(i+1));
  for (size_t i=0;i<M;++i) {
    size_t x, y;
    unsigned long r;
    cin >> x >> y >> r;
    if (x < y) Edges.push_back(Edge(x, y, r));
    else Edges.push_back(Edge(y, x, r));
  }
  size_t S; cin >> S;//not used
  sort(Edges.begin(), Edges.end());
  //for (auto e: Edges) cout << e.wt << ": " << e.from << " - " << e.to << endl;
  size_t components = N;
  unsigned long tot_len = 0;
  for (size_t i=0;i<M;++i) {
    size_t u = Edges[i].from;
    size_t v = Edges[i].to;
    size_t w;
    //if u and v are already in same component continue
    if (Vert[u-1].comp == Vert[v-1].comp) continue;
    tot_len += Edges[i].wt;
    if (--components == 1) break;
    //merge the components containing u and v
    u = Vert[u-1].comp;
    v = Vert[v-1].comp;
    if (Vert[u-1].csize < Vert[v-1].csize) {
      w = u; u = v; v = w;
    }
    Vert[u-1].csize += Vert[v-1].csize;
    w = Vert[v-1].clink;
    Vert[v-1].clink = Vert[u-1].clink;
    Vert[u-1].clink = w;
    for (;;w = Vert[w-1].clink) {
      Vert[w-1].comp = u;
      if (w == v) break;
    }
  }
  cout << tot_len << endl;
}
