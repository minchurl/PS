#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MAXN = 100005;
const LL mod = 1000000007;
LL cnt[MAXN];
char num[MAXN];
int main() {
    cnt[0] = 1;
    for (LL i = 1; i < MAXN; i++) {
        cnt[i] = (cnt[i - 1] * 3) % mod;
    }
    LL T;
    scanf("%lld", &T);
    for (LL TC = 1; TC <= T; TC++) {
        printf("Case #%lld\n", TC);
        LL N;
        scanf("%s", num);
        N = strlen(num);
        LL res = 0;
        LL i = N;
        for (i = N; i >= 1; i--) {
            if (num[N - i] > '2') {
                res = (res + cnt[i - 1] * 3) % mod;
                break;
            }
            LL x = num[N - i] - '0';
            res = (res + cnt[i - 1] * x) % mod;
        }
        if (i == 0) {
            res++;
        }
        printf("%lld\n", (res + mod - 1) % mod);
    }
    return 0;
}