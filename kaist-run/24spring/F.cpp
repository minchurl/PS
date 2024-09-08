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
LL res;
int dep[MAXN];
bool chk[MAXN];
LL tmax[MAXN], lmax[MAXN];
int par[MAXN];
vector<pii> adj[MAXN];
vector<pii> nadj[MAXN];
void construct_par(int u, int pa) {
    par[u] = pa;
    for (pii v: adj[u]) {
        if (v.fi == pa) {
            continue;
        }
        dep[v.fi] = dep[u] + 1;
        construct_par(v.fi, u);
    }
}
void construct_max(int u, int pa) {
    LL max1 = -inf;
    LL max2 = -inf;
    tmax[u] = lmax[u] = 0;
    for (pii v: nadj[u]) {
        if (v.fi == pa) {
            continue;
        }
        construct_max(v.fi, u);
        LL val = lmax[v.fi] + v.se;
        lmax[u] = max(lmax[u], val);
        if (max1 <= val) {
            max2 = max1;
            max1 = val;
        }
        else if (max2 < val) {
            max2 = val;
        }
    }
    tmax[u] = max(lmax[u], max1 + max2);
    res = max(res, tmax[u]);
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int x, y, v;
        scanf("%d %d %d", &x, &y, &v);
        adj[x].pb(pii(y, v));
        nadj[x].pb(pii(y, v));
        nadj[y].pb(pii(x, v));
        adj[y].pb(pii(x, v));
    }
    dep[1] = 1;
    construct_par(1, 0);
    int q;
    scanf("%d", &q);
    while (q--) {
        res = -inf;
        int x, y;
        scanf("%d %d", &x, &y);
        for (int i = 1; i <= n; i++) {
            chk[i] = false;
        }
        while (x != y) {
            if (dep[x] <= dep[y]) {
                chk[y] = true;
                y = par[y];
            }
            else {
                chk[x] = true;
                x = par[x];
            }
        }
        chk[x] = true;

        for (int u = 1; u <= n; u++) {
            int sz = adj[u].size();
            for (int i = 0; i < sz; i++) {
                nadj[u][i] = adj[u][i];
            }
            if (!chk[u]) {
                continue;
            }
            for (int i = 0; i < sz; i++) {
                if (chk[adj[u][i].fi]) {
                    nadj[u][i].se = 0;
                }
            }
        }
        construct_max(1, 0);
        printf("%lld\n", res);
    }
    return 0;
}