#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 1000005;
const int MAXM = 10005;
const int MAXK = 10005;
int n, m, k;
LL V[MAXN];
LL flag[4 * MAXN];
LL tree[4 * MAXN];
void init_construct(int u, int l, int r) {
    if (l == r) {
        tree[u] = V[l];
        return;
    }
    int mid = (l + r) >> 1;
    init_construct(2 * u, l, mid);
    init_construct(2 * u + 1, mid + 1, r);

    tree[u] = tree[2 * u] + tree[2 * u + 1];
}
void init_construct() {
    init_construct(1, 1, n);
}
void spread(int u, int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;

    flag[2 * u] += flag[u];
    flag[2 * u + 1] += flag[u];

    tree[2 * u] += flag[u] * (mid - l + 1);
    tree[2 * u + 1] += flag[u] * (r - mid);

    flag[u] = 0;
}
void update(int u, int l, int r, int s, int e, LL v) {
    spread(u, l, r);
    if (s <= l && r <= e) {
        tree[u] += (r - l + 1) * v;
        flag[u] += v;
        return;
    }
    int mid = (l + r) >> 1;
    if (e <= mid) {
        update(2 * u, l, mid, s, e, v);
    }
    else if (s > mid) {
        update(2 * u + 1, mid + 1, r, s, e, v);
    }
    else {
        update(2 * u, l, mid, s, mid, v);
        update(2 * u + 1, mid + 1, r, mid + 1, e, v);
    }
    tree[u] = tree[2 * u] + tree[2 * u + 1];
}
void update(int s, int e, LL v) {
    update(1, 1, n, s, e, v);
}

LL get(int u, int l, int r, int s, int e) {
    spread(u, l, r);
    if (s <= l && r <= e) {
        return tree[u];
    }

    int mid = (l + r) >> 1;
    if (e <= mid) {
        return get(2 * u, l, mid, s, e);
    }
    else if (s > mid) {
        return get(2 * u + 1, mid + 1, r, s, e);
    }
    else {
        return get(2 * u, l, mid, s, mid) + get(2 * u + 1, mid + 1, r, mid + 1, e);
    }
}
LL get(int s, int e) {
    return get(1, 1, n, s, e);
}
int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &V[i]);
    }
    init_construct();
    m += k;
    while (m--) {
        int ty;
        scanf("%d", &ty);
        if (ty == 1) {
            int s, e;
            LL v;
            scanf("%d %d %lld", &s, &e, &v);
            update(s, e, v);
        }
        else {
            int s, e;
            scanf("%d %d", &s, &e);
            printf("%lld\n", get(s, e));
        }
    }
    return 0;
}