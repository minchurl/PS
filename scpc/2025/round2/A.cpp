#include<bits/stdc++.h>
#define abs(x) ((x) > 0 ? (x) : (-(x)))
#define pb push_back
using namespace std;
typedef long long LL;
const int MAXN = 200005;
const LL inf = (1LL << 60);
int N;
int sum[MAXN];
int arr[MAXN];
LL dp[MAXN][3];
void init() {
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j < 3; j++) {
            dp[i][j] = inf;
        }
    }
}
int main() {
    setbuf(stdout, NULL);
    int T;
    scanf("%d", &T);
    for (int C = 1; C <= T; C++) {
        printf("Case #%d\n", C);
        scanf("%d", &N);
        init();
        for (int i = 1; i <= N; i++) {
            scanf("%d", &arr[i]);
            sum[i] = sum[i - 1] + arr[i];
        }

        int k = sum[N] - N;
        dp[0][0] = 0;

        for (int i = 1; i <= N; i++) {
            for (int j = 0; j <= k; j++) {
                if (j > i) {
                    continue;
                }
                LL prev;

                // just 1
                prev = sum[i - 1] - (i - 1) - j;
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + abs(prev));

                // lift
                if (j != 0) {
                    prev = sum[i - 1] - (i - 1) - (j - 1);
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + abs(prev));
                }
            }
        }

        printf("%lld\n", dp[N][k]);
    }
    return 0;
}