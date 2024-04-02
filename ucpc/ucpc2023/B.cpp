#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
const int MAXN = 100005;
const int MAXM = 300005;
const int MAXK = 50005;
struct Edge {
    int u, v;
    LL cost;
};
Edge edge[MAXM];
int n, k, m;
int pa[MAXN];
LL res[MAXK];
set<pii> lst[MAXN];
int find_pa(int x) {
    return (x == pa[x]) ? (x) : (pa[x] = find_pa(pa[x]));
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d %d", &n, &k, &m);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        lst[i].insert(pii(x, 1));
        pa[i] = i;
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %lld", &edge[i].u, &edge[i].v, &edge[i].cost);
    }

    sort(edge, edge + m, [&](const Edge x, const Edge y) {
        return x.cost > y.cost;
    });

    for (Edge e: edge) {
        int u = find_pa(e.u);
        int v = find_pa(e.v);
        if (u == v) {
            continue;
        }

        if (lst[u].size() < lst[v].size()) {
            swap(u, v);
        }

        for (auto x: lst[v]) {
            auto it = lst[u].lower_bound(pii(x.fi, 0));
            if (it == lst[u].end() || it -> fi != x.fi) {
                lst[u].insert(x);
            }
            else {
                res[x.fi] += (LL)x.se * it -> se * e.cost;
                pii nx = pii(x.fi, x.se + it -> se);
                lst[u].erase(it);
                lst[u].insert(nx);
            }
        }

        pa[v] = u;
    }

    for (int i = 1; i <= k; i++) {
        printf("%lld\n", res[i]);
    }
    return 0;
}