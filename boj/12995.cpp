#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int MAXN = 55;
const int MAXK = 55;
const int M = 1000000007;
int n, k;
int dp[MAXN][MAXK];
vector<int> adj[MAXN];
int res;
void construct_dp(int u, int par) {
    dp[u][1] = 1;
    for (int v: adj[u]) {
        if (v == par) {
            continue;
        }
        construct_dp(v, u);
        for (int i = k; i >= 1; i--) {
            for (int j = 1; j < i; j++) {
                dp[u][i] = (dp[u][i] + dp[u][j] * dp[v][i - j]) % M;
            }
        }
    }
    res = (res + dp[u][k]) % M;
}
int main() {
    freopen("input.txt" ,"r", stdin);
    scanf("%d %d", &n, &k);
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        adj[x].pb(y);
        adj[y].pb(x);
    }
    construct_dp(1, 0);
    printf("%d\n", res);
    return 0;
}