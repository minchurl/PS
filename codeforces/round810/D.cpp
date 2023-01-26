#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef pair<int, int> pii;
const int MAXN = 2005;
int n;
int par[MAXN];
bool adj[MAXN][MAXN];
vector<pii> res;
int find_par(int x) {
    return (par[x] == x) ? x : (par[x] = find_par(par[x]));
}
void init() {
    for (int i = 1; i <= n; i++) {
        par[i] = i;
    }
    res.clear();
}
void merge(int x, int y) {
    int xx, yy;
    xx = find_par(x);
    yy = find_par(y);
    if (xx == yy) {
        return;
    }
    par[xx] = yy;
    res.pb(pii(x, y));
}
int main() {
    freopen("input.txt","r",stdin);
    int TC;
    scanf("%d", &TC);
    while (TC--) {
        scanf("%d", &n);
        init();
        for (int i = 1; i <= n; i++) {
            char s[MAXN];
            scanf("%s", s);
            for (int j = i; j <= n; j++) {
                adj[i][j] = s[j - i] - '0';
            }
        }

        for (int i = n - 1; i >= 1; i--) {
            for (int j = i + 1; j <= n; j++) {
                if (adj[i][j]) {
                    merge(i, j);
                }
            }
        }
        for (pii p: res) {
            printf("%d %d\n", p.fi, p.se);
        }
    }
    return 0;
}