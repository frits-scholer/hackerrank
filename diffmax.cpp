#include <iostream>
#include <fstream>
//#include <string>
using namespace std;

int main() {
  fstream fs1,fs2;
  fs1.open("maxsubarray1.out");
  fs2.open("test.out");
  long long n1, n2;
  int linenr=0;
  while (fs1>>n1) {
    fs2 >> n2;
    ++linenr;
      if (n1 != n2) cout << linenr << ":\t" << n1 << "\t" << n2 << endl;;
  }
}
