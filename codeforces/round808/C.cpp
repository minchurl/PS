#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef pair<int, int> pii;
const int MAXN = 100005;
const int MAXM = 200005;
const int LOGMAXN = 13;
int n, m;
int pa[MAXN];
int par[LOGMAXN][MAXN], depth[MAXN];
pii initGraph[MAXM];
pii range[MAXN], rn;
vector<int> MSTAdj[MAXN];
vector<pii> notMSTList;
void initPa() {
    for (int i = 1; i <= n; i++) {
        pa[i] = i;
    }
}
int findPa(int x) {
    return (pa[x] == x) ? x : (pa[x] = findPa(pa[x]));
}
bool mergeTwoVertics(int x, int y) {
    x = findPa(x);
    y = findPa(y);
    if (x == y) {
        return false;
    }
    pa[x] = y;
    return true;
}

void findMST() {
    initPa();
    for (int i = 0; i < m; i++) {
        pii e = initGraph[i];
        if (mergeTwoVertics(e.fi, e.se)) {
            MSTAdj[e.fi].pb(e.se);
            MSTAdj[e.se].pb(e.fi);
        }
        else {
            notMSTList.pb(e);
        }
    }
}

void constructPar0(int u, int p) {
    par[0][u] = p;
    range[u].fi = ++rn;
    for (int v: MSTAdj[u]) {
        if (v == p) {
            continue;
        }
        depth[v] = depth[u] + 1;
        constructPar0(v, u);
    }
    range[u].se = rn;
}
void constructPari() {
    for (int i = 1; i < LOGMAXN; i++) {
        for (int j = 1; j <= n; j++) {
            par[i][j] = par[i - 1][par[i - 1][j]];
        }
    }
}
void constructPar() {
    depth[1] = 1;
    constructPar0(1, 0);
    constructPari();
}

int getLCA(int x, int y) {
    if (depth[x] < depth[y]) {
        swap(x, y);
    }
    for (int i = LOGMAXN - 1; i >= 0; i--) {
        if (depth[par[i][x]] >= depth[par[i][y]]) {
            x = par[i][x];
            y = par[i][y];
        }
    }

    if (x == y) {
        return x;
    }

    for (int i = LOGMAXN - 1; i >= 0; i--) {
        if (par[i][x] != par[i][y]) {
            x = par[i][x];
            y = par[i][y];
        }
    }
    return par[0][x];
}


int t[MAXN];
bool ans[MAXN];

void updateBIT(int i, int v) {
    for (; i <= n; i += (i & -i)) {
        t[i] += v;
    }
}
int getBIT(int i) {
    int res = 0;
    for (; i > 0; i -= (i & -i)) {
        res += t[i];
    }
    return res;
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &initGraph[i].fi, &initGraph[i].se);
    }

    // find MST
    findMST();

    // construct par array
    constructPar();

    for (pii e: notMSTList) {
        if (depth[e.fi] < depth[e.se]) {
            swap(e.fi, e.se);
        }
        int lca = getLCA(e.fi, e.se);
        
    }

    printf("\n");
    return 0;
}