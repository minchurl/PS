#include<bits/stdc++.h>
#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
#define pb push_back
using namespace std;
typedef pair<int, int> pii;

const int MAXN = 200005;
vector<int> adj[MAXN];
vector<pii> lst;
int n;
int cap[MAXN];
int res[MAXN];
void init() {
    lst.clear();
    for (int i = 0; i <= n; i++) {
        res[i] = 0;
        adj[i].clear();
    }
}
int main() {
    freopen("input.txt","r",stdin);
    int TC;
    scanf("%d", &TC);
    for (int TI = 1; TI <= TC; TI++) {
        scanf("%d", &n);
        init();

        for (int i = 1; i <= n; i++) {
            scanf("%d", &cap[i]);
            lst.pb(pii(cap[i], i));

        }
        sort(all(lst));

        for (int i = 1; i < n; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            adj[x].pb(y);
            adj[y].pb(x);
        }

        for (pii p: lst) {
            int u = p.se;
            res[u] = 1;
            for (int v: adj[u]) {
                if (cap[u] > cap[v]) {
                    res[u] += res[v];
                }
            }
            res[0] = max(res[0], res[u]);
        }

        printf("Case #%d: %d\n", TI, res[0]);
    }
    return 0;
}