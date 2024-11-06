#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL calc(LL a, LL b, LL n) {
    if (n == 0) {
        return -1;
    }
    if (n == 1) {
        return a;
    }
    if (n == 2) {
        return b;
    }

    if (a < b) {
        return calc(b, b - a, n - 1);
    }

    if (b == 0) {
        return n % 2 ? a : 0;
    }

}
int main() {
    int q;
    LL a, b;
    scanf("%lld %lld %d", &a, &b, &q);
    while (q--) {
        scanf("%lld", &n);
        printf("%lld\n", calc(a, b, n));
    }
    return 0;
}