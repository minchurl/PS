#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
const int MAXC = 25;
const int inf = 0x3fffffff;
int n;
char A[MAXN];
int Z[MAXN];
int dp[MAXC][MAXN];
void init(int c, int l) {
    for (int i = 0; i <= c; i++) {
        for (int j = 0; j <= l; j++) {
            dp[i][j] = inf;
        }
    }
    dp[0][0] = 0;
}
void construct_Z() {
    int l, r;
    l = r = 0;
    for (int i = 1; i < n; i++) {
        if (i > r) {
            l = i;
            r = i;
            while (r < n && A[r] == A[r - i]) {
                r++;
            }
            Z[i] = r - l;
            r--;
        }
        else {
            int k = i - l;
            if (Z[k] < r - i + 1) {
                Z[i] = Z[k];
            }
            else {
                l = i;
                while (r < n && A[r] == A[r - i]) {
                    r++;
                }
                Z[i] = r - l;
                r--;
            }
        }
    }
}
bool is_repeat(int i) {
    if (i % 2 == 1) {
        return false;
    }
    if (i == 0) {
        return true;
    }
    return Z[i / 2] >= i / 2;
}
int calc(int c) {
    int l = n / ((1 << c) + 1);
    init(c, l);
    for (int a = 0; a <= c; a++) {
        for (int k = 0; k <= l; k++) {
            if (k > 0 && A[k - 1] == A[(l << a) + k - 1]) {
                dp[a][k] = min(dp[a][k], dp[a][k - 1] + 1);
            }
            if (a > 0 && is_repeat(k) && is_repeat((l << a) + k)) {
                dp[a][k] = min(dp[a][k], dp[a - 1][k / 2] + 1);
            }

        }
    }
    return dp[c][l];
}
int main() {
    scanf("%d", &n);
    scanf("%s", A);
    construct_Z();
    // construct Z
    int res = inf;
    for (int c = 0; c <= 20; c++) {
        if (n % ((1 << c) + 1)) {
            continue;
        }
        res = min(res, calc(c));
    }

    printf("%d\n", res == inf ? -1 : res);
    return 0;
}