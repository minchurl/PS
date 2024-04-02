#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3005;
int n;
int L[MAXN][MAXN], R[MAXN][MAXN], K[MAXN][MAXN], DP[MAXN][MAXN];
int V[MAXN];
void init() {
    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= n + 1; j++) {
            L[i][j] = R[i][j] = K[i][j] = DP[i][j] = 0;
        }
        V[i] = 0;
    }
}
void calc() {
    for (int i = 1; i <= n; i++) {
        DP[i][i] = V[i];
        L[i][i] = R[i][i] = V[i];
        K[i][i] = i - 1;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;

            // set K[i][j];
            for (K[i][j] = K[i][j - 1]; K[i][j] < K[i + 1][j] && DP[i][K[i][j] + 1] < DP[K[i][j] + 2][j]; K[i][j]++);

            DP[i][j] = max(L[i][K[i][j]], R[K[i][j] + 1][j]);
            L[i][j + 1] = max(L[i][j], DP[i][j] + V[j + 1]);
            R[i - 1][j] = max(R[i][j], DP[i][j] + V[i - 1]);
            printf("%d %d : %d :: %d\n", i, j, DP[i][j], K[i][j]);
        }
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        printf("Case #%d\n", tc);
        scanf("%d", &n);
        init();
        for (int i = 1; i <= n; i++) {
            scanf("%d", &V[i]);
        }
        calc();
        printf("%d\n", DP[1][n]);
    }
    return 0;
}