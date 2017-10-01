#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int numOps(int n) {
    if (n <= 0)
        return 0;
    switch (n){
        case 1:
        case 2:
            return 1;
        case 3:
        case 4:
            return 2;
    }
    return n/5 + numOps(n%5);
}

int main() {
    int num_tests;
    cin >>num_tests;
    for(int k=0; k<num_tests; ++k) {
        // read test data
        int N;
        cin >> N;
        vector<int> buckets(N);
        int bucket_min = 0;
        for(int i=0; i<N; ++i) {
            cin >> buckets[i];
            if ((i==0) || (bucket_min > buckets[i])) {
                bucket_min = buckets[i];
            }
        }
        
        // calculate operations
        int min_ops = 0;
        for(int j=0; j<5; j++) {
            int ops = 0;
            for(int i=0; i<N; ++i) {
                ops += numOps(buckets[i]-bucket_min+j);
            }
            if ((j==0) || (min_ops > ops)) {
                min_ops = ops;
            }
        }
        cout << min_ops << endl;
    }
    return 0;
}
