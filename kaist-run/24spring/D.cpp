#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
const int MAXN = 100005;
const int inf = 0x3fffffff;
int n, m, k;
int ldp[MAXN],rdp[MAXN];
int c[MAXN];
int t[2 * MAXN];
vector<int> X;
void init_t () {
    for (int i = 1; i <= k; i++) {
        t[i] = inf;
    }
}
void update(int i, int v) {
    for (; i <= k; i += (i & -i)) {
        t[i] = min(t[i], v);
    }
}
int get(int i) {
    int res = inf;
    for (; i > 0; i -= (i & -i)) {
        res = min(res, t[i]);
    }
    return res;
}
int get_idx (int i) {
    return lower_bound(all(X), i) - X.begin() + 1;
}
bool is_ok (int x) {
    // generate X
    X.clear();
    X.resize(0);
    X.pb(-x);
    for (int i = 1; i <= n; i++) {
        X.pb(c[i]);
        X.pb(c[i] - x);
    }
    sort(all(X)), X.erase(unique(all(X)), X.end());
    k = X.size();

    // left
    // 0
    init_t();
    update(get_idx(-x), 0);

    for (int i = 1; i <= n; i++) {
        ldp[i] = i - 1 + get(get_idx(c[i]));
        update(get_idx(c[i] - x), ldp[i] - i);
    }
    // right
    init_t();
    update(get_idx(-x), n + 1);

    for (int i = n; i >= 1; i--) {
        rdp[i] = get(get_idx(c[i])) - i - 1;
        update(get_idx(c[i] - x), rdp[i] + i);
    }

    // possibility
    for (int i = 1; i <= n; i++) {
        if (ldp[i] + rdp[i] <= m) {
            return true;
        }
    }
    return false;
}
int main () {
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &c[i]);
    }

    int lo = 0;
    int hi = 1000000000;
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if (is_ok(mid)) {
            hi = mid;
        }
        else {
            lo = mid + 1;
        }
    }
    printf("%d\n", hi);
    return 0;
}