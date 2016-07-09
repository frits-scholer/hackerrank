#include <iostream>
#include <vector>
using namespace std;

void insertionSort(vector<int>& v) {
  if (v.size()==1) cout << v[0] << endl;
  else {
    for (unsigned int i = 1;i < v.size();++i) {
      int e = v[i];
      int j = i+1;
      while (--j > 0 && v[j-1] > e) {
      v[j] = v[j-1];
      }
      v[j] = e;
      for (auto n:v) cout << n << " ";
      cout << endl;
    }
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
