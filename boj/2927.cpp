#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
using namespace std;
const int MAXN = 30005;
const int MAXQ = 300005;
struct Query {
    int type; // 0 -> bridge, 1 -> penguins, 2 -> excursion
    int a, b, x;
    int res;
    // bridge -> 0: NO, 1: YES
    // excursion -> -1: impossible
};
int q;
Query query[MAXQ];

struct SegTree {
    int n;
    int tree[(1 << 16) + 5];
    void init(int _n) {
        n = _n;
    }

    void update(int x, int l, int r, int p, int v) {
        if (l == r) {
            tree[x] = v;
            return;
        }

        int mid = (l + r) >> 1;
        if (p <= mid) {
            update(2 * x, l, mid, p, v);
        }
        else {
            update(2 * x + 1, mid + 1, r, p, v);
        }
        tree[x] = tree[2 * x] + tree[2 * x + 1];
    }
    void update(int p, int v) {
        update(1, 1, n, p, v);
    }

    int get(int x, int l, int r, int s, int e) {
        if (s <= l && r <= e) {
            return tree[x];
        }
        
        int mid = (l + r) >> 1;

        if (e <= mid) {
            return get(2 * x, l, mid, s, e);
        }
        if (s > mid) {
            return get(2 * x + 1, mid + 1, r, s, e);
        }

        return get(2 * x, l, mid, s, mid) + get(2 * x + 1, mid + 1, r, mid + 1, e);
    }
    int get(int l, int r) {
        if (l > r) {
            swap(l, r);
        }
        return get(1, 1, n, l, r);
    }
};
SegTree segTree;

int n;
int pa[MAXN];
int initialNum[MAXN];
int weight[MAXN];
int par[MAXN], head[MAXN];
int dfn[MAXN], dn;

vector<int> adj[MAXN];
void initPa() {
    for (int i = 1; i <= n; i++) {
        pa[i] = i;
    }
}
int findPa(int x) {
    return (pa[x] == x) ? x : (pa[x] = findPa(pa[x]));
}
bool merge(int x, int y) {
    x = findPa(x);
    y = findPa(y);
    if (x == y) {
        return false;
    }
    pa[x] = y;
    return true;
}

bool isConnected(int x, int y) {
    x = findPa(x);
    y = findPa(y);
    return x == y;
}

void dfs1(int u, int p) {
    weight[u] = 1;
    par[u] = p;
    for (int v: adj[u]) {
        if (v == p) {
            continue;
        }
        dfs1(v, u);
        weight[u] += weight[v];
    }
}

void dfs2(int u, int p, int h) {
    dn++;
    dfn[u] = dn;
    head[u] = h;
    for (int &v: adj[u]) {
        if (v == p) {
            continue;
        }
        if (adj[u][0] == p || weight[adj[u][0]] < weight[v]) {
            swap(adj[u][0], v);
        }
    }

    for (int v: adj[u]) {
        if (v == p) {
            continue;
        }
        if (v == adj[u][0]) {
            dfs2(v, u, h);
        }
        else {
            dfs2(v, u, v);
        }
    }
}

int getLinearSum(int a, int b) {
    int res = 0;
    while (head[a] != head[b]) {
        if (dfn[head[a]] > dfn[head[b]]) {
            swap(a, b);
        }
        res += segTree.get(dfn[head[b]], dfn[b]);
        b = par[head[b]];
    }
    if (dfn[a] > dfn[b]) {
        swap(a, b);
    }
    res += segTree.get(dfn[a], dfn[b]);
    return res;
}

int main() {
    freopen("input.txt","r",stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &initialNum[i]);
    }

    initPa();
    segTree.init(n);

    scanf("%d", &q);

    for (int i = 1; i <= q; i++) {
        char s[20];
        scanf("%s", s);
        if (s[0] == 'b') { // bridge
            query[i].type = 1;
            scanf("%d %d", &query[i].a, &query[i].b);
            if (merge(query[i].a, query[i].b)) {
                query[i].res = 1;
                adj[query[i].a].pb(query[i].b);
                adj[query[i].b].pb(query[i].a);
            }
            else {
                query[i].res = 0;
            }
        }
        else if (s[0] == 'p') { // penguins
            query[i].type = 1;
            scanf("%d %d", &query[i].a, &query[i].x);
        }
        else { // excursion
            query[i].type = 2;
            scanf("%d %d", &query[i].a, &query[i].b);
            if (!isConnected(query[i].a, query[i].b)) {
                query[i].res = -1;
            }
        }
    }

    // connect remain part of graph
    for (int i = 2; i <= n; i++) {
        if (merge(1, i)) {
            adj[1].pb(i);
            adj[i].pb(1);
        }
    }

    // construct HLD
    dfs1(1, 0);
    dfs2(1, 0, 1);

    for (int i = 1; i <= n; i++) {
        segTree.update(dfn[i], initialNum[i]);
    }

    for (int i = 1; i <= q; i++) {
        if (query[i].type == 0) {
            printf("%s\n", query[i].res ? "yes" : "no");
        }
        else if (query[i].type == 1) {
            segTree.update(dfn[query[i].a], query[i].x);
        }
        else {
            if (query[i].res == -1) {
                printf("impossible\n");
                continue;
            }
            printf("%d\n", getLinearSum(query[i].a, query[i].b));
        }
    }
    return 0;
}