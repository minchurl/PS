#include<bits/stdc++.h>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
const int MAXN = 1005;
const int MAXM = 30005;
const int MAXK = 30005;
const int inf = 0x3fffffff;
int n, m, k;
int dst[MAXN][MAXN];
int S, D;
vector<pii> adj[MAXN];
int sn;
pll st[MAXN];
void construct_dst() {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dst[i][j] = inf;
        }
    }
    dst[0][S] = 0;

    for (int i = 1; i <= n; i++) {
        for (int u = 1; u <= n; u++) {
            for (pii p: adj[u]) {
                dst[i][p.fi] = min(dst[i][p.fi], dst[i - 1][u] + p.se);
            }
        }
    }
}
void construct_st() {
    st[sn++] = pll(n, dst[n][D]);
    for (int a = n - 1; a >= 1; a--) {
        while (sn > 1 && (st[sn - 1].se - dst[a][D]) * (st[sn - 2].fi - st[sn - 1].fi) >= (st[sn - 2].se - st[sn - 1].se) * (st[sn - 1].fi - a)) {
            sn--;
        }
        st[sn++] = pll(a, dst[a][D]);
    }
}
LL cur_x;
LL cur_i;
LL calc() {
    while (cur_i < sn - 1 && st[cur_i].fi * cur_x + st[cur_i].se >= st[cur_i + 1].fi * cur_x + st[cur_i + 1].se) {
        cur_i++;
    }
    return st[cur_i].fi * cur_x + st[cur_i].se;
}
int main() {
    scanf("%d %d %d", &n, &m, &k);
    scanf("%d %d", &S, &D);
    for (int i = 1; i <= m; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        adj[u].eb(v, c);
        adj[v].eb(u, c);
    }
    construct_dst();
    construct_st();
    printf("%lld\n", calc());
    for (int i = 1; i <= k; i++) {
        int x;
        scanf("%d", &x);
        cur_x += x;
        printf("%lld\n", calc());
    }
    return 0;
}