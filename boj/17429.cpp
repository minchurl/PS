#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<unsigned int, unsigned int> pui;
typedef pair<LL, LL> pil;
const int MAXN = 500005;
const int SEGTREESIZE = (1 << 20) + 5;
struct SegTree {
    int n;
    unsigned int tree[SEGTREESIZE];
    pui remainOperation[SEGTREESIZE];
    // operation -> (fi, se) => fi + se * x

    unsigned int adjustOperation(unsigned int val, pui operation, int l, int r) {
        return val * operation.se + operation.fi * (r - l + 1);
    }

    pui mergeOperation(pui opX, pui opY) {
        // x -> opX(x) -> opY(opX(x))
        // get opY(opX)
        pui res;
        res.fi = opX.fi * opY.se + opY.fi;
        res.se = opX.se * opY.se;
        return res;
    }

    void init(int _n) {
        n = _n;
    }

    void spread(int u, int l, int r) {
        int v1 = 2 * u;
        int v2 = 2 * u + 1;
        int mid = (l + r) >> 1;
        tree[v1] = adjustOperation(tree[v1], remainOperation[u], l, mid);
        tree[v2] = adjustOperation(tree[v2], remainOperation[u], mid + 1, r);
        remainOperation[v1] = mergeOperation(remainOperation[v1], remainOperation[u]);
        remainOperation[v2] = mergeOperation(remainOperation[v2], remainOperation[u]);
        remainOperation[u] = pii(0, 1);
    }

    void update(int u, int l, int r, int s, int e, pui operation) {
        if (l != r) {
            spread(u, l, r);
        }
        if (s <= l && r <= e) {
            if (l != r) {
                remainOperation[u] = mergeOperation(remainOperation[u], operation);
            }
            tree[u] = adjustOperation(tree[u], operation, l, r);
            return;
        }
        int mid = (l + r) >> 1;
        if (e <= mid) {
            update(2 * u, l, mid, s, e, operation);
        }
        else if (s > mid) {
            update(2 * u + 1, mid + 1, r, s, e, operation);
        }
        else {
            update(2 * u, l, mid, s, mid, operation);
            update(2 * u  + 1, mid + 1, r, mid + 1, e, operation);
        }
        tree[u] = (tree[2 * u] + tree[2 * u + 1]);

    }

    void update(int s, int e, int type, int val) {
        pii operation;
        if (type == 0) {
            operation = pii(val, 1);
        }
        else {
            operation = pii(0, val);
        }
        update(1, 1, n, s, e, operation);
    }

    unsigned int get(int u, int l, int r, int s, int e) {
        if (l != r) {
            spread(u, l, r);
        }
        if (s <= l && r <= e) {
            return tree[u];
        }
        int mid = (l + r) >> 1;
        if (e <= mid) {
            return get(2 * u, l, mid, s, e);
        }
        else if (s > mid) {
            return get(2 * u + 1, mid + 1, r, s, e);
        }
        return get(2 * u, l, mid, s, mid) + get(2 * u + 1, mid + 1, r, mid + 1, e);
    }
    unsigned int get(int s, int e) {
        return get(1, 1, n, s, e);
    }
    
}segTree;
int n;
int c;
int weight[MAXN], par[MAXN];
int head[MAXN];
pii range[MAXN];
vector<int> adj[MAXN];
void makeWeight(int u, int pa) {
    weight[u] = 1;
    par[u] = pa;
    for (int v: adj[u]) {
        if (v == pa) {
            continue;
        }
        makeWeight(v, u);
        weight[u] += weight[v];
    }
}

void constructHLD(int u, int pa, int h) {
    range[u].fi = ++c;
    head[u] = h;
    for (int &v: adj[u]) {
        if (v == pa) {
            continue;
        }
        if (weight[v] > weight[adj[u][0]] || adj[u][0] == pa) {
            swap(adj[u][0], v);
        }
    }

    for (int v: adj[u]) {
        if (v == pa) {
            continue;
        }
        if (adj[u][0] == v) {
            // main chain
            constructHLD(v, u, h);
        }
        else {
            // generate new chain
            constructHLD(v, u, v);
        }
    }
    range[u].se = c;
}

void updateCurvedRoute(int x, int y, int type, int val) {
    while (head[x] != head[y]) {
        if (range[head[x]].fi < range[head[y]].fi) {
            swap(x, y);
        }
        segTree.update(range[head[x]].fi, range[x].fi, type, val);
        x = par[head[x]];
    }
    if (range[x].fi < range[y].fi) {
        swap(x, y);
    }
    segTree.update(range[y].fi, range[x].fi, type, val);
}

unsigned int getCurvedRoute(int x, int y) {
    unsigned int res = 0;
    while (head[x] != head[y]) {
        if (range[head[x]].fi < range[head[y]].fi) {
            swap(x, y);
        }
        res = res + segTree.get(range[head[x]].fi, range[x].fi);
        x = par[head[x]];
    }
    if (range[x].fi < range[y].fi) {
        swap(x, y);
    }
    res = res + segTree.get(range[y].fi, range[x].fi);
    return res;
}

int main() {
    freopen("input.txt","r",stdin);
    int q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        adj[x].pb(y);
        adj[y].pb(x);
    }

    makeWeight(1, 0);

    c = 0;
    constructHLD(1, 0, 1);

    segTree.init(n);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 1) {
            int x, v;
            scanf("%d %d", &x, &v);
            segTree.update(range[x].fi, range[x].se, 0, v);
        }
        else if (type == 2 || type == 4) {
            int x, y, v;
            scanf("%d %d %d", &x, &y, &v);
            updateCurvedRoute(x, y, type / 2 - 1, v);
        }
        else if (type == 3) {
            int x, v;
            scanf("%d %d", &x, &v);
            segTree.update(range[x].fi, range[x].se, 1, v);
        }
        else if (type == 5) {
            int x;
            scanf("%d", &x);
            printf("%u\n", segTree.get(range[x].fi, range[x].se));
        }
        else if (type == 6) {
            int x, y;
            scanf("%d %d", &x, &y);
            printf("%u\n", getCurvedRoute(x, y));
        }
    }
    return 0;
}