#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
using namespace std;

bool abs_eq(int i, int j) {
  return (i == j) || (i == -j);
}

bool is_funny(const string& s) {
  string r;
  reverse_copy(s.begin(),s.end(),back_inserter(r));
  vector<int> dist_s(s.size());
  adjacent_difference(s.begin(), s.end(), dist_s.begin());
  vector<int> dist_r(s.size());
  adjacent_difference(r.begin(), r.end(), dist_r.begin());
  return equal(dist_s.begin()+1, dist_s.end(), dist_r.begin()+1, abs_eq);
}

int main() {
  int T;
  cin >> T;
  vector<string> v(T);
  for (int i=0;i<T;++i) cin >> v[i];
  for (auto s:v)
    cout <<  (is_funny(s)?"": "Not ") << "Funny" << endl;
}
