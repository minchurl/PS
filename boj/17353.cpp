#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 100005;
struct SegTree {
    int n;
    LL tree[4 * MAXN];
    void init(int _n) {
        n = _n;
    }
    void update(int x, int l, int r, int s, int e, LL v) {
        if (r < s || l > e) {
            return;
        }
        if (s <= l && r <= e) {
            tree[x] += v;
            return;
        }
        int mid = (l + r) >> 1;
        update(2 * x, l, mid, s, e, v);
        update(2 * x + 1, mid + 1, r, s, e, v);
    }
    void update(int s, int e, LL v) {
        update(1, 1, n, s, e, v);
    }

    LL get(int x, int l, int r, int p) {
        if (p < l || p > r) {
            return 0;
        }
        if (l == r) {
            return tree[x];
        }
        int mid = (l + r) >> 1;
        return tree[x] + get(2 * x, l, mid, p) + get(2 * x + 1, mid + 1, r, p);
    }
    LL get(int p) {
        return get(1, 1, n, p);
    }
}sumSegTree, numSegTree;
int n;
LL A[MAXN];
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    sumSegTree.init(n);
    numSegTree.init(n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &A[i]);
    }
    int q;
    scanf("%d", &q);
    while (q--) { 
        int ty;
        scanf("%d", &ty);
        if (ty == 1) {
            int l, r;
            scanf("%d %d", &l, &r);
            sumSegTree.update(l, r, l - 1);
            numSegTree.update(l, r, 1);
        }
        else {
            int p;
            scanf("%d", &p);
            LL res = p * numSegTree.get(p) - sumSegTree.get(p) + A[p];
            printf("%lld\n", res);
        }
    }
    return 0;
}