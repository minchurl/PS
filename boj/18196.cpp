#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef pair<int, int> pii;

const int MAXN = 300005;
const int LOGMAXN = 19;


struct TreeNode {
    int maxVal;
    int mergeVal;
}tree[4 * MAXN];

int n, q;
int par[LOGMAXN][MAXN];
int maxVal[LOGMAXN][MAXN];
int depth[MAXN];
vector<pii> adj[MAXN];

void makePar0(int u, int preU) {
    for (pii v: adj[u]) {
        if (v.fi == preU) {
            continue;
        }
        par[0][v.fi] = u;
        maxVal[0][v.fi] = v.se;
        depth[v.fi] = depth[u] + 1;
        makePar0(v.fi, u);
    }
}

void preprocessLCA() {
    for (int j = 1; j < LOGMAXN; j++) {
        for (int i = 1; i <= n; i++) {
            par[j][i] = par[j - 1][par[j - 1][i]];
            maxVal[j][i] = max(maxVal[j - 1][i], maxVal[j - 1][par[j - 1][i]]);
        }
    }
}

int getMaxVal(int x, int y) {
    int res = 0;

    if (depth[x] < depth[y]) {
        swap(x, y);
    }

    for (int i = LOGMAXN - 1; i >= 0; i--) {
        if (depth[par[i][x]] < depth[y]) {
            continue;
        }
        res = max(res, maxVal[i][x]);
        x = par[i][x];
    }

    if (x == y) {
        return res;
    }

    for (int i = LOGMAXN - 1; i >= 0; i--) {
        if (par[i][x] == par[i][y]) {
            continue;
        }
        res = max({res, maxVal[i][x], maxVal[i][y]});
        x = par[i][x];
        y = par[i][y];
    }

    res = max({res, maxVal[0][x], maxVal[0][y]});
    return res;
}

void initSegTree(int x, int l, int r) {

    if (l == r) {
        return;
    }

    int mid = (l + r) >> 1;
    initSegTree(2 * x, l, mid);
    initSegTree(2 * x + 1, mid + 1, r);

    tree[x].mergeVal = getMaxVal(mid, mid + 1);
    tree[x].maxVal = max({tree[2 * x].maxVal, tree[2 * x + 1].maxVal, tree[x].mergeVal});
}

int getMaxVal(int x, int l, int r, int s, int e) {

    if (s <= l && r <= e) {
        return tree[x].maxVal;
    }

    int mid = (l + r) >> 1;

    if (e <= mid) {
        return getMaxVal(2 * x, l, mid, s, e);
    }
    if (s > mid) {
        return getMaxVal(2 * x + 1, mid + 1, r, s, e);
    }

    int leftChildVal = getMaxVal(2 * x, l, mid, s, mid);
    int rightChildVal = getMaxVal(2 * x + 1, mid + 1, r, mid + 1, e);
    int res = max({leftChildVal, rightChildVal, tree[x].mergeVal});

    return res;
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &n, &q);
    for (int i = 1; i < n; i++) {
        int x, y, v;
        scanf("%d %d %d", &x, &y, &v);
        adj[x].pb(pii(y, v));
        adj[y].pb(pii(x, v));
    }
    depth[1] = 1;
    makePar0(1, 0);
    preprocessLCA();
    initSegTree(1, 1, n);

    while (q--) {
        int s, e;
        scanf("%d %d", &s, &e);
        printf("%d\n", getMaxVal(1, 1, n, s, e));
    }
    return 0;
}