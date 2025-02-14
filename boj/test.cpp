#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long LL;
typedef pair<LL, LL> pll;
const int MAXN = 35;
const int MAXM = 14349000;
const LL inf = (1LL << 60);
int n, m;
LL D;
LL A[MAXN], B[MAXN];
LL tree[4 * MAXM];
vector<pll> lst;
LL res;
void construct_tree(int u, int l, int r) {
    if (l == r) {
        tree[u] = lst[l].se;
        return;
    }
    int mid = (l + r) >> 1;
    construct_tree(2 * u, l, mid);
    construct_tree(2 * u + 1, mid + 1, r);
    tree[u] = max(tree[2 * u], tree[2 * u + 1]);
}
LL get_max(int u, int l, int r, int s, int e) {
    if (s <= l && r <= e) {
        return tree[u];
    }
    int mid = (l + r) >> 1;
    if (e <= mid) {
        return get_max(2 * u, l, mid, s, e);
    }
    else if (s > mid) {
        return get_max(2 * u + 1, mid + 1, r, s, e);
    }
    else {
        return max(get_max(2 * u, l, mid, s, mid), get_max(2 * u + 1, mid + 1, r, mid + 1, e));
    }
}
LL get_max(int s, int e) {
    return get_max(1, 0, m - 1, s, e);
}
void calc_first_half(int i, LL a, LL b) {
    if (i >= n / 2) {
        lst.pb(pll(a, b));
        return;
    }

    // 0
    calc_first_half(i + 1, a, b);
    // 1
    calc_first_half(i + 1, a + A[i], b + B[i]);
    // 2
    calc_first_half(i + 1, a - A[i], b - B[i]);
}

void calc_second_half(int i, LL a, LL b) {
    if (i >= n) {
        int s = lower_bound(all(lst), pll(-a - D, -inf)) - lst.begin();
        int e = upper_bound(all(lst), pll(-a + D, inf)) - lst.begin() - 1;
        if (s <= e) {
            res = max(res, b + get_max(s, e));
        }
        return;
    }

    // 0
    calc_second_half(i + 1, a, b);
    // 1
    calc_second_half(i + 1, a + A[i], b + B[i]);
    // 2
    calc_second_half(i + 1, a - A[i], b - B[i]);
}
int main() {
    scanf("%d %lld", &n, &D);
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &A[i], &B[i]);
    }
    if (n == 1) {
        printf("%lld\n", A[0] <= D ? B[0] : 0);
        return 0;
    }

    calc_first_half(0, 0, 0);
    sort(all(lst));
    m = lst.size();
    construct_tree(1, 0, m - 1);

    calc_second_half(n / 2, 0, 0);

    printf("%lld\n", res);
    return 0;
}