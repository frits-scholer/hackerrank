#include <vector>
#include <queue>
#include <fstream>
#include <iostream>
#include <unordered_map>
using namespace std;
 
class State {
  size_t _node;
  long _dist;
public:
  State( size_t aNode, long aDist) : _node{aNode}, _dist{aDist} {}
  inline size_t node()const { return _node; }
  inline long dist()const { return _dist; }
};
 
class AdjacencyList {
  vector< vector< State>  > _adj;//a vector of states
  AdjacencyList() = delete;
public:
  AdjacencyList( istream &input );
  inline size_t size() const { return _adj.size(); }
  inline const std::vector<State>& adj(size_t node )  const { return _adj[node]; }
};
 
inline bool operator<( const State &a, const State &b ) {
  return a.dist() > b.dist();
  //priority queue selects the maximum: a < max if a.dist() > max.dist()
}
 
AdjacencyList::AdjacencyList( istream& input) : _adj{} {
  size_t nNodes; size_t nEdges; input >> nNodes >> nEdges;
  _adj.resize( nNodes );
 
  for( size_t e = 0; e < nEdges; ++e ) {
    size_t v, w; long weight;
    input >> v >> w >> weight;
    // Add this edge to both the v and w lists
    _adj[v-1].push_back( State{ w-1, weight} );
    _adj[w-1].push_back( State{ v-1, weight} );
  }
}
 
long prim( const AdjacencyList &adj ) {
  unordered_map<int, bool> visited;
  priority_queue<State> pq;
  size_t S;
  cin >> S;
  pq.push( State{ S-1, 0 } );
  long weight = 0;
  
  while( visited.size() < adj.size() ) {
    auto top = pq.top(); pq.pop();//get nearest neighbor to fragment
     if( visited.count( top.node() ) == 0 ) {//if vertex was not known
      visited[top.node()] = true;
      weight += top.dist();//this vertex is now known
      for( auto vertex : adj.adj( top.node() ) ) 
	pq.push( vertex );//update priority queue with all unseen neighbors
     }
  }
  return weight;
}
 
int main() {
    auto adj = AdjacencyList{cin};
    cout << prim( adj ) << "\n";
}
