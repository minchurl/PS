#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 3005;
const int REALMAXN = 100005;
const LL inf = (1LL << 60);

LL V[MAXN];
struct SegTree {
    int n, a;
    LL tree[2 * MAXN];

    void update(int u, int l, int r, LL V[]) {
        if (l == r) {
            tree[u] = V[l];
            return;
        }

        int mid = (l + r) >> 1;
        update(2 * u, l, mid, V);
        update(2 * u + 1, mid + 1, r, V);
        tree[u] = min(tree[2 * u], tree[2 * u + 1]);
    }

    void init(int _n, int _a, LL V[]) {
        n = _n;
        a = _a;
        update(1, a + 1, n, V);
    }


    LL get(int u, int l, int r, int s, int e) {
        if (s <= l && r <= e) {
            return tree[u];
        }

        int mid = (l + r) >> 1;

        LL lval, rval;
        lval = rval = inf;

        if (s <= mid) {
            lval = get(2 * u, l, mid, s, e);
        }
        if (e > mid) {
            rval = get(2 * u + 1, mid + 1, r, s, e);
        }


        return min(lval, rval);
    }
    LL get(int s, int e) {
        return get(1, a + 1, n, s, e);
    }
}segTree[MAXN];
int n;
LL X[REALMAXN], H[REALMAXN];
void construct_segTree() {
    for (int a = 1; a < n; a++) {
        for (int b = a + 1; b <= n; b++) {
            V[b] = (X[b] - X[a]) * (H[a] + H[b]);
        }
        segTree[a].init(n, a, V);
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    int TN;
    scanf("%d", &TN);
    for (int TC = 1; TC <= TN; TC++) {
        printf("Case #%d\n", TC);

        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%lld %lld", &X[i], &H[i]);
        }

        int k;
        scanf("%d", &k);

        if (n > 3000 || k > 3000) {
            while (k--) {
                printf("0\n");
            }
            continue;
        }
        construct_segTree();

        for (int i = 0; i < k; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            LL res = inf;
            for (; a < b; a++) {
                res = min(res, segTree[a].get(a + 1, b));
            }

            printf("%lld\n", res);
        }
    }
    return 0;
}