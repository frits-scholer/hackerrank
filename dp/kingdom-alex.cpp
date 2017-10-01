#include <cstdio>
#include <vector>

using namespace std;

const int MX = 100000, md = 1000000007;

vector<int> G[MX];
int f[MX], g[MX];

void dfs(int v, int p = -1) {
    f[v] = 0;
    g[v] = 1;
    
    for (int u : G[v]) {
        if (u == p) continue;
        
        dfs(u, v);
        
        f[v] = ((f[v] + g[v]) * 1ll * g[u] + f[v] * 2ll * f[u] + g[v] * 1ll * f[u]) % md;
        g[v] = (g[v] * 1ll * f[u]) % md;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    
    dfs(0);
    
    printf("%d\n", (2 * f[0]) % md);
    
    return 0;
}
