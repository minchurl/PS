#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<LL, LL> pll;
const int MAXN = 100005;
LL n;
LL a[MAXN], b[MAXN];
pll line[MAXN];
LL l, r;

bool cmp(pll p, pll q, pll r) {
    return (double) (q.se - p.se) / (p.fi - q.fi) >= (double) (r.se - q.se) / (q.fi - r.fi);
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%lld", &n);
    for (LL i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    for (LL i = 1; i <= n; i++) {
        scanf("%lld", &b[i]);
    }
    line[r++] = pll(b[1], 0);

    for (LL i = 2; i <= n; i++) {
        while (r - l > 1 && line[l + 1].se - line[l].se <= a[i] * (line[l].fi - line[l + 1].fi)) {
            l++;
        }

        pll new_line = pll(b[i], line[l].fi * a[i] + line[l].se);

        while (r - l > 1 && cmp(line[r - 2], line[r - 1], new_line)) {
            r--;
        }
        line[r++] = new_line;
    }

    printf("%lld\n", line[r - 1].se);
    return 0;
}