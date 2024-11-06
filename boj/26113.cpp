#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef pair<int, int> pii;
const int MAXN = 100005;
const int LOGMAXN = 16;
int n;
vector<int> adj[MAXN];
int dep[MAXN];
int pa[LOGMAXN + 1][MAXN];
bool vis[MAXN];
vector<pii> back_edge[MAXN];
void init_vis() {
    for (int i = 1; i <= n; i++) {
        vis[i] = false;
    }
}
void dfs1(int u) {
    vis[u] = true;
    for (int v: adj[u]) {
        if (vis[v]) {
            continue;
        }
        dfs1(v);
    }
}
void connect_forest() {
    dfs1(1);

    for (int i = 2; i <= n; i++) {
        if (vis[i]) {
            continue;
        }
        dfs1(i);
        adj[1].pb(i);
        adj[i].pb(1);
    }
}
void dfs2(int u, int par) {
    vis[u] = true;
    for (int v: adj[u]) {
        if (vis[v]) {
            if (v != par && dep[u] > dep[v]) {
                back_edge[0].pb(pii(u, v));
            }
            continue;
        }
        pa[0][v] = u;
        dep[v] = dep[u] + 1;
        dfs2(v, u);
    }
}
void construct_pa() {
    init_vis();
    dep[1] = 1;
    dfs2(1, 0);

    for (int i = 1; i <= LOGMAXN; i++) {
        for (int j = 1; j <= n; j++) {
            pa[i][j] = pa[i - 1][pa[i - 1][j]];
        }
    }
}

int get_lca(int u, int v) {
    if (dep[u] > dep[v]) {
        swap(u, v);
    }
    for (int i = LOGMAXN; i >= 0; i--) {
        if (dep[pa[i][v]] >= dep[u]) {
            v = pa[i][v];
        }
    }
    if (u == v) {
        return u;
    }


    for (int i = LOGMAXN; i >= 0; i--) {
        if (pa[i][u] != pa[i][v]) {
            u = pa[i][u];
            v = pa[i][v];
        }
    }
    return pa[0][u];
}

void construct_back_edge() {
    for (pii e: back_edge[0]) {
        int lca = get_lca(e.fi, e.se);
        back_edge[dep[e.fi] + dep[e.se] - 2 * dep[lca]].pb(e);
    }
    back_edge[0].clear();
}

void print_path(pii p) {
    int lca = get_lca(p.fi, p.se);
    vector<int> t1, t2;
    while (p.fi != lca) {
        t1.pb(p.fi);
        p.fi = pa[0][p.fi];
    }

    while (p.se != lca) {
        t2.pb(p.se);
        p.se = pa[0][p.se];
    }

    for (int v: t1) {
        printf("%d ", v);
    }
    printf("%d ", lca);
    reverse(all(t2));

    for (int v: t2) {
        printf("%d ", v);
    }

    printf("\n");
}
void calc() {
    // two back_edge has same distance
    for (int i = 2; i < n; i++) {
        if (back_edge[i].size() > 1) {
            printf("%d\n", i + 1);
            print_path(back_edge[i][0]);
            print_path(back_edge[i][1]);
            return;
        }
    }


    // then, back_edge[i].size() = 1 for all i in [1, n - 1]
    printf("3\n");
    // len = 2
    printf("%d %d %d\n", back_edge[2][0].fi, pa[0][back_edge[2][0].fi], back_edge[2][0].se);

    int x = back_edge[n - 2][0].fi;
    int y = back_edge[n - 2][0].se;
    int z = back_edge[n - 1][0].fi;
    int k = back_edge[n - 1][0].se;

    if (x == z) {
        printf("%d %d %d\n", x, y, k);
    }
    else {
        printf("%d %d %d\n", x, k, z);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < 2 * n - 3; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        adj[x].pb(y);
        adj[y].pb(x);
    }
    connect_forest();
    construct_pa();
    construct_back_edge();
    calc();
    return 0;
}