#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 105;
LL n, m;
LL A[MAXN];
LL B[MAXN];
int main() {
    scanf("%lld %lld", &n, &m);
    A[0] = A[1] = 1;
    B[0] = B[1] = 0;
    
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            A[i] = (A[i] + A[j - 1] * A[i - j]) % m;
        }

        for (int j = 1; j <= i; j++) {
            B[i] = 
            (
                B[i] + 
                (i - 1) * (A[j - 1] * A[i - j] % m) + 
                (A[j - 1] * B[i - j] % m) + 
                (B[j - 1] * A[i - j] % m)
            ) % m;
        }

        for (int j = 1; j < i; j++) {
            for (int k = j + 1; k <= i; k++) {
                B[i] = 
                (
                    B[i] - 
                    (A[j - 1] * A[k - j - 1] % m) * A[i - k] % m
                    + m
                ) % m;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%lld ", B[i]);
    }
    printf("\n");
    return 0;
}