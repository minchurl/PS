#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
const int MAXN = 305;
int n;
int dst[MAXN][MAXN];
bool chk[MAXN][MAXN];
vector<pii> res;
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &dst[i][j]);
            chk[i][j] = true;
        }
        chk[i][i] = false;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j || j == k || i == k) {
                    continue;
                }
                int c = max({dst[i][j], dst[j][k], dst[i][k]});
                if (dst[i][k] != c) {
                    continue;
                }
                int a = dst[i][j];
                int b = dst[j][k];
                if (a + b < c) {
                    return !printf("-1\n");
                }
                if (a + b == c) {
                    chk[i][k] = false;
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (chk[i][j]) {
                res.pb(pii(i, j));
            }
        }
    }

    printf("%d\n", res.size());
    for (pii p: res) {
        printf("%d %d %d\n", p.fi, p.se, dst[p.fi][p.se]);
    }
    return 0;
}