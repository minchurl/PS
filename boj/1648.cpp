#include<bits/stdc++.h>
using namespace std;
const int MAXN = 20;
const int MAXM = 20;
const int POWERM = (1 << 14);
const int mod = 9901;
int n, m;
int dp[MAXN][POWERM];
void calc(int i, int j, int prev, int curr) {
    if (j == m) {
        dp[i][curr] = (dp[i][curr] + dp[i - 1][prev]) % mod;
        return;
    }

    // case 1, horizentally.
    if (j <= m - 2) {
        calc(i, j + 2, prev, curr);
    }

    // case 2, vertically, with above.
    calc(i, j + 1, prev + (1 << j), curr);

    // case 3, vertically, with below
    calc(i, j + 1, prev, curr + (1 << j));
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        calc(i, 0, 0, 0);
    }

    printf("%d\n", dp[n][0]);
    return 0;
}