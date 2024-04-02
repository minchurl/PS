#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int MAXN = 1005;
const int MAXM = 10005;
int n, m;
int cn;
int dfn[MAXN], dn;
int vis[MAXN], vn;
int cmp[MAXN], sz[MAXN];
vector<int> adj[MAXN],sadj[MAXN];
int conn[MAXN][MAXN];
void init() {
    dn = cn = vn = 0;
    for (int i = 1; i <= n; i++) {
        sadj[i].clear();
        adj[i].clear();
        dfn[i] = cmp[i] = sz[i] = 0;
        vis[i] = 0;
        for (int j = 1; j <= n; j++) {
            conn[i][j] = 0;
        }
    }
}

stack<int> st;
int construct_scc(int u) {
    int ret;
    ret = dfn[u] = ++dn;
    st.push(u);
    for (int v: adj[u]) {
        if (!dfn[v]) {
            ret = min(ret, construct_scc(v));
        }
        else if (dfn[v] && !cmp[v]) {
            ret = min(ret, dfn[v]);
        }
    }
    if (ret == dfn[u]) {
        cn++;
        while (dfn[st.top()] > ret) {
            sz[cn]++;
            cmp[st.top()] = cn;
            st.pop();
        }
        sz[cn]++;
        cmp[st.top()] = cn;
        st.pop();
    }
    return ret;
}
void construct_scc() {
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            construct_scc(i);
        }
    }

    for (int u = 1; u <= n; u++) {
        for (int v: adj[u]) {
            if (cmp[u] != cmp[v]) {
                sadj[cmp[u]].pb(cmp[v]);
            }
        }
    }
}
void construct_conn(int u, int r) {
    vis[u] = vn;
    conn[r][u]++;
    for (int v: sadj[u]) {
        if (vis[v] == vn) {
            conn[r][v]++;
        }
        else {
            construct_conn(v, r);
        }
    }
}
void construct_conn() {
    for (int i = 1; i <= cn; i++) {
        vn++;
        construct_conn(i, i);
    }
}
long long calc() {
    long long ret = 0;

    for (int u = 1; u <= cn; u++) {
        for (int v: sadj[u]) {
            if (conn[u][v] <= 1) {
                continue;
            }
            int sum = 0;
            for (int i = 1; i <= cn; i++) {
                if (conn[u][i] && conn[i][v]) {
                    sum += sz[i];
                }
            }

            ret += sum;
        }
    }
    return ret;

}
int main() {
    freopen("input.txt", "r", stdin);
    int TC;
    scanf("%d", &TC);

    for (int TI = 1; TI <= TC; TI++) {
        printf("Case #%d\n", TI);
        scanf("%d %d", &n, &m);
        init();
        for (int i = 1; i <= m; i++) {
            int s, e;
            scanf("%d %d", &s, &e);
            adj[s].pb(e);
        }
        construct_scc();
        construct_conn();
        printf("%lld\n", calc());
    }
    return 0;
}