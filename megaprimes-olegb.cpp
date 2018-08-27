#include <bits/stdc++.h>

using namespace std;

struct IPT {
    const int kLookupSize;
    const int iter_max;
    int base[8] = {2, 3, 5, 7, 11, 13, 17, 23};
    vector<bool> arr;

    IPT(int lookup_size)
        : kLookupSize(lookup_size)
        , iter_max(8)
        , arr(lookup_size, true)
    {
        for(int i=2; i<kLookupSize; ++i) {
            if (arr[i]) {
                for(int j=2*i; j<kLookupSize; j+=i) {
                    arr[j] = false;
                }
            }
        }
    }
   
    long pm(long a, long p, long mod) const {
        long res = 1;
        __int128_t factor = a;
        while(p) {
            if (p % 2)
                res = (res * factor) % mod;
            p /= 2;
            if (p)
                factor = (factor * factor) % mod;
        }
        return res;
    }
   
    bool isp(long p) const {
        if (p < kLookupSize) {
            return arr[p];
        }
        if ((p%3 == 0) || (p%7 == 0) || (p%11 == 0) || (p%13 == 0) || (p%17 == 0) || (p%19 == 0))
            return false;
        long m = (p-1)/2;
        int s = 1;
        while(m % 2 == 0) { ++s; m /= 2; }
        for(int k=0; k<iter_max; ++k) {
            long a = pm(base[k], m, p);
            if ((a == 1) || (a == p-1))
                continue;
            int s_count = s;
            while (s_count > 1) {
                a = __int128_t(a)*a % p;
                if (a == 1)
                    return false;
                if (a == p-1)
                    break;
                --s_count;
            }
            if (a != p-1)
                return false;
        }
        return true;
    }
};

struct MegaIter {
    long base;
    long next_limit;
    
    MegaIter(long v) : base(0) {
        long factor = 1;
        while(v) {
            int d = v%10;
            int gd = upper_good_digit(d);
            if (gd == d) {
                base += factor*digit_to_base4(d);
            } else {
                base = factor*digit_to_base4(gd);
            }
            factor *= 4;
            v /= 10;
        }
        base += factor;
        next_limit = 2*factor;
        if ((base & 3)%2 == 0)
            ++base;
    }
    
    int upper_good_digit(int d) const {
        const static int index[10] = {2, 2, 2, 3, 5, 5, 7, 7, 0, 0};        
        return index[d];
    }
    
    int digit_to_base4(int d) const {
        const static int index[10] = {4, 4, 0, 1, 4, 2, 4, 3, 4, 4};        
        return index[d];
    }
    
    void inc() {
        ++base;
        if (base == next_limit) {
            base *= 2;
            next_limit *= 4;
        }
        ++base;
    }  
    
    long value() const {
        const static int revert[4] = {2, 3, 5, 7};
        long factor = 1;
        long b = base;
        long res = 0;
        while(b>1) {
            res += factor*revert[b & 3];
            b = b>>2;
            factor *= 10;
        }
        return res;
    }
};

int main(){
    long first, last;
    cin >> first >> last;

    IPT ipt(1000000);
    // separate the single-digit cases
    int count = 0;
    if (first < 10) {
        set<int> single_digit_mega_primes = {2, 3, 5, 7};
        for(long i=first; i<=min(long(10), last); ++i) {
            if (single_digit_mega_primes.count(i))
                ++count;
        }
        first = 11;
    }

// Debugging the iterator    
/*    long v = 777743;
    MegaIter it(v);
    for(int i=0; i<20; ++i) {
        cout << it.value() << endl;
        it.inc();
    } */
    
    // all-the-rest cases
    MegaIter it(first);
    long pcand;
    while((pcand = it.value()) <= last) {
//cout << "Candidate: " << pcand;        
        if (ipt.isp(pcand)) {
            ++count;
//cout << "   GOOD!";
        }
//cout << endl;        
        it.inc();
    }
    
    cout << count << endl;
    return 0;
}
