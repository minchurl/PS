#include<bits/stdc++.h>
#define pb push_back
#define eb emplace_back
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 100005;
const int inf = 0x3fffffff;
struct cont_range {
    int h, i;
    int lc, rc, mc;
    cont_range(int _h, int _i, int _lc, int _rc, int _mc) {
        h = _h;
        i = _i;
        lc = _lc;
        rc = _rc;
        mc = _mc;
    }
    bool operator < (const cont_range d) const {
        if (h == d.h) {
            return i < d.i;
        }
        return h < d.h;
    }
};
vector<cont_range> t[2 * MAXN];
int n;
int par[MAXN], sz[MAXN];
int h[MAXN];
int find_par(int x) {
    return (par[x] == x) ? (x) : (par[x] = find_par(par[x]));
}
void init (int u, int l, int r) {
    t[u].eb(inf, 0, 0, 0, 0);
    for (int i = l; i <= r; i++) {
        par[i] = i;
        sz[i] = 1;
        t[u].eb(h[i], i, 0, 0, 0);
    }
    sort(all(t[u]));

    int i = t[u].size() - 2;
    int mc = 0;
    for (; i >= 0; i--) {
        cont_range c = t[u][i];
        int cip = find_par(c.i);
        // merge with left
        if (c.i - 1 >= l && c.h <= h[c.i - 1]) {
            int p = find_par(c.i - 1);
            if (p != cip) {
                par[p] = cip;
                sz[cip] += sz[p];
            }
        }
        // merge with right
        if (c.i + 1 <= r && c.h <= h[c.i + 1]) {
            int p = find_par(c.i + 1);
            if (p != cip) {
                par[p] = cip;
                sz[cip] += sz[p];
            }
        }

        t[u][i].mc = mc = max(mc, sz[cip]);
        t[u][i].lc = (h[l] >= c.h) ? sz[find_par(l)] : 0;
        t[u][i].rc = (h[r] >= c.h) ? sz[find_par(r)] : 0;
    }

    if (l == r) {
        return;
    }

    int mid = (l + r) >> 1;
    init(2 * u, l, mid);
    init(2 * u + 1, mid + 1, r);
}
cont_range get_max_cont(int u, int l, int r, int s, int e, int limit_h) {
    if (s <= l && r <= e) {
        cont_range ret = *(lower_bound(all(t[u]), cont_range(limit_h, 0, 0, 0, 0)));
        return ret;
    }
    int mid = (l + r) >> 1;
    if (e <= mid) {
        return get_max_cont(2 * u, l, mid, s, e, limit_h);
    }
    else if (s > mid) {
        return get_max_cont(2 * u + 1, mid + 1, r, s, e, limit_h);
    }
    else {
        cont_range lv = get_max_cont(2 * u, l, mid, s, mid, limit_h);
        cont_range rv = get_max_cont(2 * u + 1, mid + 1, r, mid + 1, e, limit_h);
        cont_range ret = cont_range(
            0, 0, 
            (lv.lc == mid - l + 1) ? mid - l + 1 + rv.lc : lv.lc,   // lc
            (rv.rc == r - mid) ? r - mid + lv.rc : rv.rc,   // rc
            max({lv.mc, rv.mc, lv.rc + rv.lc})  // mc
        );
        return ret;
    }
}
int get_max_cont(int l, int r, int limit_h) {
    return get_max_cont(1, 1, n, l, r, limit_h).mc;
}
int calc(int l, int r, int w) {
    int lo = 1;
    int hi = inf;
    while (lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if (get_max_cont(l, r, mid) >= w) {
            lo = mid;
        }
        else {
            hi = mid - 1;
        }
    }
    return lo;
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &h[i]);
    }
    init(1, 1, n);
    int q;
    scanf("%d", &q);
    while (q--) {
        int l, r, w;
        scanf("%d %d %d", &l, &r, &w);
        printf("%d\n", calc(l, r, w));
    }
    return 0;
}
