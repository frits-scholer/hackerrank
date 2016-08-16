#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void quickSort(vector <int> &ar) {
  if (ar.size()<=1) return;
  vector<int> left;
  vector<int> right;
  int p = ar[0];
  vector<int> equal(1,p);
  for (unsigned int i=1;i<ar.size();i++) {
    if (ar[i]<p) left.push_back(ar[i]);
    else if (ar[i]>p) right.push_back(ar[i]);
    else equal.push_back(ar[i]);
  }
  quickSort(left);
  quickSort(right);
  //merge
  for (unsigned int i=0;i<ar.size();i++) {
    for (auto l: left) ar[i++] = l;
    for (auto l: equal) ar[i++] = l;
    for (auto l: right) ar[i++] = l;
  }
  for (auto l: ar) cout << l << " ";
  cout << endl;
}

int main()
{
    int n;
    cin >> n;

    vector <int> arr(n);
    for(int i = 0; i < (int)n; ++i) {
        cin >> arr[i];
    }

    quickSort(arr);

    return 0;
}
