#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL inf = (1LL << 60);
const int MAXN = 100005;
LL loc[MAXN];
int main() {
    int T;
    scanf("%d", &T);
    for (int TC = 1; TC <= T; TC++) {
        printf("Case #%d\n", TC);
        LL N, L;
        scanf("%lld %lld", &N, &L);
        LL res = 0;
        LL sum = 0;
        for (int i = 1; i <= N; i++) {
            scanf("%lld", &loc[i]);
            sum += 2 * loc[i];
        }
        res = sum;

        sum = sum + L - 2 * loc[N];
        res = min(res, sum);

        for (int i = N - 1; i >= 1; i--) {
            sum = sum + L - 2 * loc[i + 1] + L - 2 * loc[i];
            res = min(res, sum);
        }
        printf("%lld\n", res);
        fflush(stdout);
    }
    return 0;
}