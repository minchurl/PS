#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
using namespace std;
typedef pair<int, int> pii;
typedef long long LL;
const int MAXN = 10000005;
bool is_prime[MAXN];
pii k[MAXN];
int a, b, c, d;
void prop(int p) {
    for (int i = 2 * p; i <= b; i++) {
        is_prime[i] = false;
        if (i >= a) {
            k[i].fi *= (p - 1);
            k[i].se *= p;
        }
    }
}
int main() {
    scanf("%d %d %d %d", &a, &b, &c, &d);
    for (int i = a; i <= b; i++) {
        k[i].fi = 1;
        k[i].se = 1;
    }
    is_prime[1] = false;
    is_prime[2] = true;
    prop(2);
    for (int i = 3; i <= b; i++) {
        if (is_prime[i]) {
            prop(i);
        }
    }

    LL res = 0;
    for (int i = a; i <= b; i++) {
        int x = (LL)b * k[i].fi / k[i].se;
        int y = (LL)(a - 1) * k[i].fi / k[i].se;
        res += x - y;
    }

    printf("%lld\n", res);
    return 0;
}