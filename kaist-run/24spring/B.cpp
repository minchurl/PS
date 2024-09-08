#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
const int MAXN = 5005;
int n;
int arr[MAXN];
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
    }

    LL res = 0;
    for (int diff = -n + 1; diff <= n - 1; diff++) {
        int u, d;
        if (diff < 0) {
            u = 1;
            d = u - diff;
        }
        else {
            d = 1;
            u = d + diff;
        }
        LL stric = 0;
        for (; u <= n && d <= n; u++, d++) {
            if (arr[u] <= arr[d]) {
                stric++;
            }
            else {
                res += (stric * (stric + 1)) / 2;
                stric = 0;
            }
        }
        res += (stric * (stric + 1)) / 2;
    }
    printf("%lld\n", res);
    return 0;
}