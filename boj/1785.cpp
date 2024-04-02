#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long LL;
const int MAXK = 105;
LL n, k;
LL ans;
map<LL, LL> M[MAXK];
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%lld %lld", &n, &k);
    ans = n;
    M[0][n] = 0;
    for (int i = 0; i < k; i++) {
        for (auto x: M[i]) {
            ans = min(ans, x.se + x.fi);
            if (x.se > ans) {
                continue;
            }
            if (i == k - 1 || x.fi < 2) {
                continue;
            }
            for (int j = 2; j <= 5; j++) {
                LL p = x.fi / j;
                LL q = x.se + x.fi % j;
                if (M[i + 1].find(p) == M[i + 1].end()) {
                    M[i + 1][p] = q;
                }
                else {
                    M[i + 1][p] = min(M[i +1][p], q);
                }
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}