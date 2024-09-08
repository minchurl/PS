#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
vector<LL> lst;
int main() {
    freopen("input.txt", "r", stdin);
    LL n, k;
    LL t;
    LL b = 1;
    for (int i = 0; i <= 17; i++) {
        for (LL j = 1; j <= 9; j++) {
            lst.pb(j * b);
        }
        b = b * 10 + 1;
    }
    scanf("%lld", &t);
    while (t--) {
        scanf("%lld %lld", &n, &k);
        vector<LL> res;
        while (k) {
            LL x = lower_bound(lst.begin(), lst.end(), k + 1) - lst.begin() - 1;
            x = lst[x];
            res.pb(x);
            k -= x;
        }
        printf("%d\n", res.size());
        for (LL x: res) {
            printf("%lld ", x);
        }
        printf("\n");
    }
    return 0;
}