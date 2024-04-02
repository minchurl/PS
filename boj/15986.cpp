#include<bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long LL;
const LL MAXN = 200005;
LL n;
LL V[2 * MAXN];
struct SegTree {
    LL n;
    LL tree[4 * MAXN];
    void construct(LL u, LL l, LL r, LL *val) {
        if (l == r) {
            tree[u] = val[l];
            return;
        }

        LL mid = (l + r) >> 1;
        construct(2 * u, l, mid, val);
        construct(2 * u + 1, mid + 1, r, val);
        tree[u] = __gcd(tree[2 * u], tree[2 * u + 1]);
    }

    void init(LL _n, LL *val) {
        n = _n;
        construct(1, 1, n, val);
    }

    LL get(LL u, LL l, LL r, LL s, LL e) {
        if (s <= l && r <= e) {
            return tree[u];
        }

        LL mid = (l + r) >> 1;
        LL lv = s > mid ? 0 : get(2 * u, l, mid, s, e);
        LL rv = e <= mid ? 0 : get(2 * u + 1, mid + 1, r, s, e);
        return __gcd(lv, rv);
    }

    LL get(LL s, LL e) {
        return get(1, 1, n, s, e);
    }
}segTree;
vector<LL> adj[2 * MAXN];
LL find_par(LL u) {
    LL l = u + 1;
    LL r = 2 * n + 1;
    while (l < r) {
        LL mid = (l + r) >> 1;
        if (segTree.get(u, mid - 1) == 1) {
            r = mid;
        }
        else {
            l = mid + 1;
        }
    }
    return l;
}

LL st[2 * MAXN];
LL depth[2 * MAXN];
LL res[MAXN];
void dfs(LL u, LL l, LL r) {
    while (l < r && st[l] - n > u) {
        l++;
    }

    if (u <= n) {
        res[u] = r - l;
    }
    for (LL v: adj[u]) {
        st[r + 1] = v;
        depth[v] = depth[u] + 1;
        dfs(v, l, r + 1);
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%lld", &n);
    for(LL i = 1; i <= n; i++) {
        scanf("%lld", &V[i]);
        V[n + i] = V[i];
    }
    V[2 * n] = 1;
    segTree.init(2 * n, V);

    for (LL i = 1; i <= 2 * n; i++) {
        LL p = find_par(i);
        adj[p].pb(i);
    }
    depth[2 * n + 1] = 1;
    st[0] = 2 * n + 1;
    dfs(2 * n + 1, 0, 0);

    for (LL i = 1; i <= n; i++) {
        printf("%lld\n", res[i]);
    }
    return 0;
}