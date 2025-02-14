#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int MAXN = 100005;
const int MAXC = 19;
const int inf = 0x3fffffff;
int n;
// dp[i][j] -> ith node, head color -> j
int dp[MAXN][MAXC];
vector<int> adj[MAXN];
int calc(int u, int par, int head_c) {
    int sum = 0;
    for (int v: adj[u]) {
        if (v == par) {
            continue;
        }
        int mn = inf;
        for (int c = 1; c < MAXC; c++) {
            if (c != head_c) {
                mn = min(mn, dp[v][c]);
            }
        }
        sum += mn;
    }
    return sum;
}
void dfs(int u, int par) {
    for (int v: adj[u]) {
        if (v == par) {
            continue;
        }
        dfs(v, u);
    }
    // calc
    for (int c = 1; c < MAXC; c++) {
        dp[u][c] = c + calc(u, par, c);
    }
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        adj[x].pb(y);
        adj[y].pb(x);
    }
    int res = inf;
    dfs(1, 0);
    for (int c = 1; c < MAXC; c++) {
        res = min(res, dp[1][c]);
    }

    printf("%d\n", res);
    return 0;
}