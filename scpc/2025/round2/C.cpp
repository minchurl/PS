#include<bits/stdc++.h>
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define fi first
#define se second
using namespace std;
typedef pair<int, int> pii;
const int inf = 0x3fffffff;
const int MAXN = 200005;
int N;
int k1, k2;
int n1, n2;
vector<int> l1, l2, L;
int maxx[4 * MAXN];
int flag[4 * MAXN];
void init() {
    k1 = k2 = 0;
    l1.clear();
    l2.clear();
    L.clear();
}
void init_segtree(int u, int l, int r) {
    if (l == r) {
        int v = l + 1 - (lower_bound(all(l1), l2[l] - k2) - l1.begin());
        maxx[u] = v;
        flag[u] = v;
        return;
    }
    int mid = (l + r) >> 1;
    init_segtree(2 * u, l, mid);
    init_segtree(2 * u + 1, mid + 1, r);
    maxx[u] = max(maxx[2 * u], maxx[2 * u + 1]);
    flag[u] = 0;
}
void init_segtree() {
    init_segtree(1, 0, n2 - 1);
}
void spread(int u) {
    maxx[2 * u] += flag[u];
    maxx[2 * u + 1] += flag[u];

    flag[2 * u] += flag[u];
    flag[2 * u + 1] += flag[u];

    flag[u] = 0;
}
void update(int u, int l, int r, int s, int e, int v) {
    if (l != r) {
        spread(u);
    }
    if (e < l || s > r || s > e) {
        return;
    }
    if (s <= l && r <= e) {
        maxx[u] += v;
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
    maxx[u] = max(maxx[2 * u], maxx[2 * u + 1]) + flag[u];
}
void update(int s, int e, int v) {
    update(1, 0, n2 - 1, s, e, v);
}
int get_max(int u, int l, int r, int s, int e) {
    if (l != r) {
        spread(u);
    }
    if (e < l || s > r || s > e) {
        return -inf;
    }
    if (s <= l && r <= e) {
        return maxx[u];
    }
    int mid = (l + r) >> 1;
    if (e <= mid) {
        return get_max(2 * u, l, mid, s, e) + flag[u];
    }
    else if (s > mid) {
        return get_max(2 * u + 1, mid + 1, r, s, e) + flag[u];
    }
    else {
        int lv = get_max(2 * u, l, mid, s, mid);
        int rv = get_max(2 * u + 1, mid + 1, r, mid + 1, e);
        return max(lv, rv) + flag[u];
    }
}
int get_max(int s, int e) {
    return get_max(1, 0, n2 - 1, s, e);
}
void input() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        int v, k;
        scanf("%d %d", &v, &k);
        if (k1 == 0) {
            k1 = k;
        }
        else if (k2 == 0 && k != k1) {
            k2 = k;
        }

        if (k1 == k) {
            l1.pb(v);
        }
        else {
            l2.pb(v);
        }
        L.pb(v);
    }
    if (k1 < k2) {
        swap(l1, l2);
        swap(k1, k2);
    }
    n1 = l1.size();
    n2 = l2.size();
}
void solve() {
    int res = 0;
    sort(all(l1));
    sort(all(l2));
    sort(all(L));
    for (int i = 0; i < n1; i++) {
        int l = lower_bound(all(l1), l1[i] - k1) - l1.begin();
        res = max(res, i - l + 1);
    }
    if (k2 == 0) {
        printf("%d\n", res);
        return;
    }

    int ln = L.size();
    for (int i = 0; i < ln; i++) {
        int l = lower_bound(all(L), L[i] - k2) - L.begin();
        res = max(res, (i - l + 1));
    }
    init_segtree();

    int dl1i = 0;
    for (int i = 0; i < n1; i++) {
        int r = l1[i];
        while (dl1i < n1 && l1[dl1i] < r - k1) {
            int s = lower_bound(all(l2), l1[dl1i] + k2 + 1) - l2.begin();
            update(s, n2 - 1, 1);
            dl1i++;
        }
        int r1 = lower_bound(all(l2), r - k2) - l2.begin();
        int r2 = lower_bound(all(l2), r + 1) - l2.begin() - 1;
        int v = (i - dl1i + 1) - r1 + get_max(r1, r2);
        // printf("%d : %d :: %d :: %d %d : %d\n", i, v, dl1i, r1, r2, get_max(r1, r2));
        res = max(res, v);
    }
 
    printf("%d\n", res);
}
int main() {
    setbuf(stdout, NULL);
    int T;
    scanf("%d", &T);
    for (int C = 1; C <= T; C++) {
        printf("Case #%d\n", C);
        init();
        input();
        solve();
    }
    return 0;
}