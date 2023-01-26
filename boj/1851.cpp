#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<LL, LL> pll;
typedef pair<int, int> pii;
const int MAXN = 100005;
const int inf = 0x3fffffff;
int n;
int val[MAXN];
int loc[MAXN];
pii sorted[MAXN];
int globalMin;
bool isVisited[MAXN];
LL res;
void calc(int st) {
    LL sum = 0;
    int cnt = 0;
    int i = st;
    while (!isVisited[i]) {
        isVisited[i] = true;
        if (val[i] != val[loc[i]]) {
            sum += val[i];
            cnt++;
        }
        i = loc[i];
    }
    if (cnt == 0) {
        return;
    }
    LL naiveRes = (LL)(cnt - 1) * val[st] + (sum - val[st]);
    LL swapRes = (LL)(cnt - 1) * globalMin + (sum - val[st]) + 2 * (val[st] + globalMin);
    res += min(naiveRes, swapRes);
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    globalMin = inf;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        globalMin = min(globalMin, x);
        val[i] = x;
        sorted[i] = pii(x, i);
    }
    sort(sorted, sorted + n);

    for (int i = 0; i < n; i++) {
        loc[sorted[i].se] = i;
    }

    for (int i = 0; i < n; i++) {
        int st = sorted[i].se;
        if (isVisited[st]) {
            continue;
        }
        calc(st);
    }
    printf("%lld\n", res);
    return 0;
}