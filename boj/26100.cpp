#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
int n;
int origin[MAXN][MAXN];
int V[MAXN];
int max_idx[MAXN];
unsigned int dp[55][5 * 100005 / 32];
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &origin[i][j]);
        }
    }
    int target = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            V[i] += origin[i][j] + origin[j][i];
        }
        target += V[i];
    }
    target /= 2;
    dp[0][0] = 1;
    max_idx[0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = n / 2 - 1; j >= 0; j--) {
            for (int k = 0; k < max_idx[j]; k++) {
                if (k * 32 + V[i] > target) {
                    break;
                }

                if (dp[j][k] == 0) {
                    continue;
                }

                int x = V[i] / 32;
                int y = V[i] % 32;
                dp[j + 1][k + x] |= dp[j][k] << y;
                max_idx[j + 1] = max(max_idx[j + 1], k + x + 1);
                if (y != 0) {
                    dp[j + 1][k + x + 1] |= dp[j][k] >> (32 - y);
                    max_idx[j + 1] = max(max_idx[j + 1], k + x + 2);
                }
            }
        }
    }
    int x, y;
    for (x = target / 32, y = target % 32; (dp[n / 2][x] >> y & 1) == 0 ; (y == 0) ? (x--, y = 31) : y--) {
    }
    printf("%d\n", target - (32 * x + y));
    return 0;
}
