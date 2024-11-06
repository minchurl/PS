#include<bits/stdc++.h>
using namespace std;
typedef long long llint;
typedef unsigned long long ulint;
const int MAXN = 100005;
const int MAXM = 20;
const int inf = 0x3fffffff;
ulint b;
int n;
char s[MAXN];
int dp[MAXN][MAXM + 2];
bool is_overflow (ulint x, ulint y) {
    // is 10 * x + y > ULLONG_MAX?
    if (x > ULLONG_MAX / 10) {
        return true;
    }
    if (x == ULLONG_MAX / 10 && y > ULLONG_MAX % 10) {
        return true;
    }
    return false;
}
int main() {
    scanf("%s %llu", s + 1, &b);
    n = strlen(s + 1);
    s[0] = '0';
    for (int i = 0; i <= n; i++) {
        for (int j = 1; j <= MAXM; j++) {
            dp[i][j] = inf;
        }
    }
    ulint v = 0;
    bool Z = true;
    for (int i = 1; i <= n; i++) {
        ulint x = s[i] - '0';
        if (is_overflow(v, x) || 10 * v + x > b) {
            Z = false;
            break;
        }
        v = 10 * v + x;
    }
    if (Z) {
        return !printf("0\n");
    }
    dp[0][1] = 0;

    for (int ed = 0; ed < n; ed++) {
        if (s[ed + 1] == '0') {
            continue;
        }
        int max_pre_l = min(ed + 1, MAXM);
        for (int pre_l = 1; pre_l <= max_pre_l; pre_l++) {
            if (dp[ed][pre_l] == inf) {
                continue;
            }

            // construct pre_v
            ulint pre_v = 0;
            for (int i = ed - pre_l + 1; i <= ed; i++) {
                ulint x = s[i] - '0';
                pre_v = pre_v * 10 + x;
            }
            if (pre_v > b) {
                break;
            }

            // printf("%d %d : %llu : %d\n", ed, pre_l, pre_v, dp[ed][pre_l]);


            int max_curr_l = min(n - ed, MAXM);
            ulint curr_v = 0;
            for (int curr_l = 1; curr_l <= max_curr_l; curr_l++) {
                ulint y = s[ed + curr_l] - '0';
                if (is_overflow(curr_v, y) || 10 * curr_v + y > b) {
                    break;
                }
                curr_v = 10 * curr_v + y;
                if (curr_v >= pre_v) {
                    dp[ed + curr_l][curr_l] = min(dp[ed + curr_l][curr_l], dp[ed][pre_l] + 1);
                }
            }
        }
    }

    int res = inf;
    for (int l = 1; l <= MAXM; l++) {
        res = min(res, dp[n][l]);
    }

    if (res == inf) {
        printf("NO WAY\n");
    }
    else {
        printf("%d\n", res - 1);
    }
    return 0;
}