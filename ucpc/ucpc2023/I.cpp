#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long LL;
const int MAXN = 500005;
const LL inf = (1LL << 60);
int n;
LL k;
LL E[MAXN];
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %lld", &n, &k);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &E[i]);
    }

    LL res = -inf;

    // S N
    LL maxx = -E[1];
    for (int i = 2; i <= n; i++) {
        maxx -= k;
        if (res < maxx + E[i]) {
            res = maxx + E[i];
        }

        maxx = max(maxx, -E[i]);
    }

    // N S
    maxx = E[1];

    for (int i = 2; i <= n; i++) {
        maxx -= k;
        if (res < maxx - E[i]) {
            res = maxx - E[i];
        }

        maxx = max(maxx, E[i]);
    }

    printf("%lld\n", res);
    return 0;
}