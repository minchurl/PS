#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pil;

const int MAXN = 100005;

LL n, m, k;

pil V[MAXN];

LL ccw(pil x, pil y, pil z) {
    return (x.fi * y.se + y.fi * z.se + z.fi * x.se) - (x.se * y.fi + y.se * z.fi + z.se * x.fi);
}
int main() {
    freopen("input.txt","r",stdin);
    scanf("%lld %lld %lld", &n, &m, &k);
    pil b;
    scanf("%lld %lld" ,&b.fi, &b.se);
    
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &V[i].fi, &V[i].se);
    }
    return 0;
}