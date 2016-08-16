#include <iostream>
#include <vector>
using namespace std;

unsigned long insertionSort_shifts(vector<int>& v) {
  if (v.size()==1) return 0;
  else {
    unsigned long shifts = 0;
    for (unsigned int i = 1;i < v.size();++i) {
      int e = v[i];
      unsigned int j = i+1;
      while (--j > 0 && v[j-1] > e) {
      v[j] = v[j-1];
      shifts++;
      }
      v[j] = e;
    }
    return shifts;
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
   cout << insertionSort_shifts(ar) << endl;
   return 0;
}
