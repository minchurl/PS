#include<bits/stdc++.h>

#define fi first
#define se second
#define pb push_back
#define all(v) (v).begin(), (v).end()

using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const LL MAXV = 50005;
const LL MAXE = 200005;
const LL LOGMAXV = 16;

// number of vertex, edge
LL V, E;

// kruskal
LL pa[MAXV];

// MST / Non-MST edges
struct Edge {
    LL u, v;
    LL val;
    Edge(){}
    Edge(LL _u, LL _v, LL _val) {
        u = _u;
        v = _v;
        val = _val;
    }
};
vector<Edge> nonMST, edge;
vector<pii> adj[MAXV];
LL sumMST;

// union-find
void initPa() {
    for (LL i = 1; i <= V; i++) {
        pa[i] = i;
    }
}

LL find_pa(LL x) {
    return (x == pa[x]) ? x : (pa[x] = find_pa(pa[x]));
}

bool mergeVertex(LL u, LL v) {
    u = find_pa(u);
    v = find_pa(v);
    if (u == v) {
        return false;
    }
    pa[u] = v;
    return true;
}

void kruskal() {
    initPa();

    sort(all(edge), [&](const Edge x, const Edge y) {
        return x.val < y.val;
    });

    for (Edge e: edge) {
        if (mergeVertex(e.u, e.v)) {
            adj[e.u].pb(pii(e.v, e.val));
            adj[e.v].pb(pii(e.u, e.val));
            sumMST += (LL)e.val;
        }
        else {
            nonMST.pb(e);
        }
    }
}

// LCA
struct Min2Min {
    LL fi, se;

    Min2Min() {
        fi = se = -1;
    }

    Min2Min(LL x) {
        fi = x;
        se = -1;
    }

    Min2Min(LL x, LL y) {
        fi = x;
        se = y;
    }
};
Min2Min updateMin2Min(Min2Min x, LL val) {
    if (val == -1 || x.fi == val) {
        return x;
    }
    if (x.fi == -1 || x.fi > val) {
        return Min2Min(val, x.fi);
    }
    if (x.se == -1 || x.se > val) {
        return Min2Min(x.fi, val);
    }
    return x;
}
Min2Min mergeMin2Min(Min2Min x, Min2Min y) {
    x = updateMin2Min(x, y.fi);
    x = updateMin2Min(x, y.se);
    return x;
}

LL depth[MAXV];
LL par[LOGMAXV][MAXV];
Min2Min routeVal[LOGMAXV][MAXV];
bool vis[MAXV];

void generatePar0(LL u) {
    vis[u] = true;
    for (pii v: adj[u]) {
        if (vis[v.fi]) {
            continue;
        }
        par[0][v.fi] = u;
        routeVal[0][v.fi] = Min2Min(v.se);
        depth[v.fi] = depth[u] + 1;
        generatePar0(v.fi);
    }
}

void generatePar() {
    depth[1] = 1;
    generatePar0(1);

    for (LL i = 1; i < LOGMAXV; i++) {
        for (LL j = 1; j <= V; j++) {
            par[i][j] = par[i - 1][par[i - 1][j]];
            routeVal[i][j] = mergeMin2Min(routeVal[i - 1][j], routeVal[i - 1][par[i - 1][j]]);
        }
    }
}

Min2Min getRouteMin2Min(LL u, LL v) {
    Min2Min res;
    if (depth[u] < depth[v]) {
        swap(u, v);
    }

    for (LL i = LOGMAXV - 1; i >= 0; i--) {
        if (depth[par[i][u]] >= depth[v]) {
            res = mergeMin2Min(res, routeVal[i][u]);
            u = par[i][u];
        }
    }

    if (u == v) {
        return res;
    }

    for (LL i = LOGMAXV - 1; i >= 0; i--) {
        if (par[i][u] != par[i][v]) {

            res = mergeMin2Min(res, routeVal[i][u]);
            res = mergeMin2Min(res, routeVal[i][v]);

            u = par[i][u];
            v = par[i][v];
        }
    }

    res = mergeMin2Min(res, routeVal[0][u]);
    res = mergeMin2Min(res, routeVal[0][v]);

    return res;
}

LL ans = -1;
void updateAns(LL val) {
    if (ans == -1) {
        ans = val;
    }
    else {
        ans = min(ans, val);
    }
}
void solve() {
    for (Edge e: nonMST) {
        Min2Min routeV = getRouteMin2Min(e.u, e.v);
        if (routeV.fi != -1 && routeV.fi < e.val) {
            updateAns(-routeV.fi + e.val);
        }
        if (routeV.se != -1 && routeV.se < e.val) {
            updateAns(-routeV.se + e.val);
        }
    }
}



int main() {
    freopen("input.txt", "r", stdin);
    scanf("%lld %lld", &V, &E);
    for (LL i = 0; i < E; i++) {
        LL u, v, val;
        scanf("%lld %lld %lld", &u, &v, &val);
        edge.pb(Edge(u, v, val));
    }

    kruskal();
    // If there exists no MST, printf -1
    if (E - nonMST.size() != V - 1) {
        printf("-1\n");
        return 0;
    }

    generatePar();

    solve();
    printf("%lld\n", (LL)ans + sumMST);
    return 0;
}