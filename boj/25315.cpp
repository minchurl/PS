#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
const int MAXN = 2505;
int n;
pll lst[MAXN];
pll line[MAXN][2];
bool adj[MAXN][MAXN];
int ccw(pll a, pll b, pll c) {
    LL x = (a.fi * b.se + b.fi * c.se + c.fi * a.se) - (a.se * b.fi + b.se * c.fi + c.se * a.fi);
    return x > 0 ? 1 : -1;
}

bool is_cross(pll xs, pll xe, pll ys, pll ye) {
    if (ccw(xs, xe, ys) * ccw(xs, xe, ye) > 0) {
        return false;
    }
    if (ccw(ys, ye, xs) * ccw(ys, ye, xe) > 0) {
        return false;
    }
    return true;
}
int main() {
    freopen("input.txt", "r", stdin);
    LL res = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        pll p, q;
        LL w;
        scanf("%lld %lld %lld %lld %lld", &p.fi, &p.se, &q.fi, &q.se, &w);
        line[i][0] = p;
        line[i][1] = q;
        for (int j = 0; j < i; j++) {
            if (is_cross(line[j][0], line[j][1], p, q)) {
                adj[i][j] = adj[j][i] = true;
            }
        }

        lst[i] = pll(w, i);
        res += (LL)w;
    }

    sort(lst, lst + n);

    for (int j = 0; j < n; j++) {
        pll p = lst[j];
        for (int i = 0; i < n; i++) {
            if (adj[p.se][i]) {
                adj[p.se][i] = adj[i][p.se] = false;
                res += (LL)p.fi;
            }
        }
    }

    printf("%lld\n", res);
    return 0;
}