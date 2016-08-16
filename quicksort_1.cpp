#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
void partition(vector <int>  ar) {
   // Enter code for partitioning and printing here.
  vector<int> left;
  vector<int> right;
  int p = ar[0];
  vector<int> equal(1,p);
  for (int i=1;i<ar.size();i++) {
    if (ar[i]<p) left.push_back(ar[i]);
    else if (ar[i]>p) right.push_back(ar[i]);
    else equal.push_back(ar[i]);
  }
  for (auto l: left) cout << l << " ";
  for (auto l: equal) cout << l << " ";
  for (auto l: right) cout << l << " ";
  cout << endl;
}
int main(void) {
   vector <int>  _ar;
   int _ar_size;
   cin >> _ar_size;
    
     for(int _ar_i=0; _ar_i<_ar_size; _ar_i++) {
        int _ar_tmp;
        cin >> _ar_tmp;
        _ar.push_back(_ar_tmp); 
    }

   partition(_ar);
   
   return 0;
}
