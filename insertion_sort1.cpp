#include <iostream>
#include <vector>
using namespace std;

void insertionSort(vector<int>& v) {
  int e = v.back();
  int i = v.size();
  if (i==1) cout << e << endl;
  else {
    while (--i>0 && v[i-1] > e) {
      v[i] = v[i-1];
      for (auto n:v) cout << n << " ";
      cout << endl;
     }
    v[i] = e;
    for (auto n:v) cout << n << " ";
    cout << endl;
  }
}

int main(void) {
   vector <int> ar;
   int ar_size;
   cin >> ar_size;
   for (int i=0; i < ar_size; i++) {
     int tmp;
     cin >> tmp;
     ar.push_back(tmp); 
   }
   insertionSort(ar);
   return 0;
}
