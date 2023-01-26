#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int MAXN = 100005;
vector<int> adj[MAXN];
int n;
int cnt[2];
void dfs(int u, int p, int c) {
    cnt[c]++;
    for (int v: adj[u]) {
        if (p == v) {
            continue;
        }
        dfs(v, u, !c);
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        adj[x].pb(y);
        adj[y].pb(x);
    }
    dfs(1, 0, 0);
    if (cnt[0] < cnt[1]) {
        swap(cnt[0], cnt[1]);
    }
    printf("%d\n", cnt[0] * 1 + cnt[1] * 2);
    return 0;
}