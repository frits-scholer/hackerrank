#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

int main() {
  string S;
  cin >> S;
  map<char, int> ft;
  for_each(S.begin(), S.end(),[&](char c){ft[c]++;});
  vector<int> difs;
  for_each(ft.begin(), ft.end(),[&](pair<char,int> p)
	   {difs.push_back(p.second);});
  sort(difs.begin(),difs.end());
  vector<int>::iterator di = unique(difs.begin(), difs.end());
  difs.resize(distance(difs.begin(), di));
  if (difs.size() == 1) cout << "YES";
  else if (difs.size() > 2) cout << "NO";
  else {
    int n = 0; int m = 0;
    for_each(ft.begin(), ft.end(),[&](pair<char,int> p)
	     {if (p.second == difs[0]) n++;if (p.second == difs[1]) m++;});
    if ((difs[0]==1 && n==1) || (difs[1]==difs[0]+1 && m ==1)) cout << "YES";
    else cout << "NO";
  }
  cout << endl;
}
