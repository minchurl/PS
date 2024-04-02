#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int MAXN = 100005;
const int SEGTREENUMBER = (1 << 18) + 5;

int n;
int initVal[MAXN];
int head[MAXN], par[MAXN], idx[MAXN], weight[MAXN];
int hn;

vector<int> adj[MAXN];

struct node {
    bool flag;
    int flagVal;
    int sum, lmax, rmax, mmax;
    int l, r;

    node() {
        sum = lmax = rmax = mmax = 0;
    }
    
    node(int _sum, int _lmax, int _rmax, int _mmax) {
        sum = _sum;
        lmax = _lmax;
        rmax = _rmax;
        mmax = _mmax;
    }

    void zero() {
        sum = lmax = rmax = mmax = 0;
    }
};

void merge(node l, node r, node &res) {
    res.sum = l.sum + r.sum;
    res.lmax = max(l.lmax, l.sum + r.lmax);
    res.rmax = max(r.rmax, r.sum + l.rmax);
    res.mmax = max({
        l.mmax, 
        r.mmax, 
        l.rmax + r.lmax
    });
}

struct SegTree {
    int tn;
    node tree[SEGTREENUMBER];

    void init(int i, int l, int r) {
        tree[i].l = l;
        tree[i].r = r;
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        init(2 * i, l, mid);
        init(2 * i + 1, mid + 1, r);
    }

    void init(int _tn) {
        tn = _tn;
        init(1, 1, tn);
    }

    void adjustFlag(int i) {
        int width = tree[i].r - tree[i].l + 1;
        tree[i].sum = tree[i].flagVal * width;
        tree[i].lmax = tree[i].rmax = tree[i].mmax = max(tree[i].sum, 0);
    }

    void spread(int i) {
        if (tree[i].l == tree[i].r || !tree[i].flag) {
            return;
        }
        tree[2 * i].flag = tree[2 * i + 1].flag = true;
        tree[2 * i].flagVal = tree[2 * i + 1].flagVal = tree[i].flagVal;
        adjustFlag(2 * i);
        adjustFlag(2 * i + 1);
        tree[i].flag = false;
    }

    void update(int i, int s, int e, int v) {
        spread(i);
        if (tree[i].l >= s && tree[i].r <= e) {
            tree[i].flag = true;
            tree[i].flagVal = v;
            adjustFlag(i);
            return;
        }

        int mid = (tree[i].l + tree[i].r) >> 1;
        if (s <= mid) {
            update(2 * i, s, e, v);
        }
        if (e > mid) {
            update(2 * i + 1, s, e, v);
        }
        merge(tree[2 * i], tree[2 * i + 1], tree[i]);
    }
    void update(int s, int e, int v) {
        update(1, s, e, v);
    }

    node get(int i, int s, int e) {
        spread(i);
        if (tree[i].l >= s && tree[i].r <= e) {
            return tree[i];
        }
        int mid = (tree[i].l + tree[i].r) >> 1;

        node l, r, res;
        l.zero(), r.zero(), res.zero();
        if (s <= mid) {
            l = get(2 * i, s, e);
        }
        if (e > mid) {
            r = get(2 * i + 1, s, e);
        }

        merge(l, r, res);
        return res;
    }

    node get(int s, int e) {
        return get(1, s, e);
    }
}segTree;

void setWeight(int u, int p) {
    weight[u] = 1;
    par[u] = p;
    for (int v: adj[u]) {
        if (v == p) {
            continue;
        }
        setWeight(v, u);
        weight[u] += weight[v];
    }
}
void setWeight() {
    setWeight(1, 0);
}

void constructHLD(int u, int p) {
    int sz = adj[u].size();
    if (sz == 1 && adj[u][0] == p) {
        return;
    }

    int maxVal = 0, maxIdx = 0;
    for (int i = 0; i < sz; i++) {
        int v = adj[u][i];
        if (v == p) {
            continue;
        }
        if (maxVal < weight[v]) {
            maxVal = weight[v];
            maxIdx = i;
        }
    }
    swap(adj[u][0], adj[u][maxIdx]);

    head[adj[u][0]] = head[u];
    idx[adj[u][0]] = ++hn;
    constructHLD(adj[u][0], u);

    for (int i = 1; i < sz; i++) {
        int v = adj[u][i];
        if (v == p) {
            continue;
        }
        head[v] = v;
        idx[v] = ++hn;
        constructHLD(v, u);
    }
}
void constructHLD() {
    setWeight();

    head[1] = 1;
    idx[1] = ++hn;
    constructHLD(1, 0);
}


void adjustInitVal() {
    for (int i = 1; i <= n; i++) {
        segTree.update(idx[i], idx[i], initVal[i]);
    }
}

void adjustQuery(int u, int v, int val) {
    while (head[u] != head[v]) {
        if (idx[head[u]] > idx[head[v]]) {
            swap(u, v);
        }
        segTree.update(idx[head[v]], idx[v], val);
        v = par[head[v]];
    }
    if (idx[u] > idx[v]) {
        swap(u, v);
    }
    segTree.update(idx[u], idx[v], val);
}

int calcQuery(int u, int v) {
    node lres, rres, res;
    lres.zero(), rres.zero(), res.zero();
    while (head[u] != head[v]) {
        if (idx[head[u]] > idx[head[v]]) {
            merge(segTree.get(idx[head[u]], idx[u]), lres, lres);
            u = par[head[u]];
        }
        else {
            merge(segTree.get(idx[head[v]], idx[v]), rres, rres);
            v = par[head[v]];
        }
    }
    if (idx[u] > idx[v]) {
        merge(segTree.get(idx[v], idx[u]), lres, lres);
    }
    else {
        merge(segTree.get(idx[u], idx[v]), rres, rres);
    }

    swap(lres.lmax, lres.rmax);

    merge(lres, rres, res);

    return res.mmax;
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &initVal[i]);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].pb(v);
        adj[v].pb(u);
    }
    constructHLD();

    segTree.init(n);
    adjustInitVal();

    int q;
    scanf("%d", &q);
    while (q--) {
        int queryType;
        scanf("%d", &queryType);
        int u, v, val;
        if (queryType == 1) {
            scanf("%d %d", &u, &v);
            printf("%d\n", calcQuery(u, v));
        }
        else {
            scanf("%d %d %d", &u, &v, &val);
            adjustQuery(u, v, val);
        }
    }
    return 0;
}