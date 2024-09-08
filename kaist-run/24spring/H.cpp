#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
const int MAXN = 100005;
const LL inf = (1LL << 60);
int n;
int A[MAXN];
vector<int> adj[MAXN];
LL res;
LL dfs(int u, int par) {
    LL sum = A[u];
    for (int v: adj[u]) {
        if (v == par) {
            continue;
        }
        LL val = dfs(v, u);
        if (val > 0) {
            sum += val;
        }
    }
    res = max(res, sum);
    return sum;
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        adj[x].pb(y);
        adj[y].pb(x);
    }
    int q;
    scanf("%d", &q);
    while (q--) {
        int i, v;
        scanf("%d %d", &i, &v);
        A[i] = v;
        res = -inf;
        dfs(1, 0);
        printf("%lld\n", res);
    }
    return 0;
}