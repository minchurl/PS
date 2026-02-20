#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int inf = 0x3fffffff;
int n, m;
int main() {
    LL res = 0;
    int minx = inf;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int x;
            scanf("%d", &x);
            minx = min(minx, x);
            res += x;
        }
    }
    res -= minx;
    printf("%lld\n", res);
    return 0;
}