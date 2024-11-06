#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 200005;
int n;
LL A[MAXN];
LL tree[4 * MAXN];
void update(int u, int l, int r, int p, LL v) {
    if (l == r) {
        tree[u] = v;
        return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid) {
        update(2 * u, l, mid, p, v);
    }
    else {
        update(2 * u + 1, mid + 1, r, p, v);
    }
    tree[u] = tree[2 * u] + tree[2 * u + 1];
}
void update(int p, LL v) {
    update(1, 0, n, p, v);
}
LL get(int u, int l, int r, LL v) {
    if (l == r) {
        return min(v, tree[u] - v);
    }
    int mid = (l + r) >> 1;
    if (tree[2 * u] > v) {
        return get(2 * u, l, mid, v);
    }
    else {
        return get(2 * u + 1, mid + 1, r, v - tree[2 * u]);
    }
}
LL get(LL v) {
    return get(1, 0, n, v);
}
int main() {
    scanf("%d", &n);
    LL sum = 0;
    for (int i = 1; i < n; i++) {
        int x;
        scanf("%d", &x);
        A[i] = x;
        sum += x;
        update(i, 2 * x);
    }
    printf("%lld\n", get(sum));
    int qn;
    scanf("%d", &qn);
    while (qn--) {
        int p, v;
        scanf("%d %d", &p, &v);
        sum = sum - A[p] + v;
        A[p] = v;
        update(p, 2 * v);
        printf("%lld\n", get(sum));
    }
    return 0;
}