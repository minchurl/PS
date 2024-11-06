#include<bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 1005;
const int MAXM = 1005;
const int MAXK = 2005;
struct node {
    int s, e;
    vector<int> in, out;
};
struct edge {
    int nxt;
    int s, e;
    edge (int _nxt, int _s, int _e) {
        nxt = _nxt;
        s = _s;
        e = _e;
    }
};
node V[MAXN];
vector<edge> adj[MAXK];
vector<vector<int>> lst;
int n, m, k;
int in_deg[MAXK], out_deg[MAXK];
void special_case() {
    for (int i = 1; i <= m; i++) {
        int x;
        scanf("%d", &x);
        printf("%d ", x);
    }
    printf("\n");
}
vector<int> dfs(int u) {
    vector<int> res;
    while (adj[u].size()) {
        edge e = adj[u].back();
        adj[u].pop_back();
        vector<int> res1 = dfs(e.nxt);
        res1.pb(e.s);
        for (int v: res1) {
            res.pb(v);
        }
    }
    return res;
}
int main() {
    scanf("%d %d", &n, &m);

    if (n == m) {
        special_case();
        return 0;
    }
    for (int i = 1; i <= n - m + 1; i++) {
        for (int j = 1; j <= m; j++) {
            int x;
            scanf("%d", &x);
            if (j == 1) {
                V[i].s = x;
            }
            if (j == m) {
                V[i].e = x;
            }

            if (j != m) {
                V[i].in.pb(x);
            }
            if (j != 1) {
                V[i].out.pb(x);
            }
        }
        lst.pb(V[i].in);
        lst.pb(V[i].out);
    }

    sort(all(lst)); lst.erase(unique(all(lst)), lst.end());

    k = lst.size();

    for (int i = 1; i <= n - m + 1; i++) {
        int in_idx = lower_bound(all(lst), V[i].in) - lst.begin();
        int out_idx = lower_bound(all(lst), V[i].out) - lst.begin();


        adj[in_idx].pb(edge(out_idx, V[i].s, V[i].e));
        in_deg[out_idx]++;
        out_deg[in_idx]++;
    }
    int st = 0, ed = 0;
    for (int i = 0; i < k; i++) {
        for (int v: lst[i]) {
        }

        if (in_deg[i] < out_deg[i]) {
            st = i;
        }
        if (in_deg[i] > out_deg[i]) {
            ed = i;
        }
    }


    vector<int> res = dfs(st);
    reverse(all(res));
    for (int v: lst[ed]) {
        res.pb(v);
    }
    for (int v: res) {
        printf("%d ", v);
    }
    printf("\n");

    return 0;
}