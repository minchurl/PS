#include<bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long LL;
const LL MAXN = 1000005;
const LL MAXK = 1000005;
const LL M = 1000000007;
LL n, k;
LL P[MAXN];
LL C[MAXN];
LL t[MAXN], tn;
LL nxt[MAXN];
void construct_power() {

    P[0] = 1;
    for (LL i = 1; i <= n; i++) {
        P[i] = (P[i - 1] * (k - 1)) % M;
    }

    C[0] = k;
    for (LL i = 2; i <= n; i++) {
        C[i] = (C[i - 1] * (k - 2) + C[i - 2] * (k - 1)) % M;
    }
    C[1] = k;
    C[0] = 1;
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%lld %lld", &n, &k);
    construct_power();
    for (LL i = 1; i <= n; i++) {
        scanf("%lld", &nxt[i]);
    }
    LL res = 1;
    LL not_in_cycle = n;
    tn = 1;
    for (LL i = 1; i <= n; i++) {
        if (t[i]) {
            continue;
        }
        LL j = i;
        for (; t[j] == 0; j = nxt[j]) {
            t[j] = tn++;
        }
        if (t[j] >= t[i]) {
            LL x = tn - t[j];
            res = (res * C[x]) % M;
            not_in_cycle -= x;
        }
    }

    res = (res * P[not_in_cycle]) % M;

    printf("%lld\n", res);

    return 0;
}