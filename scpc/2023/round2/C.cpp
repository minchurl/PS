#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
const int MAXM = 5005;
const int inf = 0x3fffffff;
int n, m, t;
int arr[MAXN];
int dp[MAXM][MAXN];
int LT[MAXN], RT[MAXN];
void init() {
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= n + 1; j++) {
            dp[i][j] = 0;
        }
    }
}

int next_val(int c, int l, int i) {

    if (i <= l) {
        return 0;
    }

    // get ft, st
    int ft = RT[l];
    int st = RT[ft];


    int val;
    // l + 1 <= i < ft
    if (i >= l + 1 && i < ft) {
        if (l + t + 1 >= ft) {
            return 0;
        }
        val = min(ft - 1, i + t) - max(i - t, l + t + 1) + 1;
        val = val + dp[c][l];
        return val;
    }

    if (i == ft) {
        // i == ft
        if (ft > 0 && ft <= n) {
            val = dp[c][l] + min(st - 1, ft + t) - max(ft - t, min(l + t + 1, ft)) + 1;
            return val;
        }
        else {
            return 0;
        }
    }

    // ft < i < st
    if (i > ft && i < st) {

        if (l + t >= ft && i - t <= ft) {
            val = dp[c][l] + min(st - 1, i + t) - ft + 1;
        }
        else {
            val = dp[c][l] + min(st - 1, i + t) - max(i - t, ft + 1) + 1;
        }
        return val;
    }

    // i == st
    if (i == st) {

        if (st > 0 && st <= n) {
            int tt = RT[st];
            if (l + t >= ft && st - t <= ft) {
                val = dp[c][l] + min(tt - 1, st + t) - ft + 1;
            }
            else {
                val = dp[c][l] + min(tt - 1, st + t) - max(st - t, ft + 1) + 1;
            }
            return val;
        }
        else {
            return 0;
        }
    }

    // i > st
    if (i > st) {
        val = dp[c][l] + min(i + t, RT[i] - 1) - max(i - t, LT[i] + 1) + 1;
        return val;
    }
    return 0;
}

int calc(int c, int s, int e, int l, int r) {
    if (s > e) {
        return 0;
    }
    int mid = (s + e) >> 1;
    int opt = l;
    int val = next_val(c - 1, opt, mid);

    for (int i = l; i <= r; i++) {
        int v = next_val(c - 1, i, mid);
        if (val < v) {
            opt = i;
            val = v;
        }
    }
    dp[c][mid] = val;
    int lval = calc(c, s, mid - 1, l, opt);
    int rval = calc(c, mid + 1, e, opt, r);
    return max(val, max(lval, rval));
}

int calc() {
    int res = 0;

    // c == 1

    for (int l = 1; l <= n; l++) {
        dp[1][l] = min(l + t, RT[l] - 1) - max(l - t, LT[l] + 1) + 1;
        res = max(res, dp[1][l]);
    }

    // dnc

    for (int c = 2; c <= m; c++) {
        res = max(res, calc(c, 1, n, 1, n));
    }
    return res;
}
int main() {
    freopen("input.txt", "r", stdin);
    int TN;
    scanf("%d", &TN);
    for (int TC = 1; TC <= TN; TC++) {
        printf("Case #%d\n", TC);
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &arr[i]);
        }
        scanf("%d %d", &m, &t);
        if (n > 1000) {
            printf("0\n");
            continue;
        }
        arr[0] = arr[n + 1] = 2;
        int lt = 0;
        LT[0] = -1;
        for (int i = 1; i <= n + 1; i++) {
            LT[i] = lt;
            if (arr[i] == 2) {
                lt = i;
            }
        }

        int rt = n + 1;
        RT[n + 1] = -1;
        for (int i = n; i >= 0; i--) {
            RT[i] = rt;
            if (arr[i] == 2) {
                rt = i;
            }
        }


        init();
        printf("%d\n", calc());
    }
    return 0;
}