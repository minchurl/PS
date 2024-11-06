#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef pair<int, int> pii;
typedef long long LL;
const int MAXN = 250005;
const int MAXM = 500005;
int n, m;
bool vis[MAXM];
vector<int> V;
vector<int> adj[MAXM];
pii E[MAXN];
pii dfs(int u) {
    pii ret = pii(-2 + adj[u].size(), V[u]);
    vis[u] = true;
    for (int v: adj[u]) {
        if (vis[v]) {
            continue;
        }
        pii p = dfs(v);
        ret.fi += p.fi;
        ret.se = max(ret.se, p.se);
    }
    return ret;
}
int main() {
    LL ret = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        ret += a + b;
        E[i] = pii(a, b);
        V.pb(a);
        V.pb(b);
    }
    sort(all(V)); V.erase(unique(all(V)), V.end());

    m = V.size();

    for (int i = 1; i <= n; i++) {
        int a = lower_bound(all(V), E[i].fi) - V.begin();
        int b = lower_bound(all(V), E[i].se) - V.begin();
        adj[a].pb(b);
        adj[b].pb(a);
    }
    

    for (int i = 0; i < m; i++) {
        ret -= V[i];
        if (vis[i]) {
            continue;
        }
        pii p = dfs(i);
        ret += (p.fi == 0 ? 0 : 1) * p.se;
    }

    printf("%lld\n", ret);
    return 0;
}