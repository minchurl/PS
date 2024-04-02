#include<bits/stdc++.h>
using namespace std;
const int MAXN = 55;
const int MAXM = 500005;
const int inf = 0x3fffffff;
int n;
int dp[2 * MAXM];
int temp[2 * MAXM];
void init() {
    for (int i = 0; i < 2 * MAXM; i++) {
        dp[i] = -inf;
    }
    dp[MAXM] = 0;
}
void copy_into_temp() {
    for (int i = 0; i < 2 * MAXM; i++) {
        temp[i] = dp[i];
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    init();
    bool is_all_zero = true;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        if (x != 0) {
            is_all_zero = false;
        }

        copy_into_temp();

        // +x
        for (int j = 0; j < 2 * MAXM - x; j++) {
            if (temp[j] == -inf) {
                continue;
            }
            dp[j + x] = max(dp[j + x], temp[j] + x);
        }

        // -x
        for (int j = x; j < 2 * MAXM; j++) {
            if (temp[j] == -inf) {
                continue;
            }
            dp[j - x] = max(dp[j - x], temp[j]);
        }
    }

    if (dp[MAXM] == 0 && !is_all_zero) {
        printf("-1\n");
    }
    else {
        printf("%d\n", dp[MAXM]);
    }
    return 0;
}