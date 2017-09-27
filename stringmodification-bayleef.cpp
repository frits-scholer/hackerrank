#ifdef ssu1
#define _GLIBCXX_DEBUG
#endif
#undef NDEBUG

#include <algorithm>
#include <functional>
#include <numeric>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cassert>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <bitset>
#include <sstream>

using namespace std;

#define fore(i, l, r) for(int i = (l); i < (r); ++i)
#define forn(i, n) fore(i, 0, n)
#define fori(i, l, r) fore(i, l, (r) + 1)
#define sz(v) int((v).size())
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define mp make_pair
#define X first
#define Y second

typedef long long li;
typedef long double ld;
typedef pair<int, int> pt;

template<typename T> T abs(T a) { return a < 0 ? -a : a; }
template<typename T> T sqr(T a) { return a*a; }

const int INF = (int)1e9;
const ld EPS = 1e-9;
const ld PI = 3.1415926535897932384626433832795;

/*

    This is just to check correctness of input

*/
int readInt(int l, int r){
    int x;
    if(scanf("%d", &x) != 1){
        fprintf(stderr, "Expected int in range [%d, %d], but haven't found!", l, r);
        throw;
    }
    if(!(l <= x && x <= r)){
        fprintf(stderr, "Expected int in range [%d, %d], but found %d!", l, r, x);
        throw;
    }
    return x;
}
int readInt(int l, int r, string name){
    int x;
    if(scanf("%d", &x) != 1){
        fprintf(stderr, "Expected int %s in range [%d, %d], but haven't found!", name.c_str(), l, r);
        throw;
    }
    if(!(l <= x && x <= r)){
        fprintf(stderr, "Expected int %s in range [%d, %d], but found %d!", name.c_str(), l, r, x);
        throw;
    }
    return x;
}
li readLong(li l, li r){
    li x;
    if(scanf("%lld", &x) != 1){
        fprintf(stderr, "Expected long long in range [%lld, %lld], but haven't found!", l, r);
        throw;
    }
    if(!(l <= x && x <= r)){
        fprintf(stderr, "Expected long long in range [%lld, %lld], but found %lld!", l, r, x);
        throw;
    }
    return x;
}
li readLong(li l, li r, string name){
    li x;
    if(scanf("%lld", &x) != 1){
        fprintf(stderr, "Expected long long %s in range [%lld, %lld], but haven't found!", name.c_str(), l, r);
        throw;
    }
    if(!(l <= x && x <= r)){
        fprintf(stderr, "Expected long long %s in range [%lld, %lld], but found %lld!", name.c_str(), l, r, x);
        throw;
    }
    return x;
}
const ld __EPS__ = 1e-15;
ld readDouble(double l, double r){
    double x;
    if(scanf("%lf", &x) != 1){
        fprintf(stderr, "Expected double in range [%lf, %lf], but haven't found!", l, r);
        throw;
    }
    if(!(l <= x + __EPS__ && x <= r + __EPS__)){
        fprintf(stderr, "Expected double in range [%lf, %lf], but found %lf!", l, r, x);
        throw;
    }
    return x;
}
ld readDouble(double l, double r, string name){
    double x;
    if(scanf("%lf", &x) != 1){
        fprintf(stderr, "Expected double %s in range [%lf, %lf], but haven't found!", name.c_str(), l, r);
        throw;
    }
    if(!(l <= x + __EPS__ && x <= r + __EPS__)){
        fprintf(stderr, "Expected double %s in range [%lf, %lf], but found %lf!", name.c_str(), l, r, x);
        throw;
    }
    return x;
}

const int ALP = 26, mod = 1000003, NMAX = 3000;

int cnt[ALP], global_n, d[ALP][NMAX], k, fact[mod], rfact[mod];

int prime(int x){
    for(int d = 2; d * d <= x; d++)
        if(x % d == 0)
            return false;
    return x > 1;
}

int modpow(int a, int b){
    int ans = 1 % mod;
    while(b){
        if(b & 1)
            ans = (ans * 1LL * a) % mod;
        a = (a * 1LL * a) % mod;
        b >>= 1;
    }
    return ans;
}

int rev(int val){
    return modpow(val, mod - 2);
}

void init(){
    fact[0] = rfact[0] = 1;
    fore(i, 1, mod){
        fact[i] = (fact[i - 1] * 1LL * i) % mod;
        rfact[i] = (rfact[i - 1] * 1LL * rev(i)) % mod;
    }
}

int C(int n, int k){
    if(k < 0 || k > n)
        return 0;
    if(k == 0)
        return 1;
    //n!/(n-k)!/k!
    //(n-k+1)*...*n / (1*...*k)
    int lf = (n - k + 1) % mod, rg = n % mod;
    if(lf > rg || lf == 0)
        return 0;
    return ((fact[rg] * 1LL * rfact[lf-1]) % mod * 1LL * rfact[k]) % mod; 
}

int D(int n, int m){
    assert(m > 0);
    return C(n + m - 1, m - 1);
}

int ways(int n, int c){
    assert(n >= 0);
    if(c == 0)
        return 1;
    if(c == 1)
        return n + 1;
    if(k * 1LL * (c - 1) > n)
        return 0;
    n -= k * (c - 1);
    return D(n, c + 1);
}

int calc(int idx, int n){
    if(idx == ALP){
        return 1;
    }
    int& res = d[idx][global_n - n];
    if(res == -1){
        res = 0;
        fori(cntc, 0, cnt[idx]){
            if(cntc > n)
                break;
            int rem = n - cntc;
            res = (res + calc(idx + 1, rem) * 1LL * ways(rem, cntc)) % mod;
        }
    }
    return res;
}

int main(){
#ifdef ssu1
    assert(freopen("input.txt", "rt", stdin));
    //assert(freopen("output.txt", "wt", stdout));
#endif
    if(!prime(mod))
        throw;

    init();

    global_n = readInt(1, 1e9), k = readInt(0, 1e9);
    char buf[3000];
    gets(buf); gets(buf);
    int szb = strlen(buf);

    forn(i, szb){
        cnt[buf[i] - 'A']++;
    }    

    memset(d, -1, sizeof d);

    printf("%d\n", calc(0, global_n));
    return 0;
}
