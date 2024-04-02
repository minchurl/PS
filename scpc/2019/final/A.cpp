#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef pair<int, int> pii;
const int MAXN = 100005;
int n, m;
bool chk[MAXN];
vector<pii> lst;
int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    for (int TC = 1; TC <= T; TC++) {
        printf("Case #%d\n", TC);
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; i++) {
            chk[i] = false;
        }
        lst.clear();
        for (int i = 1; i <= m; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            lst.pb(pii(x, y));
        }
        sort(all(lst));
        for (pii p: lst) {
            if (binary_search(all(lst), pii(p.se, p.fi))) {
                chk[p.fi] = true;
                chk[p.se] = true;
            }
        }

        int res = n;
        for (int i = 1; i <= n; i++) {
            res -= chk[i] ? 1 : 0;
        }

        printf("%d\n", res);
    }
    return 0;
}