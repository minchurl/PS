#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<math.h>
#include<vector>
#include<set>
#include<utility>
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef pair<int, int> pii;
const int MAXN = 200005;
int n, m;
pair<int, pii> lst[MAXN];
vector<int> X, Y;
set<pii> t[MAXN];
int get(int x, int y) {
    int res = 0;
    for (; x > 0; x -= (x & -x)) {
        if (t[x].size() == 0) {
            continue;
        }
        auto it = t[x].lower_bound(pii(y + 1, -1));
        if (it == t[x].begin()) {
            continue;
        }
        it--;
        res = max(res, it -> se);
    }
    return res;
}
void update(int x, int y, int v) {
    for (; x <= n; x += (x & -x)) {
        if (t[x].size() == 0) {
            t[x].insert(pii(y, v));
            continue;
        }
        auto it = t[x].lower_bound(pii(y, v));
        while (it != t[x].end() && it -> se <= v) {
            auto nxt_it = it;
            nxt_it++;
            t[x].erase(it);
            it = nxt_it;
        }
        it = t[x].lower_bound(pii(y, v));
        if (it != t[x].begin()) {
            it--;
            if (it -> se >= v) {
                continue;
            }
        }
        t[x].insert(pii(y, v));
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &m, &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &lst[i].fi);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &lst[i].se.fi);
    }
    if (m == 3) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &lst[i].se.se);
        }
    }
    sort(lst + 1, lst + n + 1);
    for (int i = 1; i <= n; i++) {
        X.pb(lst[i].se.fi);
        Y.pb(lst[i].se.se);
    }
    sort(all(X)); X.erase(unique(all(X)), X.end());
    sort(all(Y)); Y.erase(unique(all(Y)), Y.end());

    int res = 0;

    for (int i = 1; i <= n; i++) {
        int x = lower_bound(all(X), lst[i].se.fi) - X.begin() + 1;
        int y = lower_bound(all(Y), lst[i].se.se) - Y.begin() + 1;

        int v = get(x, y) + 1;
        res = max(res, v);
        update(x, y, v);

    }
    printf("%d\n", res);
    return 0;
}