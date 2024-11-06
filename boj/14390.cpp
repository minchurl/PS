#include<bits/stdc++.h>
using namespace std;
const int MAXN = 15;
const int MAXM = 15;
const int MAXK = (1 << 10) + 5;
const int inf = 0x3fffffff;
int n, m, k;
char A[MAXN][MAXM];
int dp[MAXN][MAXK];
int calc(int i, int pre, int cur) {
    int sum = 0;
    for (int j = 0; j < m; j++) {
        if (A[i][j] == '#') {
            continue;
        }

        // 0 -> horizantal
        if (j != 0 && !(cur >> j & 1) && !(cur >> (j - 1) & 1) && A[i][j - 1] != '#') {
            continue;
        }

        // 1 -> vertical
        if ((cur >> j & 1) && (pre >> j & 1) && A[i - 1][j] != '#') {
            continue;
        }

        sum++;
    }
    return sum;
}
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%s", A[i]);
    }
    k = (1 << m);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < k; j++) {
            dp[i][j] = inf;
        }
    }
    dp[0][0] = 0;
    int res = n * m;
    for (int i = 1; i <= n; i++) {
        for (int pre = 0; pre < k; pre++) {
            for (int cur = 0; cur < k; cur++) {
                dp[i][cur] = min(dp[i][cur], dp[i - 1][pre] + calc(i, pre, cur));
                if (i == n) {
                    res = min(res, dp[i][cur]);
                }
            }
        }
    }

    printf("%d\n", res);
    return 0;
}