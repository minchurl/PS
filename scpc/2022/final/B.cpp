#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 3005;
int n;
LL l_max[MAXN][MAXN], r_max[MAXN][MAXN];
LL V[MAXN];
LL dp[MAXN][MAXN];
void init() {
    for (int len = 1; len <= n; len++) {
        for (int l = 1; l <= n - len + 1; l++) {
            int r = l + len - 1;
            dp[l][r] = 0;
        }
    }

    for (int l = 1; l <= n; l++) {
        for (int i = l; i <= n; i++) {
            l_max[l][i] = V[l];
        }
    }

    for (int r = 1; r <= n; r++) {
        for (int i = r; i >= 1; i--) {
            r_max[r][i] = V[r];
        }
    }
}
int find_point(int l, int r) {
    int s = l - 1;
    int e = r;
    while (s < e) {
        int mid = (s + e + 1) >> 1;
        if (dp[l][mid - 1] <= dp[mid + 1][r]) {
            s = mid;
        }
        else {
            e = mid - 1;
        }
    }
    return s;
}
void calc() {
    // len = 1
    for (int i = 1; i <= n; i++) {
        dp[i][i] = V[i];

        if (i != n) {
            l_max[i][i + 1] = max(l_max[i][i], dp[i][i] + V[i + 1]);
        }

        if (i != 1) {
            r_max[i][i - 1] = max(r_max[i][i], dp[i][i] + V[i - 1]);
        }
    }


    // len > 1
    for (int len = 2; len <= n; len++) {
        for (int l = 1; l <= n - len + 1; l++) {
            int r = l + len - 1;

            int p = find_point(l, r);

            dp[l][r] = max(l_max[l][p], r_max[r][p + 1]);

            if (r != n) {
                l_max[l][r + 1] = max(l_max[l][r], dp[l][r] + V[r + 1]);
            }
            if (l != 1) {
                r_max[r][l - 1] = max(r_max[r][l], dp[l][r] + V[l - 1]);
            }
        }
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    for (int TC = 1; TC <= T; TC++) {
        printf("Case #%d\n", TC);
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &V[i]);
        }
        init();
        calc();
        printf("%lld\n", dp[1][n]);
    }
    return 0;
}