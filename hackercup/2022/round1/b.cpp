#include<bits/stdc++.h>
#define SQ(x) ((x) * (x))
#define MOD(x) (((x) % mod + mod) % mod)
using namespace std;
typedef long long LL;
const LL mod = 1000000007;
const int MAXN = 500005;


int n, q;

LL sum;
int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int TC;
    scanf("%d", &TC);
    for (int TI = 1; TI <= TC; TI++) {
        printf("Case #%d: ", TI);
        scanf("%d", &n);
        LL sumA = 0;
        LL sumB = 0;
        LL sumAA = 0;
        LL sumBB = 0;
        for (int i = 0; i < n; i++) {
            LL a, b;
            scanf("%lld %lld", &a, &b);
            sumA = MOD(sumA + a);
            sumB = MOD(sumB + b);

            sumAA = MOD(sumAA + SQ(a));
            sumBB = MOD(sumBB + SQ(b));
        }
        LL res = 0;

        scanf("%d", &q);
        for (int i = 0; i < q; i++) {
            LL x, y;
            scanf("%lld %lld", &x, &y);
            res = MOD(res + n * MOD(SQ(x)));
            res = MOD(res + sumAA);
            res = MOD(res + (-2) * x * sumA);

            res = MOD(res + n * MOD(SQ(y)));
            res = MOD(res + sumBB);
            res = MOD(res + (-2) * y * sumB);
        }
        printf("%lld\n", res);
    }
    return 0;
}