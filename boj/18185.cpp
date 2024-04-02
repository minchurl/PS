#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long LL;
typedef pair<LL, LL> pll;
const LL MAXN = 10005;
LL n;
LL par[MAXN];
LL width[MAXN];
LL lastHeight, res, scoreSum;
vector<pll> lst;
LL find_par(LL x) {
    return (par[x] == x) ? x : (par[x] = find_par(par[x]));
}
LL width2score(LL w) {
    if (w % 3 == 0) {
        return (w / 3) * 7;
    }
    else if (w % 3 == 1) {
        return (w / 3) * 7 + 3;
    }
    else {
        return (w / 3) * 7 + 5;
    }
    return -1;
}
LL getScore(LL i) {
    return width2score(width[i]);
}
void merge(LL x, LL y) {
    x = find_par(x);
    y = find_par(y);
    if (x == y) {
        return;
    }
    scoreSum -= getScore(x) + getScore(y);
    par[y] = x;
    width[x] += width[y];
    scoreSum += getScore(x);
}
void generateNewNode(LL x) {
    par[x] = x;
    width[x] = 1;
    scoreSum += 3;
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%lld", &n);
    for (LL i = 1; i <= n; i++) {
        LL x;
        scanf("%lld", &x);
        if (x) {
            lst.pb(pll(-x, i));
        }
    }
    sort(all(lst));

    for (pll p: lst) {
        if (lastHeight == 0) {
            lastHeight = -p.fi;
        }
        if (lastHeight != -p.fi) {
            res += (lastHeight + p.fi) * scoreSum;
            lastHeight = -p.fi;
        }
        generateNewNode(p.se);
        if (par[p.se - 1]) {
            merge(p.se - 1, p.se);
        }
        if (par[p.se + 1]) {
            merge(p.se + 1, p.se);
        }
    }
    res += (lastHeight) * scoreSum;
    printf("%lld\n", res);
    return 0;
}