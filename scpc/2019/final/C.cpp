#include<bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long LL;
const int MAXN = 100005;
const LL M = 1000000007;
const LL rev2 = 500000004; 
int n, R;
int par[17][MAXN];
int depth[MAXN];
bool pivoted[MAXN];
int left_child[MAXN], right_child[MAXN];
vector<int> adj[MAXN];
void init() {
    for (int i = 0; i <= n; i++) {
        adj[i].clear();
        pivoted[i] = false;
        left_child[i] = right_child[i] = 0;
    }
}
void construct_par() {
    for (int i = 1; i <= 16; i++) {
        for (int j = 1; j <= n; j++) {
            par[i][j] = par[i - 1][par[i - 1][j]];
        }
    }
}

void construct_depth(int u) {
    for (int v: adj[u]) {
        depth[v] = depth[u] + 1;
        construct_depth(v);
    }
}

void construct_depth() {
    depth[0] = 0;
    construct_depth(0);
}

int get_lca(int x, int y) {
    if (depth[x] > depth[y]) {
        swap(x, y);
    }

    for (int i = 16; i >= 0; i--) {
        if (depth[x] <= depth[par[i][y]]) {
            y = par[i][y];
        }
    }

    if (x == y) {
        return x;
    }

    for (int i = 16; i >= 0; i--) {
        if (par[i][x] != par[i][y]) {
            x = par[i][x];
            y = par[i][y];
        }
    }

    return par[0][x];
}

int get_direction(int pa, int u) {
    for (int i = 16; i >= 0; i--) {
        if (depth[par[i][u]] > depth[pa]) {
            u = par[i][u];
        }
    }
    return u;
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    
    for (int TC = 1; TC <= T; TC++) {
        printf("Case #%d\n", TC);
        scanf("%d %d", &n, &R);
        init();
        for (int i = 1; i <= n; i++) {
            int p;
            scanf("%d", &p);
            adj[p].pb(i);
            par[0][i] = p;
        }


        construct_par();
        construct_depth();

        LL cnt = 1;

        for (int i = 1; i <= n; i++) {
            if (adj[i].size()) {
                cnt = (cnt * 2) % M;
            }
        }

        LL sum = cnt;

        for (int i = 1; i <= R; i++) {
            int small, large;
            scanf("%d %d", &small, &large);
            int lca = get_lca(small, large);
            int s = adj[lca].size() >= 2 ? adj[lca][0] + adj[lca][1] : adj[lca][0];
            int l, r;
            if (lca == small) {
                r = get_direction(lca, large);
                l = s - r;
            }
            else if (lca == large) {
                l = get_direction(lca, small);
                r = s - l;
            }
            else {
                l = get_direction(lca, small);
                r = s - l;
            }
            if (pivoted[lca] && (l != left_child[lca] || r != right_child[lca])) {
                cnt = 0;
            }
            if (!pivoted[lca]) {
                cnt = (cnt * rev2) % M;
            }
            pivoted[lca] = true;
            left_child[lca] = l;
            right_child[lca] = r;
            sum = (sum + cnt) % M;
        }

        printf("%lld\n", sum);

    }
    return 0;
}