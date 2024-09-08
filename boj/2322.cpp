#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef pair<int, int> pint;
typedef long long llint;
const int MAXN = 100005;
const llint inf = 0x3fffffff;
int n;
bool vis[MAXN];
vector<pint> lst;
int main() {
    scanf("%d", &n);
    int gm = inf;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        gm = min(gm, x);
        lst.pb(pint(x, i));
    }
    sort(all(lst));
    int res = 0;

    for (int i = 0; i < n; i++) {
        if (lst[i].se == i || vis[i]) {
            continue;
        }

        vis[i] = true;
        llint lm = lst[i].fi;
        llint sum = lst[i].fi;
        llint c = 1;
        for (int j = lst[i].se; j != i; j = lst[j].se) {
            vis[j] = true;
            lm = min(lm, (llint)lst[j].fi);
            sum += lst[j].fi;
            c++;
        }
        llint x = lm * (c - 1) + (sum - lm);
        llint y = gm * (c - 1) + (sum - lm) + 2 * (lm + gm);
        if (x < y) {
            res += (int)x;
        }
        else {
            res += (int)y;
        }
    }

    printf("%d\n", res);
    return 0;
}