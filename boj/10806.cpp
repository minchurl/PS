#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
const int MAXN = 100005;
int n, m;
int dn, dfn[MAXN], low[MAXN];
int cmp[MAXN];
bool vis[MAXN];
vector<pii> adj[MAXN];
vector<int> bcc_adj[MAXN];
vector<int> bcc;
vector<int> lst;
void construct_dfn(int u, int idx) {
    dfn[u] = low[u] = ++dn;
    for (pii e: adj[u]) {
        if (!dfn[e.fi]) {
            construct_dfn(e.fi, e.se);
            low[u] = min(low[u], low[e.fi]);
        }
        else if (e.se != idx) {
            low[u] = min(low[u], dfn[e.fi]);
        }
    }
}
void coloring(int u, int c) {
    if (u == c) {
        bcc.pb(u);
    }
    cmp[u] = c;
    vis[u] = true;
    for (pii e: adj[u]) {
        if (vis[e.fi]) {
            continue;
        }
        if (dfn[u] < low[e.fi]) {
            coloring(e.fi, e.fi);
        }
        else {
            coloring(e.fi, c);
        }
    }
}

void construct_bcc_adj() {
    for (int u = 1; u <= n; u++) {
        for (pii e: adj[u]) {
            if (cmp[u] != cmp[e.fi]) {
                bcc_adj[cmp[u]].pb(cmp[e.fi]);
            }
        }
    }
}
void construct_bcc_dfn(int u, int par) {
    dfn[u] = ++dn;
    for (int v: bcc_adj[u]) {
        if (par != v) {
            construct_bcc_dfn(v, u);
        }
    }
    if (bcc_adj[u].size() == 1) {
        lst.pb(u);
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        if (x != y) {
            adj[x].pb(pii(y, i));
            adj[y].pb(pii(x, i));
        }
    }
    construct_dfn(1, 0);
    coloring(1, 1);
    construct_bcc_adj();

    if (bcc.size() == 1) {
        printf("0\n");
        return 0;
    }
    else if (bcc.size() == 2) {
        printf("1\n");
        printf("%d %d\n", bcc[0], bcc[1]);
        return 0;
    }

    int r = 0;
    for (int v: bcc) {
        dfn[v] = 0;
        if (bcc_adj[v].size() > 1) {
            r = v;
        }
    }

    dn = 0;
    construct_bcc_dfn(r, 0);

    printf("%d\n", (lst.size() + 1) / 2);

    for (int i = 0; i < lst.size() / 2; i++) {
        printf("%d %d\n", lst[i], lst[i + lst.size() / 2]);
    }
    if (lst.size() % 2) {
        printf("%d %d\n", lst[0], lst.back());
    }
    return 0;
}