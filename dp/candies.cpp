#include <iostream>
#include <vector>
using namespace std;
vector<int> dp;

int candies(int n, vector <int> arr) {
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    dp.resize(n,1);//everybody gets 1
    for(int arr_i = 0; arr_i < n; arr_i++){
       cin >> arr[arr_i];
    }
    int result = candies(n, arr);
    cout << result << endl;
    return 0;
}
