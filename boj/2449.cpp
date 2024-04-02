#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;
const int MAXK = 25;
const int inf = 0xfffffff;
int n, k;
int dp[MAXN][MAXN][MAXK];
int C[MAXN];
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &C[i]);
        for (int c = 1; c <= k; c++) {
            dp[i][i][c] = 1;
        }
        dp[i][i][C[i]] = 0;
    }

    for (int len = 2; len <= n; len++) {
        for (int l = 1; l <= n - len + 1; l++) {
            int r = l + len - 1;
            dp[l][r][0] = inf;
            for (int c = 1; c <= k; c++) {
                dp[l][r][c] = inf;
                for (int m = l; m < r; m++) {
                    // [l, m], [m + 1, r]
                    dp[l][r][c] = min(dp[l][r][c], dp[l][m][c] + dp[m + 1][r][c]);
                }
                dp[l][r][0] = min(dp[l][r][0], dp[l][r][c]);
            }
            for (int c = 1; c <= k; c++) {
                dp[l][r][c] = min(dp[l][r][c], dp[l][r][0] + 1);
            }
        }
    }
    printf("%d\n", dp[1][n][0]);
    return 0;
}