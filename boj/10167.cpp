#include<bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long LL;
const LL MAXN = 3005;
const LL SEGTREESIZE = (1 << 13) + 5;
const LL ZERO = 0;
struct node {
    LL lv, rv, mv, sum;
};
struct SegTree {
    LL tn;
    node tree[SEGTREESIZE];

    void init() {
        for (LL i = 0; i < SEGTREESIZE; i++) {
            tree[i].lv = tree[i].rv = tree[i].mv = tree[i].sum = ZERO; 
        }
    }
    void init(LL _tn) {
        tn = _tn;
        init();
    }
    
    void update(LL u, LL l, LL r, LL p, LL v) {
        if (l == r) {
            tree[u].sum += v;
            tree[u].lv = tree[u].rv = tree[u].mv = max(tree[u].sum, ZERO);
            return;
        }
        LL mid = (l + r) >> 1;
        if (p <= mid) {
            update(2 * u, l, mid, p, v);
        }
        else {
            update(2 * u + 1, mid + 1, r, p, v);
        }
        tree[u].sum = tree[2 * u].sum + tree[2 * u + 1].sum;
        tree[u].lv = max({
            tree[2 * u].lv, 
            tree[2 * u].sum + tree[2 * u + 1].lv});
        tree[u].rv = max({
            tree[2 * u + 1].rv, 
            tree[2 * u + 1].sum + tree[2 * u].rv});
        tree[u].mv = max({
            tree[2 * u].mv, 
            tree[2 * u + 1].mv, 
            tree[2 * u].rv + tree[2 * u + 1].lv
        });
    }
    void update(LL p, LL v) {
        update(1, 0, tn - 1, p, v);
    }

    LL get() {
        return tree[1].mv;
    }
}segTree;

struct Mine {
    LL x, y;
    LL v;
}mine[MAXN];
LL n;
LL h, w;
vector<LL> X, Y;
int main() {
    freopen("input.txt","r",stdin);
    scanf("%lld", &n);
    for (LL i = 0; i < n; i++) {
        scanf("%lld %lld %lld", &mine[i].x, &mine[i].y, &mine[i].v);
        X.pb(mine[i].x);
        Y.pb(mine[i].y);
    }

    sort(all(X)); X.erase(unique(all(X)), X.end());
    sort(all(Y)); Y.erase(unique(all(Y)), Y.end());

    for (LL i = 0; i < n; i++) {
        mine[i].x = lower_bound(all(X), mine[i].x) - X.begin();
        mine[i].y = lower_bound(all(Y), mine[i].y) - Y.begin();
    }
    h = Y.size();
    w = X.size();

    sort(mine, mine + n, [&](const Mine x, const Mine y) {
        return x.x < y.x;
    });

    segTree.init(Y.size());

    LL res = 0;

    for (LL l = 0; l < w; l++) {
        LL i = 0;
        // find start point
        while (i < n && mine[i].x < l) {
            i++;
        }
        for (LL r = l; r < w; r++) {
            // add mine
            while (i < n && mine[i].x <= r) {
                segTree.update(mine[i].y, mine[i].v);
                i++;
            }
            res = max(res, segTree.get());
        }
        segTree.init();
    }

    printf("%lld\n", res);

    return 0;
}