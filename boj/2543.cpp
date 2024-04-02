#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef pair<int, int> pii;
const int MAXN = 100005;
const int MAXM = 2 * MAXN;
const int M = 20070713;
int n, m;
int t[MAXM];
vector<pii> robots;
vector<int> X;
int get(int i) {
    int res = 0;
    for (; i > 0; i -= (i & -i)) {
        res = (res + t[i]) % M;
    }
    return res;
}
void update(int i, int val) {
    for (; i <= m; i += (i & -i)) {
        t[i] = (t[i] + val) % M;
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    X.pb(-1);
    for (int i = 0; i < n; i++) {
        int st, ed;
        scanf("%d %d", &st, &ed);
        robots.pb(pii(st, ed));
        X.pb(st);
        X.pb(ed);
    }
    sort(all(X));
    X.erase(unique(all(X)), X.end());
    m = X.size();

    for (int i = 0; i < n; i++) {
        robots[i].fi = lower_bound(all(X), robots[i].fi) - X.begin() + 1;
        robots[i].se = lower_bound(all(X), robots[i].se) - X.begin() + 1;
    }

    sort(all(robots), [&](const pii x, const pii y) {
        return x.se < y.se;
    });

    update(1, 1);
    for (pii robot: robots) {
        // has no device
        update(robot.se, get(robot.fi - 1));
        // has device
    }
    printf("%d\n", get(m));
    return 0;
}