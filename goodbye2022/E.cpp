#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL getMAX(LL a, LL b, LL c, LL n, LL k) {
    if (a < c) {
        swap(a, c);
    }

    if (b >= a) {
        return b * (n - 1);
    }
    return (n - k) * a + ((k - 1) / 2) * a + (k / 2) * c;
}

LL getMIN(LL a, LL b, LL c, LL n, LL k) {
    if (a < c) {
        swap(a, c);
    }

    if (b >= a) {
        return (n - k) * a + ((k - 1) / 2) * a + (k / 2) * c;
    }
    return b * (n - 1);
}
int main() {
    freopen("input.txt", "r", stdin);
    int TC;
    scanf("%d", &TC);
    while (TC--) {
        LL a, b, c, n, k;
        scanf("%lld %lld %lld %lld %lld", &a, &b, &c, &n, &k);
        printf("%lld %lld\n", getMAX(a, b, c, n, k), getMIN(a, b, c, n, k));
    }
    return 0;
}