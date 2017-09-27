#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

struct wave {
  int length;
  int current;
  wave(int l):length(l), current(0) {}
  int operator()() { return (current++ % length == 0);}
};

int main() {
  int amount;
  cin >> amount;
  int M;
  cin >> M;
  vector<int> coins(M);
  for (int i=0;i<M;++i) cin >> coins[i];
  sort(coins.begin(), coins.end());
  vector<unsigned long> genfunc(amount+1);
  vector<int>::iterator ci = coins.begin();
  vector<unsigned long>::iterator gfi;
  for (gfi =  genfunc.begin(); gfi < genfunc.end(); gfi += *ci) {
    *gfi = 1;
  }
  //  print(genfunc.begin(), genfunc.end());
  for (++ci;ci < coins.end(); ++ci) {
    for (gfi =  genfunc.begin()+(*ci); gfi < genfunc.end(); ++gfi) {
      *gfi += *(gfi-*ci);
    }
    //    print(genfunc.begin(), genfunc.end());
  }
  /*
  generate(genfunc.begin(), genfunc.end(), wave(*ci));
  for (++ci;ci != coins.end(); ++ci) {
    transform(genfunc.begin()+(*ci), genfunc.end(), genfunc.begin(),
	      genfunc.begin()+(*ci), plus<int>());
  }
  */
  cout << genfunc[amount] << endl;
}
