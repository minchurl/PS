#include<bits/stdc++.h>
#define pb push_back
#define eb emplace_back
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 1000005;
const int MAXQ = 1000005;
const int MAXM = 19;
int n;
int V[MAXN];
int last[MAXN];
vector<int> X;
struct node {
    int v, l, r;
    node(int _v, int _l, int _r) {
        v = _v;
        l = _l;
        r = _r;
    }
};
vector<node> node_val;
int roots[MAXQ];
int update(int idx, int i, int p, int d) {
    node u = node_val[i];
    int ret = node_val.size();
    node_val.eb(u.v + d, u.l, u.r);
    if (idx < 0) {
    }
    else if (p >> idx & 1) {
        // right
        node_val[ret].r = update(idx - 1, u.r, p, d);
    }
    else {
        // left
        node_val[ret].l = update(idx - 1, u.l, p, d);
    }
    return ret;
}
int get(int idx, int i, int l) {
    if (idx < 0) {
        return node_val[i].v;
    }
    if (l >> idx & 1) {
        return get(idx - 1, node_val[i].r, l);
    }
    else {
        return node_val[node_val[i].r].v + get(idx - 1, node_val[i].l, l);
    }
}
int get(int l, int r) {
    return get(MAXM, roots[r], l);
}
int main() {
    scanf("%d", &n);
    node_val.reserve(MAXN * 2 * (MAXM + 2));
    node_val.eb(0, 0, 0);
    roots[0] = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &V[i]);
        X.pb(V[i]);
    }
    sort(all(X)); X.erase(unique(all(X)), X.end());

    for (int i = 1; i <= n; i++) {
        int v = lower_bound(all(X), V[i]) - X.begin();
        int pre_root = roots[i - 1];
        if (last[v]) {
            pre_root = update(MAXM, pre_root, last[v], -1);
        }
        last[v] = i;
        roots[i] = update(MAXM, pre_root, i, 1);
    }
    int q;
    int prev = 0;
    scanf("%d", &q);
    while (q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        l += prev;
        prev = get(l, r);
        printf("%d\n", prev);
    }
    return 0;
}