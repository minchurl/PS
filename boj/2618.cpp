#include<bits/stdc++.h>
#define pb push_back
#define abs(x) ((x) > 0 ? (x) : (-(x)))
using namespace std;
const int MAXN = 1005;
const int MAXW = 1005;
const int inf = 0x3fffffff;
int N, W;
int X[MAXN], Y[MAXN];
int dp[MAXW][MAXW];
int pre[MAXW][MAXW];
vector<int> ops;
int get_dst(int st, int ed) {
    return abs(X[st] - X[ed]) + abs(Y[st] - Y[ed]);
}
int main() {
    scanf("%d %d", &N, &W);
    X[0] = Y[0] = 1;
    X[1] = Y[1] = N;
    for (int i = 2; i <= W + 1; i++) {
        scanf("%d %d", &X[i], &Y[i]);
    }

    // init

    for (int i = 0; i <= W + 1; i++) {
        for (int j = 0; j <= W + 1; j++) {
            dp[i][j] = inf;
        }
    }
    dp[0][1] = 0;

    // dp
    for (int i = 2; i <= W + 1; i++) {
        for (int j = 0; j < i - 1; j++) {
            // 1 -> i - 1, 2 -> j
            // 1 go
            if (dp[i][j] > dp[i - 1][j] + get_dst(i - 1, i)) {
                dp[i][j] = dp[i - 1][j] + get_dst(i - 1, i);
                pre[i][j] = i - 1;
            }
            // 2 go
            if (dp[i - 1][i] > dp[i - 1][j] + get_dst(j, i)) {
                dp[i - 1][i] = dp[i - 1][j] + get_dst(j, i);
                pre[i - 1][i] = -j;
            }

            // 1 -> j, 2 -> i - 1 
            // 1 go
            if (dp[i][i - 1] > dp[j][i - 1] + get_dst(j, i)) {
                dp[i][i - 1] = dp[j][i - 1] + get_dst(j, i);
                pre[i][i - 1] = j;
            }
            // 2 go
            if (dp[j][i] > dp[j][i - 1] + get_dst(i - 1, i)) {
                dp[j][i] = dp[j][i - 1] + get_dst(i - 1, i);
                pre[j][i] = -(i - 1);
            }
        }
    }

    int res = inf;
    int i, j;
    for (int k = 0; k <= W; k++) {
        if (res > dp[k][W + 1]) {
            res = dp[k][W + 1];
            i = k;
            j = W + 1;
        }
        if (res > dp[W + 1][k]) {
            res = dp[W + 1][k];
            i = W + 1;
            j = k;
        }
    }

    while (i != 0 || j != 1) {
        if (pre[i][j] >= 0) {
            // 1 move
            ops.pb(1);
            i = pre[i][j];
        }
        else {
            ops.pb(2);
            j = -pre[i][j];
        }
    }

    printf("%d\n", res);

    reverse(ops.begin(), ops.end());
    for (int op: ops) {
        printf("%d\n", op);
    }
    return 0;
}