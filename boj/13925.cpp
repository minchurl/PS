#include<bits/stdc++.h>
#define MOD(x) ((x) % mod)
#define pb push_back
#define eb emplace_back
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pil;
const int MAXN = 100005;
const int mod = 1000000007;
struct SegTree{
    int l, r;
    int sum;
}segTree[4 * MAXN];

// val -> a * val + b
struct Lazy {
    int a, b;

    Lazy() {
    }

    Lazy(int _a, int _b) {
        a = _a;
        b = _b;
    }
}lazy[4 * MAXN];

int n;

void initLazy(int here) {
    lazy[here].a = 1;
    lazy[here].b = 0;
}

void initSegTree(int here, int l, int r) {
    segTree[here].l = l;
    segTree[here].r = r;
    segTree[here].sum = 0;

    initLazy(here);

    if (l == r) {
        return;
    }

    int mid = (l + r) >> 1;

    initSegTree(2 * here, l, mid);
    initSegTree(2 * here + 1, mid + 1, r);
}

void updateLazy(int target, int a, int b) {
    lazy[target].a = MOD((LL)lazy[target].a * a);
    lazy[target].b = MOD((LL)lazy[target].b * a + (LL)b);
}

void updateLazy(int here, int target) {
    updateLazy(target, lazy[here].a, lazy[here].b);
}

void executeLazy(int here) {
    segTree[here].sum = MOD((LL)segTree[here].sum * lazy[here].a + (LL)(segTree[here].r - segTree[here].l + 1) * lazy[here].b);
}

void spread(int here) {
    if (segTree[here].l != segTree[here].r) {
        updateLazy(here, 2 * here);
        updateLazy(here, 2 * here + 1);
    }
    executeLazy(here);
    initLazy(here);
}

void updateSegTree(int here, int s, int e, int a, int b) {
    int l = segTree[here].l;
    int r = segTree[here].r;
    if (l > r) {
        return;
    }
    spread(here);

    if (e < l || s > r) {
        return;
    }

    if (s <= l && r <= e) {
        updateLazy(here, a, b);
        spread(here);
        return;
    }

    int mid = (l + r) >> 1;
    updateSegTree(2 * here, s, e, a, b);
    updateSegTree(2 * here + 1, s, e, a, b);
    segTree[here].sum = MOD(segTree[2 * here].sum + segTree[2 * here + 1].sum);
}
int getResult(int here, int s, int e) {
    int l = segTree[here].l;
    int r = segTree[here].r;
    if (l > r) {
        return 0;
    }
    spread(here);
    if (e < l || s > r) {
        return 0;
    }

    if (s <= l && r <= e) {
        return segTree[here].sum;
    }
    int mid = (l + r) >> 1;
    return MOD(getResult(2 * here, s, e) + getResult(2 * here + 1, s, e));
}
int main() {
    freopen("input.txt","r",stdin);
    scanf("%d", &n);
    initSegTree(1, 1, n);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        updateSegTree(1, i, i, 3, x);
    }

    int q;
    scanf("%d", &q);
    while (q--) {
        int type;
        scanf("%d", &type);
        if (type == 4) {
            int x, y;
            scanf("%d %d", &x, &y);
            printf("%d\n", getResult(1, x, y));
        }
        else {
            int x, y, v;
            scanf("%d %d %d", &x, &y, &v);
            if (type == 1) {
                updateSegTree(1, x, y, 1, v);
            }
            if (type == 2) {
                updateSegTree(1, x, y, v, 0);
            }
            if (type == 3) {
                updateSegTree(1, x, y, 0, v);
            }
        }
    }
    return 0;
}