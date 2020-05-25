
#include <iostream>
#include <set>

using namespace std;

int main() {
  //input
  int T;
  cin >> T;
  long N;
  for (int i=0;i<T;i++) {
    cin >> N;
    long A[N];
    multiset<long> m;
    for (auto& a:A) cin >> a;
    for (auto a:A) m.insert(a);
    long cur = *begin(m);
    long S = 0;
    long curcount=0;
    for (auto it=begin(m);it != end(m); ++it){
      if (*it != cur) {S+=curcount*(curcount-1);curcount=0;cur=*it;}
      curcount++;
    }
    S+=curcount*(curcount-1);
    m.clear();
    cout << S << endl;
  }
}
