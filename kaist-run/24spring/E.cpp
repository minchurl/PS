#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
const int MAXN = 300005;
struct Range {
    int x, y;
    int a, b;
};
Range range[MAXN];
int n, k;
vector<int> ;
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        Range &r = range[i];
        scanf("%d %d %d %d", &r.x, &r.y, &r.a, &r.b);
    }
    return 0;
}